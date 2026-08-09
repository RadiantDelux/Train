#include <cstdint>

// Semantic lift of the main simulation cluster inside CGame::Process.
// Original function: 0x002FBAF0..0x002FBEDC.
//
// This file follows the PS2 ELF, not a PC/PSP source ordering.  Names marked
// provisional are useful semantic labels but are not treated as original
// symbols until the local binary gives enough independent evidence.

namespace lcs {

extern void CTheScripts_StartTestScript_0010A628();
extern void CPad_UpdatePads_0016F890();
extern void CStreaming_LoadScene_0018FA18(void* position);
extern void Func_002FBEE0(); // exact no-op in this build
extern void Func_0018FF80(int arg0, void* arg1, int arg2);
extern void Func_0018F648(int arg0);
extern void Func_001FBF68(void* manager, int mode); // volatile-RAM/custom-allocator helper
extern void CCutsceneMgr_Update_0022DAC0();
extern void CMenuManager_Process_0033F3A8(void* menuManager);
extern void Func_002D3630(void* outputOrState); // pre-streaming state/level helper, exact identity unknown
extern void CStreaming_Update_0018AE68();

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
extern void CGarages_Update_00194CA0();
extern void CRubbish_Update_001F1C60();
extern void CSpecialFX_Update_00246438();
extern void Func_00146FF0(); // unknown eight-slot manager; previous CSpecialFX label was rejected
extern void CTimeCycle_Update_001B7F30(void* timecycleData);
extern void CCullZones_Update_003523B0();
extern void TheCamera_Process_0028FAC8(void* camera); // high-confidence object identity
extern void CGameLogic_Update_00205640();
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
static constexpr std::uintptr_t kVolatileRamManager = 0x0042A8A0;
static constexpr std::uintptr_t kLoadStateObjectPtr = 0x003D0CC8;
static constexpr std::uintptr_t kStreamingLoadToken = 0x003E84A8;
static constexpr std::uintptr_t kPs2LoadScratchFlag = 0x00433D19;
static constexpr std::uintptr_t kCutsceneRunning = 0x003D5AC0;
static constexpr std::uintptr_t kCutsceneProcessing = 0x003D5AC4;
static constexpr std::uintptr_t kTimerCodePause = 0x003E9C68;
static constexpr std::uintptr_t kTimerUserPause = 0x003E9CB4;
static constexpr std::uintptr_t kPreStreamingStatePtr = 0x003D7750; // $gp + 0x860
static constexpr std::uintptr_t kTimeCycleDataPtr = 0x003D4AE8;    // $gp - 0x2408
static constexpr std::uintptr_t kPerFrameUnknownReset = 0x003D68E4; // $gp - 0x60C

static inline std::uint8_t ReadU8(std::uintptr_t address)
{
    return *reinterpret_cast<volatile std::uint8_t*>(address);
}

static inline std::uint32_t ReadU32(std::uintptr_t address)
{
    return *reinterpret_cast<volatile std::uint32_t*>(address);
}

static inline void* ReadPtr(std::uintptr_t address)
{
    return reinterpret_cast<void*>(static_cast<std::uintptr_t>(ReadU32(address)));
}

static inline void WriteU8(std::uintptr_t address, std::uint8_t value)
{
    *reinterpret_cast<volatile std::uint8_t*>(address) = value;
}

static inline void WriteU32(std::uintptr_t address, std::uint32_t value)
{
    *reinterpret_cast<volatile std::uint32_t*>(address) = value;
}

static bool CutsceneIsRunning()
{
    return ReadU32(kCutsceneRunning) != 0;
}

static bool CutsceneIsProcessing()
{
    return ReadU32(kCutsceneProcessing) != 0;
}

static bool TimerCodePaused()
{
    return ReadU32(kTimerCodePause) != 0;
}

static bool TimerUserPaused()
{
    return ReadU32(kTimerUserPause) != 0;
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

// Direct semantic lift of the non-paused simulation body 0x002FBC50..0x002FBEC0.
// Called by the full outer frame lift below after the pause/frontend/streaming gates.
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

    // Exact !CCutsceneMgr::IsRunning() gate from the PS2 ELF.
    if (!CutsceneIsRunning())
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
    CGarages_Update_00194CA0();
    CRubbish_Update_001F1C60();
    CSpecialFX_Update_00246438();
    Func_00146FF0(); // still intentionally unnamed
    CTimeCycle_Update_001B7F30(ReadPtr(kTimeCycleDataPtr));
    CCullZones_Update_003523B0();

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

// Semantic lift of the complete outer frame routine.  Unnamed helpers are
// preserved at their original addresses rather than guessed from another port.
void CGame_Process_002FBAF0()
{
    // PS2 load-transition path.  This path is present before the normal pad /
    // frontend / streaming prelude and deliberately re-enters script+camera
    // processing while loading a scene.
    if (FrontendWantsLoad()) {
        CTheScripts_StartTestScript_0010A628();
        CTheScripts_Process_0010A288();
        TheCamera_Process_0028FAC8(reinterpret_cast<void*>(kTheCamera));
        CStreaming_LoadScene_0018FA18(reinterpret_cast<void*>(kTheCamera + 0x30));
        Func_002FBEE0();

        auto* loadState = ReadPtr(kLoadStateObjectPtr);
        if (ReadU8(reinterpret_cast<std::uintptr_t>(loadState) + 0x0C) != 1) {
            Func_0018FF80(0, reinterpret_cast<void*>(kStreamingLoadToken), 5);
            Func_0018F648(0);
        }

        WriteU8(kPs2LoadScratchFlag, 0);
        TheCamera_Process_0028FAC8(reinterpret_cast<void*>(kTheCamera));
        CStreaming_LoadScene_0018FA18(reinterpret_cast<void*>(kTheCamera + 0x30));
        WriteU8(kFrontendManager + 0x47D, 0);
    }

    CPad_UpdatePads_0016F890();

    // This exactly mirrors the two field checks around 0x0042A8A0.  The
    // object is part of the PS2 custom/volatile-memory path; the precise
    // original helper name is not yet proven.
    if (ReadU32(kVolatileRamManager + 0x12C) == 1 &&
        ReadU32(kVolatileRamManager + 0x130) == 0) {
        Func_001FBF68(reinterpret_cast<void*>(kVolatileRamManager), 0);
    }

    CCutsceneMgr_Update_0022DAC0();

    if (!CutsceneIsProcessing() && !TimerCodePaused())
        CMenuManager_Process_0033F3A8(reinterpret_cast<void*>(kFrontendManager));

    if (!FrontendWantsLoad()) {
        Func_002D3630(ReadPtr(kPreStreamingStatePtr));
        ProfilerMark_002B50D0();
        CStreaming_Update_0018AE68();
        ProfilerMark_002B50D0();
    }

    // The delay slot at 0x002FBC3C clears this word even on a paused return.
    WriteU32(kPerFrameUnknownReset, 0);
    if (TimerUserPaused() || TimerCodePaused())
        return;

    CGame_ProcessSimulationBody_002FBC50();
}

} // namespace lcs
