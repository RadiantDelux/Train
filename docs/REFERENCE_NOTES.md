# Reference-validation notes

A public reLCS reverse-engineering tree was consulted as a naming and
architecture oracle after the addresses/control flow had been recovered from
this ELF. Names are only promoted when the local PS2 binary independently
supports the identification through call position, diagnostic strings,
arguments, paired init/update structure, or lifecycle control flow.

Reference repository used for comparison:
https://github.com/revcs/relcs

Important build difference already observed: this ELF passes
`DATA\\GTA_VC.DAT` to `CGame::Initialise`, so external source is not treated as
byte-identical ground truth.
