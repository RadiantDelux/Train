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

extern void Func_00205618();
extern void Func_002B5C08();
extern void Func_0028D860(void*);
extern void Func_002932F8(void*, void*);
extern void Func_001F2EA8();
extern void Func_001029A8();
extern void Func_00324B78();
extern void Func_00208278();
extern void Func_00358C10();
extern void Func_001FCEE0();
extern void Func_002F7A50();
extern void Func_002FA260();
extern void Func_00327078();
extern void Func_002D9D58();

// Original address: 0x002FAE40, end at 0x002FB380.
bool CGame_Initialise_002FAE40(const char* datFile)
{
    ResetLoadingScreenBar_001F50C8();
    UploadCollisionVUCode_0018A140(reinterpret_cast<void*>(0x003865F0), 0x40000040u);
    Strcpy_00374670(reinterpret_cast<char*>(0x00670A78), datFile);
    CPools_Initialise_0022E6D0();

    LoadingScreen_001F5270("Loading the Game", "Setup game variables", "loadsc0", nullptr);

    Func_00205618();
    Func_002B5C08();
    // ... camera/world/weather/collision/model setup ...
    Func_002D9D58();

    LoadingScreen_001F5270("Loading the Game", "Setup streaming", nullptr, nullptr);
    LoadingScreen_001F5270("Loading the Game", "Setup traffic lights", nullptr, nullptr);
    LoadingScreen_001F5270("Loading the Game", "Setup game variables", nullptr, nullptr);
    CPopulation_Initialise_002EC1A0();

    LoadingScreen_001F5270("Loading the Game", "Load scripts", nullptr, nullptr);
    CClock_Initialise_001F8760(1000);

    const bool loadingSave =
        *reinterpret_cast<std::uint8_t*>(0x00634A8D) != 0;
    const int scriptInitResult = CTheScripts_Init_00109BC8(loadingSave);

    LoadingScreen_001F5270("Loading the Game", "Setup game variables", nullptr, nullptr);
    LoadingScreen_001F5270("Loading the Game", "Start script", "loadsc1", nullptr);
    LoadingScreen_001F5270("Loading the Game", "Position dynamic objects", nullptr, nullptr);
    LoadingScreen_001F5270("Loading the Game", "Initialise vehicle paths", nullptr, nullptr);
    LoadingScreen_001F5270("Loading the Game", "Load scene", nullptr, nullptr);

    return scriptInitResult != 0;
}

// Contiguous lifecycle functions:
//   0x002FB388 CGame::ReInitGameObjectVariables
//   0x002FB600 CGame::ShutDownForRestart
//   0x002FB700 CGame::InitialiseWhenRestarting
//   0x002FBAF0 CGame::Process

} // namespace lcs
