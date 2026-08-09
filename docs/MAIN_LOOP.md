# Main loop recovery

This pass closes the primary PS2 gameplay lifecycle from `TheGame` into the
restartable frame loop.

## Recovered control flow

```text
main 0x001F3628
  -> Game_Bootstrap 0x001F3518
     -> TheGame 0x001F5FA8
        -> CTimer::Initialise 0x002B4C00
        -> CGame::Initialise 0x002FAE40
        -> boot/save probe
        -> outer restart loop
           -> CTimer::Update 0x002B4CF8
           -> TheGame_Frame 0x001F5BC0 (repeat while non-zero)
              -> CGame::Process 0x002FBAF0
              -> audio service
              -> world/effects/2D/menu/fade render path
              -> CTimer::Update
           -> CPad reset/stop-shake
           -> audio music mode disable
           -> CGame::ShutDownForRestart 0x002FB600
           -> CTimer::Stop 0x002B5098
           -> if restart/load:
                CGame::InitialiseWhenRestarting 0x002FB700
                audio music mode game
                loop
              else:
                audio terminate
```

## CGame lifecycle block

Function boundaries are now separated cleanly:

| Address | Recovered function |
|---|---|
| `0x002FAE40..0x002FB380` | `CGame::Initialise` |
| `0x002FB388..0x002FB5F8` | `CGame::ReInitGameObjectVariables` |
| `0x002FB600..0x002FB6F8` | `CGame::ShutDownForRestart` |
| `0x002FB700..0x002FBAE8` | `CGame::InitialiseWhenRestarting` |
| `0x002FBAF0..0x002FBED8` | `CGame::Process` |

`CGame::Initialise` is anchored by the call from `TheGame` with
`DATA\\GTA_VC.DAT`, the loading-stage strings, and already-identified calls to
`CPopulation::Initialise`, `CTheScripts::Init`, and `CClock::Initialise`.

## Init/update pairs recovered from CGame

The initialisation chain and per-frame chain provide strong structural pairs:

| Init | Update |
|---|---|
| `CTheScripts::Init` `0x00109BC8` | `CTheScripts::Process` `0x0010A288` |
| `CClock::Initialise` `0x001F8760` | `CClock::Update` `0x001F88C0` |
| `CEventList::Initialise` `0x0022B4D0` | `CEventList::Update` `0x0022B560` |
| `CHeli::InitHelis` `0x00256048` | `CHeli::UpdateHelis` `0x002560E8` |
| `CAntennas::Init` `0x0025A9E0` | `CAntennas::Update` `0x0025AA18` |
| `CPlane::InitPlanes` `0x00261BC0` | `CPlane::UpdatePlanes` `0x00261D10` |
| `CWeapon::InitialiseWeapons` `0x002A25D0` | `CWeapon::UpdateWeapons` `0x002A2618` |
| `CPopulation::Initialise` `0x002EC1A0` | `CPopulation::Update` `0x002EC290` |
| `CTrain::InitTrains` `0x00322848` | `CTrain::UpdateTrains` `0x00322DC8` |
| `CSkidmarks::Init` `0x0034F318` | `CSkidmarks::Update` `0x0034F3E0` |
| `CGlass::Init` `0x0011E1C0` | `CGlass::Update` `0x0011E260` |
| `CClouds::Init` `0x0016AFD0` | `CClouds::Update` `0x0016B080` |
| `CRubbish::Init` `0x001F1AA0` | `CRubbish::Update` `0x001F1C60` |
| `CDarkel::Init` `0x0023AEC8` | `CDarkel::Update` `0x0023AED0` |

These names are kept in `analysis/symbols.csv` with confidence/evidence.

## Render helpers

The inner frame loop now exposes a compact render cluster:

- `0x001F6138` — `RenderScene` (provisional/high confidence)
- `0x001F61C8` — `RenderEffects` (verified by its subsystem call cluster)
- `0x001F6198` — `RenderDebugShit` (production no-op candidate)
- `0x001F6338` — `Render2dStuff`
- `0x001F65C8` — `RenderMenus` (provisional)
- `0x001F4280` — `DoFade` (provisional)
- `0x001F66D0` — `Render2dStuffAfterFade` (provisional)
- `0x001F4C88` — `DoRWStuffEndOfFrame` (provisional)

## Boundary correction

`CClock::Initialise` begins at `0x001F8760`. The previously recorded
`0x001F8770` was an instruction inside the function that loads its diagnostic
string, not the function start.
