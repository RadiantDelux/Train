# LCS PS2 semantic decompilation status

## Target

- ELF32 little-endian MIPS/R5900 (Emotion Engine)
- Entry point: `0x001C6A60`
- `.text`: `0x00100000..0x003865E4`
- `.vutext`: `0x003865F0..0x003878C0`
- `$gp = 0x003D6EF0`
- stripped, statically linked
- SHA-256: `65bc2ec3d8a1b9f8482fb7e69427f2539e7e7b49d9dd262bf31aa8aa54ec53b2`

The PS2 ELF is authoritative. Public reverse-engineering trees are used only to test naming hypotheses after a pattern is independently observed in this binary.

## Current coverage

The startup/lifecycle path is structurally identified:

`_start -> main (0x001F3628) -> Game_Bootstrap -> TheGame (0x001F5FA8) -> CGame::Initialise (0x002FAE40) -> CGame::Process (0x002FBAF0)`

Restart handling is also mapped through `CGame::ShutDownForRestart`, `CGame::ReInitGameObjectVariables`, and `CGame::InitialiseWhenRestarting`.

`analysis/symbols.csv` contains 118 tracked function identities. `analysis/globals.csv` contains verified state globals. Longer evidence remains in the notes and assembly dumps rather than bloating the canonical CSVs.

## CGame::Process

`src/CGameProcess.cpp` now lifts the complete `0x002FBAF0..0x002FBEDC` routine, including:

- PS2 load-transition path and `CStreaming::LoadScene`
- pad and volatile/custom-memory maintenance
- `CCutsceneMgr::Update`
- frontend processing gates
- `CStreaming::Update`
- user/code pause gates
- the non-paused simulation chain
- final `MEMID_CARS` traffic maintenance

Verified during the latest pass:

- `CTheScripts::StartTestScript = 0x0010A628`
- `CStreaming::LoadScene = 0x0018FA18`
- `CGarages::Init/Update = 0x00194B58 / 0x00194CA0`
- `CTimeCycle::Update = 0x001B7F30`
- `CCutsceneMgr::Update = 0x0022DAC0`
- `CSpecialFX::Init/Update = 0x00245E50 / 0x00246438`
- `CMenuManager::Process = 0x0033F3A8`
- `CCullZones::Update = 0x003523B0`

A previous provisional `CSpecialFX` assignment at `0x00146FC0/0x00146FF0` was rejected after body inspection. That eight-slot manager is intentionally unnamed again.

## Verified frame globals

- `0x003D5AC0` -> `CCutsceneMgr::ms_running`
- `0x003D5AC4` -> `CCutsceneMgr::ms_cutsceneProcessing`
- `0x003E9C68` -> `CTimer::m_CodePause`
- `0x003E9CB4` -> `CTimer::m_UserPause`

The TimeCycle argument slot used by `CGame::Process` is `$gp - 0x2408 = 0x003D4AE8`; this corrects an earlier scaffold offset that was `+0x10` too high.

## Fidelity policy

Symbols are `verified`, `provisional`, or left address-only. A name is not promoted merely because it occupies the same position in another port. Corrections are expected and are recorded explicitly when binary evidence rejects a prior hypothesis.

The semantic C++ currently passes `g++ -std=c++17 -fsyntax-only src/*.cpp`.
