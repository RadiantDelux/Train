#!/usr/bin/env python3
import csv, struct, re, pathlib, bisect
ELF = pathlib.Path('/mnt/data/2fce5a30-d18a-47c3-9c86-0cc0d67e6a77.elf')
OUT = pathlib.Path('/mnt/data/lcs_decomp/analysis')
data = ELF.read_bytes()
assert data[:4] == b'\x7fELF' and data[4] == 1 and data[5] == 1
(e_shoff,) = struct.unpack_from('<I', data, 0x20)
(e_shentsize,) = struct.unpack_from('<H', data, 0x2e)
(e_shnum,) = struct.unpack_from('<H', data, 0x30)
(e_shstrndx,) = struct.unpack_from('<H', data, 0x32)
secs=[]
for i in range(e_shnum):
    off=e_shoff+i*e_shentsize
    sh=struct.unpack_from('<IIIIIIIIII',data,off)
    secs.append({'idx':i,'name_off':sh[0],'type':sh[1],'flags':sh[2],'addr':sh[3],'off':sh[4],'size':sh[5],'link':sh[6],'info':sh[7],'align':sh[8],'entsize':sh[9]})
shstr=secs[e_shstrndx]
strtab=data[shstr['off']:shstr['off']+shstr['size']]
def cstr(buf,o):
    e=buf.find(b'\0',o)
    if e<0:e=len(buf)
    return buf[o:e].decode('ascii','replace')
for s in secs:s['name']=cstr(strtab,s['name_off'])
secby={s['name']:s for s in secs}
with (OUT/'sections.csv').open('w',newline='') as f:
    w=csv.writer(f); w.writerow(['name','vaddr','file_offset','size','flags'])
    for s in secs:w.writerow([s['name'],f"0x{s['addr']:08X}",f"0x{s['off']:X}",f"0x{s['size']:X}",f"0x{s['flags']:X}"])
strings=[]
for s in secs:
    if s['type'] != 1 or s['size']==0 or not (s['flags'] & 0x2):continue
    blob=data[s['off']:s['off']+s['size']]
    for m in re.finditer(rb'[\x09\x0a\x0d\x20-\x7e]{4,}\x00', blob):
        txt=m.group()[:-1].decode('ascii','replace')
        strings.append((s['addr']+m.start(),s['name'],txt))
strings.sort()
with (OUT/'strings.csv').open('w',newline='') as f:
    w=csv.writer(f); w.writerow(['address','section','text'])
    for a,s,t in strings:w.writerow([f"0x{a:08X}",s,t])
text=secby['.text']; text_blob=data[text['off']:text['off']+text['size']]
text_start=text['addr']; text_end=text_start+text['size']
calls=[]; targets={}
for o in range(0,len(text_blob)-3,4):
    pc=text_start+o; ins=struct.unpack_from('<I',text_blob,o)[0]
    if ins>>26==3:
        tgt=((pc+4)&0xF0000000)|((ins&0x03ffffff)<<2)
        if text_start<=tgt<text_end:
            calls.append((pc,tgt)); targets[tgt]=targets.get(tgt,0)+1
with (OUT/'calls.csv').open('w',newline='') as f:
    w=csv.writer(f); w.writerow(['caller_site','target'])
    for a,b in calls:w.writerow([f"0x{a:08X}",f"0x{b:08X}"])
string_by_addr={a:t for a,_,t in strings}; string_addrs=set(string_by_addr); xrefs=[]
for o in range(0,len(text_blob)-28,4):
    pc=text_start+o; ins=struct.unpack_from('<I',text_blob,o)[0]
    if ins>>26 != 0x0f:continue
    rt=(ins>>16)&31; hi=ins&0xffff
    for k in range(1,7):
        ins2=struct.unpack_from('<I',text_blob,o+4*k)[0]
        op2=ins2>>26; rs=(ins2>>21)&31; rt2=(ins2>>16)&31; lo=ins2&0xffff
        if rt2!=rt or rs!=rt:continue
        addr=None
        if op2==0x09:
            slo=lo if lo<0x8000 else lo-0x10000; addr=((hi<<16)+slo)&0xffffffff
        elif op2==0x0d:addr=(hi<<16)|lo
        if addr in string_addrs:
            xrefs.append((pc,pc+4*k,addr,string_by_addr[addr])); break
with (OUT/'string_xrefs.csv').open('w',newline='') as f:
    w=csv.writer(f); w.writerow(['lui_site','materialize_site','string_address','text'])
    for a,b,c,t in xrefs:w.writerow([f"0x{a:08X}",f"0x{b:08X}",f"0x{c:08X}",t])
seeds=sorted(set(targets)|{0x001C6A60})
def owner(addr):
    i=bisect.bisect_right(seeds,addr)-1
    if i>=0 and addr-seeds[i] <= 0x2000:return seeds[i]
    return None
def clean_name(t):
    m=re.search(r'([A-Za-z_][A-Za-z0-9_]*(?:::[~A-Za-z_][A-Za-z0-9_]*)+)',t)
    return m.group(1) if m else None
out=[]; seen=set()
for a,b,sa,t in xrefs:
    n=clean_name(t); fn=owner(a)
    if n and fn is not None and (fn,n) not in seen:
        seen.add((fn,n)); out.append((fn,n,a,sa,t))
with (OUT/'name_candidates.csv').open('w',newline='') as f:
    w=csv.writer(f); w.writerow(['function_seed','candidate_name','xref_site','string_address','evidence'])
    for fn,n,x,sa,t in out:w.writerow([f"0x{fn:08X}",n,f"0x{x:08X}",f"0x{sa:08X}",t])
xref_count_by_fn={}
for a,b,sa,t in xrefs:
    fn=owner(a)
    if fn is not None:xref_count_by_fn[fn]=xref_count_by_fn.get(fn,0)+1
with (OUT/'function_seeds.csv').open('w',newline='') as f:
    w=csv.writer(f); w.writerow(['address','direct_callers','nearby_string_xrefs'])
    for fn in seeds:w.writerow([f"0x{fn:08X}",targets.get(fn,0),xref_count_by_fn.get(fn,0)])
print(f'sections={len(secs)} strings={len(strings)} direct_calls={len(calls)} function_seeds={len(seeds)} string_xrefs={len(xrefs)} name_candidates={len(out)}')
