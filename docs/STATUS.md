# LCS PS2 semantic decompilation status

## Binary

- ELF32 little-endian MIPS/R5900 (Emotion Engine)
- Entry point: `0x001C6A60`
- `.text`: `0x00100000..0x003865E4`
- `.vutext`: `0x003865F0..0x003878C0`
- `$gp` established by CRT as `0x003D6EF0`
- stripped, statically linked
- SHA-256: `65bc2ec3d8a1b9f8482fb7e69427f2539e7e7b49d9dd262bf31aa8aa54ec53b2`

## Automated inventory

Current bootstrap scan finds:

- 8,767 printable diagnostic/data strings
- 34,586 direct `jal` sites into `.text`
- 5,140 unique direct-call targets / function seeds
- 1,718 simple absolute string xrefs

The function count is an upper-bound seed set, not a final function count. SDK/runtime code and false positives still need classification.

## Verified startup path

`_start (0x001C6A60)` clears BSS, establishes `$gp`, performs PS2 thread/heap setup, calls runtime initialization and finally invokes `main` at `0x001F3628`.

`main` calls:

1. `0x0035B420` -- probable global constructor runner
2. `0x001F30F8` -- unknown startup hook; previous command-line-parser hypothesis rejected because the routine does not consume `argc/argv`
3. `0x001F3518` -- game bootstrap/orchestration

`0x001F3518` registers three callbacks, performs platform/runtime initialization, invokes an event-style dispatcher at `0x00264930`, then enters the game initialization routine at `0x001F5FA8`.

`0x001F5FA8` has high-confidence game-init evidence: it references `Into The Game!!!`, `start game init`, `DATA\\GTA_VC.DAT`, `game init DONE!`, and `Starting Game`. It directly invokes `CTimer_Initialise` at `0x002B4C00`.

## High-confidence recovered symbols

See `analysis/symbols.csv`. Exact diagnostic-string symbols already recovered include:

- `CTheScripts::Init` `0x00109BC8`
- `CFileMgr::InitCd` `0x00146F48`
- `cWorldStream::Stream` `0x00203C90`
- `cUmdStream::AcquireLock` `0x002040D8`
- `cUmdStream::ReleaseLock` `0x00204118`
- `cWorldStream::StreamingCallback` `0x00204190`
- `CCarGenerator::DoInternalProcessing` `0x0031FC10`
- `CText::LoadMissionText` `0x00332968`

Strong behavioral identifications include `CTimer_Initialise`, `CClock_Initialise`, `CPopulation_Initialise`, `AudioManager_Initialise`, and the primary game init routine.

## Fidelity rule

Names are assigned in three levels:

- **verified**: exact string, ABI, or structural proof
- **provisional**: strong behavioral evidence but no exact symbol
- **unknown**: retained as `Func_<address>`

A provisional name is never silently promoted to verified. This is important for a future portable source tree: readable code is useful only if it remains traceable to the original executable.

## Main loop pass

The primary lifecycle is now structurally closed:

`TheGame (0x001F5FA8)` -> `CGame::Initialise (0x002FAE40)` -> repeated
`TheGame_Frame (0x001F5BC0)` / `CGame::Process (0x002FBAF0)` ->
`CGame::ShutDownForRestart (0x002FB600)` -> optional
`CGame::InitialiseWhenRestarting (0x002FB700)`.

The contiguous `CGame` region also identifies
`CGame::ReInitGameObjectVariables` at `0x002FB388`.

The symbol table now contains 109 tracked names and includes multiple verified
init/update pairs recovered by correlating the initialisation and frame-update
chains. See `docs/MAIN_LOOP.md` for the current control-flow map.

Boundary correction: `CClock::Initialise` starts at `0x001F8760`.

## CGame::Process semantic lift

- Added `src/CGameProcess.cpp` for the main non-paused simulation update block (`0x002FBC50..0x002FBEC0`).
- Added `docs/CGAME_PROCESS.md` and generated `docs/CGAME_CALLMAP.md`.
- Symbol table now tracks 109 recovered/provisional symbols.
- Newly recovered families include `CParticle` (Init/Update/Render verified) and provisional WaterCannons/UserDisplay/Pickups/GameLogic Init/Update pairs.

## 2026-08-09 core-frame recovery pass

The PS2 `CGame::Process` map now has high-confidence identities for `CWeather`, `CWorld`, `CStreaming`, `CPad`, `CScriptPaths`, the per-frame sprite/font setup, record-data stubs, and `CCarCtrl` init/reinit.  The simulation lift now preserves the repeated `FrontEndMenuManager+0x47D` load-transition guards instead of flattening the frame into an unconditional call list.

The final `MEMID_CARS` block is partially reconstructed as random-car generation, roadblock generation, distant-car removal and a pool-pressure cleanup helper.  Ambiguous helpers remain provisional/address-labelled.
