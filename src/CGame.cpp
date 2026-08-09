#include <cstdint>

// High-level semantic reconstruction of the CGame lifecycle region.
// This file intentionally records only names/ordering that are supported by
// the PS2 binary. Unknown calls remain address-labelled.

namespace lcs {

extern void ResetLoadingScreenBar_001F50C8();
extern void UploadCollisionVUCode_0018A140(void* code, unsigned flags); // provisional
extern char* Strcpy_00374670(char* dst, const char* src);
extern void CPools_Initialise_0022E6D0();
extern void LoadingScreen_001F5270(const char*, const char*, const char*, void*);
extern void CPopulation_Initialise_002EC1A0();
extern int  CTheScripts_Init_00109BC8(bool loadingSave);
extern void CClock_Initialise_001F8760(int millisecondsPerGameMinute);
extern void CTimer_Initialise_002B4C00();
extern void PushMemId_001CC5B8(void* stack, int id);
extern void PopMemId_001CC5C0(void* stack);
extern void CWorld_Initialise_00173338();
extern void CParticle_Initialise_001CC7B8();
extern void CCarCtrl_Init_0021A148();
extern void CPickups_Init_001C6CB0(); // provisional name
extern void CTheCarGenerators_Init_00320760();

// Many subsystem names below are still intentionally unresolved. Their exact
// call order is preserved in analysis/2fae40_2fb600.asm.
extern void Func_00205618();
extern void Func_002B5C08();
extern void Func_0028D860(void*);
extern void Func_002932F8(void*, void*);
extern void Func_001F2EA8();
extern void CScriptPaths_Init_001029A8();
extern void CWeather_Init_00324B78();
extern void Func_00208278();
extern void Func_00358C10();
extern void CUserDisplay_Init_001FCEE0(); // provisional name
extern void Func_002F7A50();
extern void Func_002FA260();
extern void CRecordDataForGame_Init_00327078();
extern void Func_002D9D58();

// Original address: 0x002FAE40, end at 0x002FB380.
bool CGame_Initialise_002FAE40(const char* datFile)
{
    // The first part performs PS2/VU setup, copies the DAT filename and
    // initializes the object pools before entering the subsystem chain.
    ResetLoadingScreenBar_001F50C8();
    UploadCollisionVUCode_0018A140(reinterpret_cast<void*>(0x003865F0), 0x40000040u);
    Strcpy_00374670(reinterpret_cast<char*>(0x00670A78), datFile);
    CPools_Initialise_0022E6D0();

    // The original contains a long, linear initialization pipeline.  We keep
    // its verified stage boundaries here and leave unresolved calls in the ASM
    // listing until each target is individually proven.
    LoadingScreen_001F5270("Loading the Game", "Setup game variables", "loadsc0", nullptr);

    Func_00205618();
    Func_002B5C08();
    auto* theCamera = reinterpret_cast<void*>(0x0044BBF0);
    Func_0028D860(theCamera);
    Func_002932F8(theCamera, *reinterpret_cast<void**>(0x003E9920));
    Func_001F2EA8();
    CScriptPaths_Init_001029A8();
    CWeather_Init_00324B78();
    Func_00208278();
    Func_00358C10();
    CUserDisplay_Init_001FCEE0();
    Func_002F7A50();
    Func_002FA260();
    CRecordDataForGame_Init_00327078();
    Func_002D9D58();

    auto* memIds = reinterpret_cast<void*>(0x00428110);
    PushMemId_001CC5B8(memIds, 2); // MEMID_WORLD
    CWorld_Initialise_00173338();
    PopMemId_001CC5C0(memIds);

    PushMemId_001CC5B8(memIds, 12); // particle/texture allocation group
    CParticle_Initialise_001CC7B8();
    PopMemId_001CC5C0(memIds);

    PushMemId_001CC5B8(memIds, 17); // MEMID_CARS
    CCarCtrl_Init_0021A148();
    PopMemId_001CC5C0(memIds);

    PushMemId_001CC5B8(memIds, 5);
    CPickups_Init_001C6CB0();
    CTheCarGenerators_Init_00320760();
    PopMemId_001CC5C0(memIds);

    // Model/path setup continues through 0x002FB03C. The two-entry cleanup
    // loop at 0x002FB008 is retained in the raw assembly until its object type
    // is identified.

    LoadingScreen_001F5270("Loading the Game", "Setup streaming", nullptr, nullptr);
    // Streaming, initial models, animations, peds, routes, renderer, radar and
    // weapons are initialized between 0x002FB06C and 0x002FB0E4. The matching
    // per-frame CStreaming::Update is now verified at 0x0018AE68.

    LoadingScreen_001F5270("Loading the Game", "Setup traffic lights", nullptr, nullptr);
    // Traffic lights / roadblocks. 0x003506F0 is the high-confidence
    // CRoadBlocks::Init candidate paired with the frame-tail generator.

    LoadingScreen_001F5270("Loading the Game", "Setup game variables", nullptr, nullptr);
    CPopulation_Initialise_002EC1A0();

    // Coronas, shadows, weapon effects, skidmarks, antennas, glass, phone info.
    // The exact calls are retained in the assembly listing.

    LoadingScreen_001F5270("Loading the Game", "Load scripts", nullptr, nullptr);
    CClock_Initialise_001F8760(1000);

    // The script-memory block is bracketed by the binary's MEMID push/pop.
    // loadingSave is derived from FrontEndMenuManager+0x47D.
    // Additional pre/post-script calls remain unresolved for now.
    const bool loadingSave =
        *reinterpret_cast<std::uint8_t*>(0x00634A8D) != 0; // FrontEnd + 0x47D
    const int scriptInitResult = CTheScripts_Init_00109BC8(loadingSave);

    LoadingScreen_001F5270("Loading the Game", "Setup game variables", nullptr, nullptr);
    // Heli/cranes/moving things/stats/rubbish/clouds/special FX/etc.
    // CCranes::InitCranes = 0x0014C350 (surviving debug diagnostic).
    // CMovingThings::Init = 0x00100B00; its frame update is 0x001013D0.

    LoadingScreen_001F5270("Loading the Game", "Start script", "loadsc1", nullptr);
    LoadingScreen_001F5270("Loading the Game", "Position dynamic objects", nullptr, nullptr);
    LoadingScreen_001F5270("Loading the Game", "Initialise vehicle paths", nullptr, nullptr);

    // Trains, planes, credits/replay and script startup follow. The build emits
    // Loading #1..#5 diagnostics around these final operations.
    LoadingScreen_001F5270("Loading the Game", "Load scene", nullptr, nullptr);

    // The actual MIPS returns the value left by the script-init path in s5;
    // current evidence shows this is used as a success value by TheGame.
    return scriptInitResult != 0;
}

// The contiguous lifecycle functions are now structurally identified:
//   0x002FB388 CGame::ReInitGameObjectVariables
//   0x002FB600 CGame::ShutDownForRestart
//   0x002FB700 CGame::InitialiseWhenRestarting
//   0x002FBAF0 CGame::Process
// Their detailed bodies will be lifted as subsystem symbols are recovered.

} // namespace lcs
