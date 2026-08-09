# `CGame::Process` reconstruction

Binary range: `0x002FBAF0..0x002FBEDC`.

The function is split conceptually into two parts:

1. `0x002FBAF0..0x002FBC4C`: load-transition, pad, cutscene/frontend, streaming and pause prelude. Calls are mostly mapped, but several state fields remain address-labelled until their semantics are proven from the PS2 binary.
2. `0x002FBC50..0x002FBEC0`: main simulation cluster. `src/CGameProcess.cpp` now lifts both the direct-call order **and the observed load-transition guards**.

## Newly recovered core subsystems

| Address | Semantic identity | Confidence |
|---|---|---|
| `0x001029A8` | `CScriptPaths::Init` | verified |
| `0x001029F0` | `CScriptPaths::Update` | verified |
| `0x00324B78` | `CWeather::Init` | verified |
| `0x00324C50` | `CWeather::Update` | verified |
| `0x00173338` | `CWorld::Initialise` | verified |
| `0x00176CE8` | `CWorld::Process` | verified |
| `0x0018AE68` | `CStreaming::Update` | verified |
| `0x0021A148` | `CCarCtrl::Init` | verified |
| `0x0021A218` | `CCarCtrl::ReInit` | verified |
| `0x0016F890` | `CPad::UpdatePads` | verified |
| `0x001709E8` | `CPad::DoCheats` | verified |
| `0x00320B00` | `CSprite2d::InitPerFrame` | verified |
| `0x00164C08` | `CFont::InitPerFrame` | verified |
| `0x00327078/80` | `CRecordDataForGame::Init / frame hook` | verified stub pair |
| `0x00327088/90` | `CRecordDataForChase::Init / frame hook` | verified stub pair |

`CScriptPaths` is particularly distinctive in this build: the manager consists of three 52-byte entries and its subordinate setup path references `data\\paths\\spath%d.dat`.

`CWorld::Process` is also structurally strong: it walks entity/list data and performs virtual dispatch while the caller brackets it with memory ID 2 (`MEMID_WORLD`).

`CStreaming::Update` sits in the streaming-heavy `0x18xxxx` region and is called by the frame prelude immediately before the non-paused simulation body.

## PS2-specific ordering

The observed non-load-transition sequence around scripts is:

`CClock::Update -> CWeather::Update -> CTheScripts::Process -> CScriptPaths::Update -> CCollision::Update? -> CTrain::UpdateTrains -> ...`

The `CCollision::Update` label at `0x0013D040` is still marked provisional.  The surrounding ordering differs from some public reconstruction trees, so this project keeps the ELF ordering as authoritative.

## Load-transition guards

`FrontEndMenuManager + 0x47D` is repeatedly tested throughout the frame.  When set, the ELF skips several groups including weather, script paths/collision/vehicle fluff, population, user display, camera, coronas/shadows and phone updates.  `src/CGameProcess.cpp` now preserves those branches instead of presenting the whole call list as unconditional.

## Traffic tail

The final `MEMID_CARS` block is now structurally mapped as:

`CCarCtrl::GenerateRandomCars? -> CRoadBlocks::GenerateRoadBlocks? -> CCarCtrl::RemoveDistantCars? -> CCarCtrl pool-pressure cleanup`

The first three names are high-confidence lifecycle/behavior identifications; the final helper has a descriptive semantic name because its exact original method name is not yet proven.  Its body contains the surviving debug diagnostic about removing the nearest car when the pool is full.

Unknown functions remain address-labelled intentionally.  A plausible name is not promoted to a verified symbol until the PS2 binary supplies independent evidence.
