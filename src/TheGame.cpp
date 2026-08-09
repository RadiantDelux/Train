// Semantic reconstruction of the PS2 main game loop.
// Original function: 0x001F5FA8
//
// Goal: preserve the observable control flow of this build while keeping
// uncertain globals/helpers address-labelled until their type is proven.

#include <cstddef>
#include <cstdint>

namespace lcs {

extern void DebugPrintf_00104530(const char* text);
extern void DebugPrint_00104BA0(const char* text);
extern void DebugPrintf2_00104BA0(const char* format, const char* arg);
extern void SetMemContext_001F5268(int id);
extern void PushMemId_001CC5B8(void* stack, int id);
extern void PopMemId_001CC5C0(void* stack);

extern void CTimer_Initialise_002B4C00();
extern void CTimer_Update_002B4CF8();
extern void CTimer_Stop_002B5098();

extern bool CGame_Initialise_002FAE40(const char* datFile);
extern void CGame_ShutDownForRestart_002FB600();
extern void CGame_InitialiseWhenRestarting_002FB700();

extern void LoadingScreen_001F5270(const char* line1, const char* line2,
                                   const char* splash, void* unknown);
extern void ProbeRecentSave_001F5998();
extern int  RunGameFrame_001F5BC0();
extern void PrepareRestart_002F7958();
extern void CPad_ResetCheats_00172838();
extern void CPad_StopPadsShaking_00170B68();
extern void DMAudio_ChangeMusicMode_002A2238(void* audio, int mode);
extern void DMAudio_Terminate_002A1DD8(void* audio);
extern const char* GetLevelSplash_001F50B0(int level);
extern void* LoadSplash_001F4DF8(const char* name);

struct FrontEndFlagsView {
    std::uint8_t opaque000[0x144];
    std::uint8_t wantToRestart;
    std::uint8_t opaque145[0x338];
    std::uint8_t wantToLoad;
};

static_assert(offsetof(FrontEndFlagsView, wantToRestart) == 0x144);
static_assert(offsetof(FrontEndFlagsView, wantToLoad) == 0x47D);

static auto& FrontEndFlags()
{
    return *reinterpret_cast<FrontEndFlagsView*>(0x00634610);
}

static auto& FoundRecentSavedGameWantToLoad()
{
    return *reinterpret_cast<std::uint32_t*>(0x003E82DC);
}

static auto& FoundGameToLoad()
{
    return *reinterpret_cast<std::uint32_t*>(0x003D82DC);
}

static auto& CurrentLevel()
{
    return *reinterpret_cast<std::uint32_t*>(0x003D9C54);
}

static auto* const gMemIdStack = reinterpret_cast<void*>(0x00428110);
static auto* const gDMAudio    = reinterpret_cast<void*>(0x003E99E0);

void TheGame_001F5FA8()
{
    SetMemContext_001F5268(0);
    DebugPrintf_00104530("Into TheGame!!!\n");
    PushMemId_001CC5B8(gMemIdStack, 1);
    CTimer_Initialise_002B4C00();

    DebugPrint_00104BA0("start game init\n");
    CGame_Initialise_002FAE40("DATA\\GTA_VC.DAT");
    DebugPrint_00104BA0("game init DONE!\n");

    LoadingScreen_001F5270("Starting Game", nullptr, nullptr, nullptr);
    ProbeRecentSave_001F5998();

    if (FoundRecentSavedGameWantToLoad() != 0)
        LoadSplash_001F4DF8(GetLevelSplash_001F50B0(static_cast<int>(CurrentLevel())));

    for (;;) {
        CTimer_Update_002B4CF8();
        PrepareRestart_002F7958();
        DebugPrintf2_00104BA0("****PS2 PLACEHOLDER : %s****\n", "____RestartGame:");

        while (RunGameFrame_001F5BC0() != 0) {
        }

        CPad_ResetCheats_00172838();
        CPad_StopPadsShaking_00170B68();
        DMAudio_ChangeMusicMode_002A2238(gDMAudio, 3);
        CGame_ShutDownForRestart_002FB600();
        CTimer_Stop_002B5098();

        const bool restartRequested = FrontEndFlags().wantToRestart == 1;
        const bool loadRequested = FoundGameToLoad() == 1;
        if (!restartRequested && !loadRequested)
            break;

        if (FoundRecentSavedGameWantToLoad() == 1) {
            FrontEndFlags().wantToLoad = 1;
            FrontEndFlags().wantToRestart = 1;
        }

        CGame_InitialiseWhenRestarting_002FB700();
        FrontEndFlags().wantToRestart = 0;
        DMAudio_ChangeMusicMode_002A2238(gDMAudio, 1);
    }

    DMAudio_Terminate_002A1DD8(gDMAudio);
}

} // namespace lcs
