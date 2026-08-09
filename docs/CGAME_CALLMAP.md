# CGame direct-call map

This map is generated from the user-supplied ELF. Names marked **provisional** in `analysis/symbols.csv` are hypotheses; addresses and call sites are direct binary observations.

## CGame::Initialise

- Direct `jal` sites: **106**
- Targets currently named: **21**

| call site | target | recovered name | status |
|---|---|---|---|
| `0x002FAF0C` | `0x00205618` | `CGameLogic::InitAtStartOfGame` | provisional (0.94) |
| `0x002FAF5C` | `0x001FCEE0` | `CUserDisplay::Init` | provisional (0.95) |
| `0x002FAFAC` | `0x001CC7B8` | `CParticle::Initialise` | verified (0.99) |
| `0x002FAFE4` | `0x001C6CB0` | `CPickups::Init` | provisional (0.97) |
| `0x002FB09C` | `0x0022B4D0` | `CEventList::Initialise` | verified (1.00) |
| `0x002FB0E0` | `0x002A25D0` | `CWeapon::InitialiseWeapons` | verified (0.99) |
| `0x002FB11C` | `0x002EC1A0` | `CPopulation::Initialise` | verified (1.00) |
| `0x002FB13C` | `0x0034F318` | `CSkidmarks::Init` | verified (0.99) |
| `0x002FB144` | `0x0025A9E0` | `CAntennas::Init` | verified (0.98) |
| `0x002FB14C` | `0x0011E1C0` | `CGlass::Init` | verified (0.98) |
| `0x002FB178` | `0x001F8760` | `CClock::Initialise` | verified (1.00) |
| `0x002FB1A0` | `0x00109BC8` | `CTheScripts::Init` | verified (0.99) |
| `0x002FB1D0` | `0x00256048` | `CHeli::InitHelis` | verified (0.98) |
| `0x002FB1E8` | `0x0023AEC8` | `CDarkel::Init` | verified (0.98) |
| `0x002FB1F8` | `0x001F1AA0` | `CRubbish::Init` | verified (0.99) |
| `0x002FB200` | `0x0016AFD0` | `CClouds::Init` | verified (1.00) |
| `0x002FB210` | `0x00146FC0` | `CSpecialFX::Init` | provisional (0.97) |
| `0x002FB218` | `0x002CDFF8` | `CWaterCannons::Init` | provisional (0.97) |
| `0x002FB27C` | `0x00322848` | `CTrain::InitTrains` | verified (0.99) |
| `0x002FB284` | `0x00261BC0` | `CPlane::InitPlanes` | verified (1.00) |
| `0x002FB2B0` | `0x0010A288` | `CTheScripts::Process` | verified (0.99) |

## CGame::ReInitGameObjectVariables

- Direct `jal` sites: **55**
- Targets currently named: **18**

| call site | target | recovered name | status |
|---|---|---|---|
| `0x002FB3A4` | `0x001F8760` | `CClock::Initialise` | verified (1.00) |
| `0x002FB3AC` | `0x00205618` | `CGameLogic::InitAtStartOfGame` | provisional (0.94) |
| `0x002FB3E0` | `0x001FCEE0` | `CUserDisplay::Init` | provisional (0.95) |
| `0x002FB47C` | `0x0022B4D0` | `CEventList::Initialise` | verified (1.00) |
| `0x002FB484` | `0x002A25D0` | `CWeapon::InitialiseWeapons` | verified (0.99) |
| `0x002FB48C` | `0x002EC1A0` | `CPopulation::Initialise` | verified (1.00) |
| `0x002FB4C4` | `0x0025A9E0` | `CAntennas::Init` | verified (0.98) |
| `0x002FB4CC` | `0x0011E1C0` | `CGlass::Init` | verified (0.98) |
| `0x002FB4F4` | `0x00109BC8` | `CTheScripts::Init` | verified (0.99) |
| `0x002FB50C` | `0x002B4C00` | `CTimer::Initialise` | verified (1.00) |
| `0x002FB51C` | `0x00256048` | `CHeli::InitHelis` | verified (0.98) |
| `0x002FB52C` | `0x0023AEC8` | `CDarkel::Init` | verified (0.98) |
| `0x002FB534` | `0x001C6CB0` | `CPickups::Init` | provisional (0.97) |
| `0x002FB55C` | `0x00146FC0` | `CSpecialFX::Init` | provisional (0.97) |
| `0x002FB564` | `0x002CDFF8` | `CWaterCannons::Init` | provisional (0.97) |
| `0x002FB574` | `0x001CC6B8` | `CParticleMgr_Initialise` | provisional (0.95) |
| `0x002FB590` | `0x00261BC0` | `CPlane::InitPlanes` | verified (1.00) |
| `0x002FB5A0` | `0x00322848` | `CTrain::InitTrains` | verified (0.99) |

## CGame::ShutDownForRestart

- Direct `jal` sites: **20**
- Targets currently named: **0**

| call site | target | recovered name | status |
|---|---|---|---|

## CGame::InitialiseWhenRestarting

- Direct `jal` sites: **43**
- Targets currently named: **17**

| call site | target | recovered name | status |
|---|---|---|---|
| `0x002FB770` | `0x002B4C00` | `CTimer::Initialise` | verified (1.00) |
| `0x002FB7D0` | `0x001F4C88` | `DoRWStuffEndOfFrame` | provisional (0.96) |
| `0x002FB7F8` | `0x001F4C88` | `DoRWStuffEndOfFrame` | provisional (0.96) |
| `0x002FB890` | `0x002FB388` | `CGame::ReInitGameObjectVariables` | verified (0.99) |
| `0x002FB8DC` | `0x00322848` | `CTrain::InitTrains` | verified (0.99) |
| `0x002FB8E4` | `0x00261BC0` | `CPlane::InitPlanes` | verified (1.00) |
| `0x002FB90C` | `0x001F4C88` | `DoRWStuffEndOfFrame` | provisional (0.96) |
| `0x002FB934` | `0x001F4C88` | `DoRWStuffEndOfFrame` | provisional (0.96) |
| `0x002FB990` | `0x001F4C88` | `DoRWStuffEndOfFrame` | provisional (0.96) |
| `0x002FB9B8` | `0x001F4C88` | `DoRWStuffEndOfFrame` | provisional (0.96) |
| `0x002FBA0C` | `0x001F4C88` | `DoRWStuffEndOfFrame` | provisional (0.96) |
| `0x002FBA34` | `0x001F4C88` | `DoRWStuffEndOfFrame` | provisional (0.96) |
| `0x002FBA6C` | `0x002FB600` | `CGame::ShutDownForRestart` | verified (0.99) |
| `0x002FBA74` | `0x002B5098` | `CTimer::Stop` | verified (0.99) |
| `0x002FBA7C` | `0x002B4C00` | `CTimer::Initialise` | verified (1.00) |
| `0x002FBA84` | `0x002FB388` | `CGame::ReInitGameObjectVariables` | verified (0.99) |
| `0x002FBA9C` | `0x002B4CF8` | `CTimer::Update` | verified (0.99) |

## CGame::Process

- Direct `jal` sites: **77**
- Targets currently named: **21**

| call site | target | recovered name | status |
|---|---|---|---|
| `0x002FBB24` | `0x0010A288` | `CTheScripts::Process` | verified (0.99) |
| `0x002FBC80` | `0x001F88C0` | `CClock::Update` | verified (0.99) |
| `0x002FBCB4` | `0x0010A288` | `CTheScripts::Process` | verified (0.99) |
| `0x002FBCE0` | `0x00322DC8` | `CTrain::UpdateTrains` | verified (0.99) |
| `0x002FBCE8` | `0x00261D10` | `CPlane::UpdatePlanes` | verified (0.99) |
| `0x002FBCF0` | `0x002560E8` | `CHeli::UpdateHelis` | verified (0.98) |
| `0x002FBCF8` | `0x0023AED0` | `CDarkel::Update` | verified (0.98) |
| `0x002FBD00` | `0x0034F3E0` | `CSkidmarks::Update` | verified (0.99) |
| `0x002FBD08` | `0x0025AA18` | `CAntennas::Update` | verified (0.98) |
| `0x002FBD10` | `0x0011E260` | `CGlass::Update` | verified (0.98) |
| `0x002FBD18` | `0x0022B560` | `CEventList::Update` | verified (0.99) |
| `0x002FBD20` | `0x001CE1B0` | `CParticle::Update` | verified (0.99) |
| `0x002FBD48` | `0x002EC290` | `CPopulation::Update` | verified (0.99) |
| `0x002FBD68` | `0x002A2618` | `CWeapon::UpdateWeapons` | verified (0.99) |
| `0x002FBD90` | `0x0016B080` | `CClouds::Update` | verified (0.99) |
| `0x002FBDA0` | `0x002CE178` | `CWaterCannons::Update` | provisional (0.97) |
| `0x002FBDB4` | `0x001FCF28` | `CUserDisplay::Process` | provisional (0.95) |
| `0x002FBDEC` | `0x001C6D30` | `CPickups::Update` | provisional (0.97) |
| `0x002FBDFC` | `0x001F1C60` | `CRubbish::Update` | verified (0.99) |
| `0x002FBE0C` | `0x00146FF0` | `CSpecialFX::Update` | provisional (0.97) |
| `0x002FBE44` | `0x00205640` | `CGameLogic::Update` | provisional (0.94) |
