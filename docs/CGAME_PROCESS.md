# `CGame::Process` reconstruction

Binary range: `0x002FBAF0..0x002FBED8`.

The function is now split conceptually into two parts:

1. `0x002FBAF0..0x002FBC4C`: pad/cutscene/frontend/streaming/pause prelude. The direct calls are mapped, but several conditions and object identities are still intentionally unresolved.
2. `0x002FBC50..0x002FBEC0`: main simulation update cluster. A semantic lift lives in `src/CGameProcess.cpp` and preserves the observed direct-call order.

## High-confidence update families

| Init | Update/Process | Render | family |
|---|---|---|---|
| `0x001CC7B8` | `0x001CE1B0` | `0x001CF2A0` | `CParticle` |
| `0x002CDFF8` | `0x002CE178` | `0x002CE1E8` | `CWaterCannons` *(provisional)* |
| `0x001FCEE0` | `0x001FCF28` | — | `CUserDisplay` *(provisional)* |
| `0x001C6CB0` | `0x001C6D30` | — | `CPickups` *(provisional)* |
| `0x00205618` | `0x00205640` | — | `CGameLogic` *(provisional)* |

`CParticle` is the strongest new identification: its initializer is inside the particle memory block, invokes the particle manager initialization and resource setup, while its update and render targets occur in the expected frame/render clusters.

The WaterCannons/UserDisplay/Pickups/GameLogic names are kept provisional because their addresses are inferred from multiple lifecycle pairings and architecture/order evidence rather than a surviving diagnostic symbol.

## Verified central sequence

The non-paused simulation body contains this directly observed chain:

`CClock::Update -> CTheScripts::Process -> CTrain::UpdateTrains -> CPlane::UpdatePlanes -> CHeli::UpdateHelis -> CDarkel::Update -> CSkidmarks::Update -> CAntennas::Update -> CGlass::Update -> CEventList::Update -> CParticle::Update -> CPopulation::Update -> CWeapon::UpdateWeapons -> CClouds::Update -> ... -> CRubbish::Update -> CSpecialFX::Update`

Unknown functions remain address-labelled in `src/CGameProcess.cpp`; this is intentional so that later class reconstruction cannot silently inherit a bad guess.
