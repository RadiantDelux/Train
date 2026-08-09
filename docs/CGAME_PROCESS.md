# `CGame::Process` reconstruction

Binary range: `0x002FBAF0..0x002FBEDC`.

`src/CGameProcess.cpp` now contains a semantic lift of the complete outer routine, including the PS2 load-transition path, pad/custom-memory maintenance, cutscene/frontend handling, streaming, pause gates and the non-paused simulation cluster.

The PS2 ELF remains authoritative. Public reverse-engineering trees are used only to test hypotheses after a binary-side pattern has been found.

## Recovered prelude

The observed control flow is now:

1. If `FrontEndMenuManager + 0x47D` requests a load transition, run `CTheScripts::StartTestScript`, process scripts/camera, call `CStreaming::LoadScene`, perform two still-unnamed streaming helpers, process camera/load-scene again and clear the load flag.
2. `CPad::UpdatePads`.
3. Conditionally invoke the PS2 volatile/custom-memory helper at `0x001FBF68` from the manager at `0x0042A8A0`.
4. `CCutsceneMgr::Update`.
5. Call `FrontEndMenuManager.Process` only when the cutscene-processing and timer code-pause flags are clear.
6. Outside a load transition, execute the unresolved pre-streaming state helper at `0x002D3630`, then `CStreaming::Update`.
7. Return before simulation when either timer pause flag is active.

High-confidence prelude symbols:

| Address | Identity | Evidence |
|---|---|---|
| `0x0010A628` | `CTheScripts::StartTestScript` | Exact wrapper around `StartNewScript(0)` and used in both startup/load paths |
| `0x0018FA18` | `CStreaming::LoadScene` | Exact `Start load scene` diagnostic plus scene-streaming body |
| `0x0016F890` | `CPad::UpdatePads` | Pad manager structure and lifecycle context |
| `0x0022DAC0` | `CCutsceneMgr::Update` | Exact frame position; conditionally enters the cutscene loading state machine at `0x00358600` |
| `0x0033F3A8` | `CMenuManager::Process` | Receives the menu manager at `0x00634610`, mutates its fields and consumes pad input |
| `0x0018AE68` | `CStreaming::Update` | Streaming subsystem body and frame position |

The cutscene state machine reached by `0x0022DAC0` preserves `Loading Cutscene...` and `Cutscene Not Loaded!` diagnostics.

## Recovered frame globals

`analysis/globals.csv` now tracks state variables separately from function symbols.

| Address | Identity | Status |
|---|---|---|
| `0x003D5AC0` | `CCutsceneMgr::ms_running` | verified |
| `0x003D5AC4` | `CCutsceneMgr::ms_cutsceneProcessing` | verified |
| `0x003E9CB4` | `CTimer::m_UserPause` | verified |
| `0x003E9C68` | `CTimer::m_CodePause` | verified |

The timer pair is particularly strong: `CTimer::Initialise` clears the two words consecutively in the same semantic order, and `CGame::Process` uses them exactly as the user/code pause gates require.

## Main simulation cluster

The current PS2 order from `0x002FBC50` is represented directly in `src/CGameProcess.cpp`. Major recovered calls include:

`CClock::Update -> CWeather::Update -> CTheScripts::Process -> CScriptPaths::Update -> CCollision::Update? -> trains/planes/helis -> Darkel -> skidmarks/antennas/glass -> EventList -> Particle -> FireManager -> Population -> Weapon -> CarGenerators -> Cranes -> Clouds -> MovingThings -> WaterCannons -> UserDisplay -> CWorld::Process -> AccidentManager -> pickups -> Garages -> Rubbish -> SpecialFX -> [unknown 8-slot manager] -> TimeCycle -> CullZones -> Camera -> GameLogic -> Bridge -> Coronas/Shadows/Phone -> traffic tail`.

The load-transition flag at `FrontEndMenuManager + 0x47D` is retested throughout this chain. The lift preserves the exact groups skipped by the PS2 build rather than flattening them into unconditional calls.

## Corrected SpecialFX identity

An earlier provisional label assigned `CSpecialFX` to `0x00146FC0/0x00146FF0`. That hypothesis has been rejected.

The stronger binary match is:

| Address | Identity | Evidence |
|---|---|---|
| `0x00245E50` | `CSpecialFX::Init` | Large FX setup routine; initializes multiple child systems and reaches resources named `particle` / `smoketrail` |
| `0x00246438` | `CSpecialFX::Update` | Compact per-frame wrapper updating two subordinate FX systems, paired with `0x00245E50` |

`0x00146FC0/0x00146FF0` operate on eight fixed-size (`0x420`) slots. Their class identity is not proven, so they have deliberately returned to address-only names.

## Garages, TimeCycle and CullZones

Three more frame stages now have direct structural proof:

- `CGarages::Init = 0x00194B58`, `CGarages::Update = 0x00194CA0`. The update walks exactly 32 active `0x100`-byte slots.
- `CTimeCycle::Update = 0x001B7F30`. The heavy worker reads clock hour, computes `(hour + 1) % 24`, combines old/new weather and performs the large colour/fog interpolation. This PS2 build only enters the heavy worker when `(frameCounter & 0xF) == 0`.
- `CCullZones::Update = 0x003523B0`. It switches on `frameCounter & 7` with the distinctive `0/4`, `2`, `6` phase split for cull-zone, camera-attribute and player-attribute work.

The timecycle data argument in `CGame::Process` is loaded from `$gp - 0x2408`, i.e. the pointer stored at `0x003D4AE8`. This also corrects an earlier scaffold constant that was off by `0x10`.

## Remaining high-value unknowns

- `0x00146FF0`: eight-slot per-frame manager immediately after SpecialFX.
- `0x002D3630`: pre-streaming state/level helper.
- `0x0018FF80` / `0x0018F648`: helpers used only by the PS2 load-transition streaming path.
- `0x001FBF68`: custom/volatile-memory helper; behavior is understood better than its original method name.

These stay address-labelled until the ELF provides independent naming evidence.
