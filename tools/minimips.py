#!/usr/bin/env python3
import struct,sys,pathlib
ELF=pathlib.Path('/mnt/data/2fce5a30-d18a-47c3-9c86-0cc0d67e6a77.elf').read_bytes()
TEXT_VA=0x00100000; TEXT_OFF=0x1000; TEXT_SIZE=0x2865e4
R=['zero','at','v0','v1','a0','a1','a2','a3','t0','t1','t2','t3','t4','t5','t6','t7','s0','s1','s2','s3','s4','s5','s6','s7','t8','t9','k0','k1','gp','sp','fp','ra']
def sx16(x): return x if x<0x8000 else x-0x10000
def reg(x): return '$'+R[x]
def target(pc,w):return ((pc+4)&0xF0000000)|((w&0x03ffffff)<<2)
def d(pc,w):
 op=w>>26; rs=(w>>21)&31; rt=(w>>16)&31; rd=(w>>11)&31; sh=(w>>6)&31; fn=w&63; imm=w&0xffff
 if w==0:return 'nop'
 if op==0:
  m={0:'sll',2:'srl',3:'sra',4:'sllv',6:'srlv',7:'srav',8:'jr',9:'jalr',12:'syscall',13:'break',16:'mfhi',17:'mthi',18:'mflo',19:'mtlo',24:'mult',25:'multu',26:'div',27:'divu',32:'add',33:'addu',34:'sub',35:'subu',36:'and',37:'or',38:'xor',39:'nor',42:'slt',43:'sltu',44:'dadd',45:'daddu',46:'dsub',47:'dsubu'}
  n=m.get(fn)
  if n in ('sll','srl','sra'):return f'{n} {reg(rd)}, {reg(rt)}, {sh}'
  if n in ('sllv','srlv','srav'):return f'{n} {reg(rd)}, {reg(rt)}, {reg(rs)}'
  if n=='jr':return f'jr {reg(rs)}'
  if n=='jalr':return f'jalr {reg(rd)}, {reg(rs)}'
  if n in ('syscall','break'):return n
  if n in ('mfhi','mflo'):return f'{n} {reg(rd)}'
  if n in ('mthi','mtlo'):return f'{n} {reg(rs)}'
  if n in ('mult','multu','div','divu'):return f'{n} {reg(rs)}, {reg(rt)}'
  if n:return f'{n} {reg(rd)}, {reg(rs)}, {reg(rt)}'
 if op==1:
  names={0:'bltz',1:'bgez',16:'bltzal',17:'bgezal'}; n=names.get(rt,'regimm')
  return f'{n} {reg(rs)}, 0x{(pc+4+(sx16(imm)<<2))&0xffffffff:08X}'
 if op==2:return f'j 0x{target(pc,w):08X}'
 if op==3:return f'jal 0x{target(pc,w):08X}'
 if op in (4,5,6,7,20,21,22,23):
  n={4:'beq',5:'bne',6:'blez',7:'bgtz',20:'beql',21:'bnel',22:'blezl',23:'bgtzl'}[op]
  dst=(pc+4+(sx16(imm)<<2))&0xffffffff
  if op in (6,7,22,23):return f'{n} {reg(rs)}, 0x{dst:08X}'
  return f'{n} {reg(rs)}, {reg(rt)}, 0x{dst:08X}'
 if op in (8,9,10,11,12,13,14,15,24,25):
  n={8:'addi',9:'addiu',10:'slti',11:'sltiu',12:'andi',13:'ori',14:'xori',15:'lui',24:'daddi',25:'daddiu'}[op]
  if op==15:return f'lui {reg(rt)}, 0x{imm:04X}'
  val=imm if op in (12,13,14) else sx16(imm)
  return f'{n} {reg(rt)}, {reg(rs)}, {val}'
 mem={26:'ldl',27:'ldr',32:'lb',33:'lh',34:'lwl',35:'lw',36:'lbu',37:'lhu',38:'lwr',39:'lwu',40:'sb',41:'sh',42:'swl',43:'sw',44:'sdl',45:'sdr',46:'swr',47:'cache',48:'ll',49:'lwc1',52:'lld',53:'ldc1',55:'ld',56:'sc',57:'swc1',60:'scd',61:'sdc1',63:'sd'}
 if op in mem:return f'{mem[op]} {reg(rt)}, {sx16(imm)}({reg(rs)})'
 if op in (16,17,18):
  return f'cop{op-16} 0x{w&0x03ffffff:07X}'
 return f'.word 0x{w:08X}'
def read_word(va):return struct.unpack_from('<I',ELF,TEXT_OFF+(va-TEXT_VA))[0]
def dump(start,count):
 for i in range(count):
  pc=start+4*i; w=read_word(pc); print(f'{pc:08X}: {w:08X}  {d(pc,w)}')
if __name__=='__main__':dump(int(sys.argv[1],0),int(sys.argv[2],0))
