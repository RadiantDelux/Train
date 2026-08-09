# Port-oriented decompilation plan

The target is semantic fidelity, not byte-for-byte matching.

## Source organization

- `src/game/` -- platform-neutral game logic
- `src/rw/` -- RenderWare-facing compatibility layer reconstructed from observed behavior
- `src/platform/ps2/` -- CD/DVD, IOP RPC, pad, GS/DMA and other PS2-specific calls
- `src/platform/pc/` -- future replacements for the platform layer
- `src/vu/` -- VU microprogram documentation and eventual portable/SIMD equivalents

## Order of attack

1. Startup / main / event loop
2. Timer, file manager and streaming
3. Game data loaders (`GTA_VC.DAT`, IDE/IPL, handling, weapons, etc.)
4. World/entity base types and pools
5. Ped/vehicle/gameplay systems
6. Scripts / `MAIN.SCM`
7. Rendering and RenderWare glue
8. Audio / IOP interfaces
9. VU microcode and PS2-specific performance paths

## Portability discipline

Gameplay code should not depend on original PS2 virtual addresses. During reversing, addresses remain as comments and symbol IDs; after a global/structure is understood it should become a typed field or subsystem state. Platform behavior gets an interface rather than being copied into game logic.
