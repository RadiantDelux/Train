#include <cstdint>

// Semantic lift of the main simulation cluster inside CGame::Process.
// Original function: 0x002FBAF0..0x002FBEDC.
//
// This file follows the PS2 ELF, not a PC/PSP source ordering.  Names marked
// provisional are useful semantic labels but are not treated as original
// symbols until the local binary gives enough independent evidence.

namespace lcs {

extern void CSprite2d_SetRecipNearClip_00320A70(); // no-op in this build; provisional identity
extern void CSprite2d_InitPerFrame_00320B00();
extern void CFont_InitPerFrame_00164C08();
extern void CRecordDataForGame_Frame_00327080();
extern void CRecordDataForChase_Frame_00327090();
extern void CPad_DoCheats_001709E8();
extern void CClock_Update_001F88C0();
extern void CWeather_Update_00324C50();
extern void PushMemId_001CC5B8(void* stack, int id);
extern void PopMemId_001CC5C0(void* stack);
extern void CTheScripts_Process_0010A288();
extern void CScriptPaths_Update_001029F0();
extern void CCollision_Update_0013D040(); // provisional identity
extern void CTrain_UpdateTrains_00322DC8();
extern void CPlane_UpdatePlanes_00261D10();
extern void CHeli_UpdateHelis_002560E8();
extern void CDarkel_Update_0023AED0();
extern void CSkidmarks_Update_0034F3E0();
extern void CAntennas_Update_0025AA18();
extern void CGlass_Update_0011E260();
extern void CEventList_Update_0022B560();
extern void CParticle_Update_001CE1B0();
extern void CFireManager_Update_00306A50(void* manager); // provisional identity
extern void ProfilerMark_002B50D0();
extern void CPopulation_Update_002EC290(int generatePeds);
extern void ProfilerEnd_002B5040();
extern int  ProfilerCheck_002B5030();
extern void CWeapon_UpdateWeapons_002A2618();
extern void CTheCarGenerators_Process_003205F0();
extern void CCranes_UpdateCranes_0014CB78();
extern void CClouds_Update_0016B080();
extern void CMovingThings_Update_001013D0();
extern void CWaterCannons_Update_002CE178();      // provisional name
extern void CUserDisplay_Process_001FCF28();      // provisional name
extern void CWorld_Process_00176CE8();
extern void CAccidentManager_Update_003503C8(void* manager); // provisional identity
extern void CPacManPickups_Update_001CAF28();     // provisional/no-op in this build
extern void CPickups_Update_001C6D30();           // provisional name
extern void Func_00194CA0();
extern void CRubbish_Update_001F1C60();
extern void Func_00246438();
extern void CSpecialFX_Update_00146FF0();         // provisional name
extern void Func_001B7F30(void* object);
extern void Func_003523B0();
extern void TheCamera_Process_0028FAC8(void* camera); // high-confidence object identity
extern void CGameLogic_Update_00205640();         // provisional name
extern void CBridge_Update_0035AA38();             // provisional name
extern void CCoronas_DoSunAndMoon_00259B70();     // provisional name
extern void CCoronas_Update_00257F10();           // provisional name
extern void CShadows_UpdateStaticShadows_002DF2D8();    // provisional name
extern void CShadows_UpdatePermanentShadows_002DF360(); // provisional name
extern void CPhoneInfo_Update_00271678(void* phoneInfo);  // provisional name
extern void CCarCtrl_GenerateRandomCars_00212938();       // provisional name
extern void CRoadBlocks_GenerateRoadBlocks_003507B0();    // provisional name
extern void CCarCtrl_RemoveDistantCars_00215548();        // provisional name
extern void CCarCtrl_PoolPressureCleanup_002156B0();      // semantic name, exact original name unknown

static constexpr std::uintptr_t kMemIdStack = 0x00428110;
static constexpr std::uintptr_t kFrontendManager = 0x00634610;
static constexpr std::uintptr_t kTheCamera = 0x0044BBF0;
static constexpr std::uintptr_t kFireManager = 0x006329C0;
static constexpr std::uintptr_t kAccidentManager = 0x00648AD0;
static constexpr std::uintptr_t kPhoneInfo = 0x0044AB50;

static inline std::uint8_t ReadU8(std::uintptr_t address)
{
    return *reinterpret_cast<volatile std::uint8_t*>(address);
}

// FrontEndMenuManager + 0x47D.  This flag is consumed by CTheScripts::Init
// during game initialisation and gates several per-frame update groups.
static bool FrontendWantsLoad()
{
    return ReadU8(kFrontendManager + 0x47D) != 0;
}

// FrontEndMenuManager + 0x144.  Its exact field name is not yet proven; in the
// ELF it suppresses the normal camera process call at 0x002FBE3C.
static bool FrontendFlag144()
{
    return ReadU8(kFrontendManager + 0x144) != 0;
}

// Direct semantic lift of 0x002FBC50..0x002FBEC0.  The outer pause/frontend
// prelude at 0x002FBAF0..0x002FBC4C remains documented in the ASM until its
// state fields are named with the same confidence as the calls below.
void CGame_ProcessSimulationBody_002FBC50()
{
    auto* memIds = reinterpret_cast<void*>(kMemIdStack);

    CSprite2d_SetRecipNearClip_00320A70();
    CSprite2d_InitPerFrame_00320B00();
    CFont_InitPerFrame_00164C08();
    CRecordDataForGame_Frame_00327080();
    CRecordDataForChase_Frame_00327090();
    CPad_DoCheats_001709E8();
    CClock_Update_001F88C0();

    if (!FrontendWantsLoad())
        CWeather_Update_00324C50();

    PushMemId_001CC5B8(memIds, 16); // MEMID_SCRIPT
    CTheScripts_Process_0010A288();
    PopMemId_001CC5C0(memIds);

    // 0x2FBCC4 tests FrontEndMenuManager+0x47D again.  In a load transition,
    // path/collision/vehicle/fluff updates are deliberately skipped.
    if (!FrontendWantsLoad()) {
        CScriptPaths_Update_001029F0();
        CCollision_Update_0013D040();
        CTrain_UpdateTrains_00322DC8();
        CPlane_UpdatePlanes_00261D10();
        CHeli_UpdateHelis_002560E8();
        CDarkel_Update_0023AED0();
        CSkidmarks_Update_0034F3E0();
        CAntennas_Update_0025AA18();
        CGlass_Update_0011E260();
    }

    CEventList_Update_0022B560();
    CParticle_Update_001CE1B0();
    CFireManager_Update_00306A50(reinterpret_cast<void*>(kFireManager));

    if (!FrontendWantsLoad()) {
        ProfilerMark_002B50D0();
        CPopulation_Update_002EC290(1);
        ProfilerEnd_002B5040();
        // The original executes a debug-style invariant check here and BREAKs
        // if the helper returns zero.
        (void)ProfilerCheck_002B5030();
    }

    CWeapon_UpdateWeapons_002A2618();

    // The binary has an additional global guard around car-generator work.
    // We intentionally do not name that guard as "replay" until verified.
    if (*reinterpret_cast<volatile std::uint32_t*>(0x003D5AC0) == 0)
        CTheCarGenerators_Process_003205F0();

    CCranes_UpdateCranes_0014CB78();
    CClouds_Update_0016B080();
    CMovingThings_Update_001013D0();
    CWaterCannons_Update_002CE178();

    if (!FrontendWantsLoad())
        CUserDisplay_Process_001FCF28();

    PushMemId_001CC5B8(memIds, 2); // MEMID_WORLD
    CWorld_Process_00176CE8();
    PopMemId_001CC5C0(memIds);

    CAccidentManager_Update_003503C8(reinterpret_cast<void*>(kAccidentManager));
    CPacManPickups_Update_001CAF28();
    CPickups_Update_001C6D30();
    Func_00194CA0();
    CRubbish_Update_001F1C60();
    Func_00246438();
    CSpecialFX_Update_00146FF0();
    Func_001B7F30(reinterpret_cast<void*>(0x003D4AF8));
    Func_003523B0();

    if (!FrontendWantsLoad() && !FrontendFlag144())
        TheCamera_Process_0028FAC8(reinterpret_cast<void*>(kTheCamera));

    CGameLogic_Update_00205640();
    CBridge_Update_0035AA38();

    if (!FrontendWantsLoad()) {
        CCoronas_DoSunAndMoon_00259B70();
        CCoronas_Update_00257F10();
        CShadows_UpdateStaticShadows_002DF2D8();
        CShadows_UpdatePermanentShadows_002DF360();
        CPhoneInfo_Update_00271678(reinterpret_cast<void*>(kPhoneInfo));
    }

    PushMemId_001CC5B8(memIds, 17); // MEMID_CARS
    CCarCtrl_GenerateRandomCars_00212938();
    CRoadBlocks_GenerateRoadBlocks_003507B0();
    CCarCtrl_RemoveDistantCars_00215548();
    CCarCtrl_PoolPressureCleanup_002156B0();
    PopMemId_001CC5C0(memIds);
}

} // namespace lcs
