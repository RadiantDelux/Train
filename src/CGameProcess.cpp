#include <cstdint>

// Semantic lift of the main simulation body inside CGame::Process.
// Original CGame::Process: 0x002FBAF0..0x002FBED8.

namespace lcs {

extern void Func_00320A70();
extern void Func_00320B00();
extern void Func_00164C08();
extern void Func_00327080();
extern void Func_00327090();
extern void Func_001709E8();
extern void CClock_Update_001F88C0();
extern void Func_00324C50();
extern void PushMemId_001CC5B8(void* stack, int id);
extern void PopMemId_001CC5C0(void* stack);
extern void CTheScripts_Process_0010A288();
extern void Func_001029F0();
extern void Func_0013D040();
extern void CTrain_UpdateTrains_00322DC8();
extern void CPlane_UpdatePlanes_00261D10();
extern void CHeli_UpdateHelis_002560E8();
extern void CDarkel_Update_0023AED0();
extern void CSkidmarks_Update_0034F3E0();
extern void CAntennas_Update_0025AA18();
extern void CGlass_Update_0011E260();
extern void CEventList_Update_0022B560();
extern void CParticle_Update_001CE1B0();
extern void Func_00306A50(void* object);
extern void Func_002B50D0();
extern void CPopulation_Update_002EC290(int generatePeds);
extern void Func_002B5040();
extern int  Func_002B5030();
extern void CWeapon_UpdateWeapons_002A2618();
extern void Func_003205F0();
extern void Func_0014CB78();
extern void CClouds_Update_0016B080();
extern void Func_001013D0();
extern void CWaterCannons_Update_002CE178();
extern void CUserDisplay_Process_001FCF28();
extern void Func_00176CE8();
extern void Func_003503C8(void* object);
extern void Func_001CAF28();
extern void CPickups_Update_001C6D30();
extern void Func_00194CA0();
extern void CRubbish_Update_001F1C60();
extern void Func_00246438();
extern void CSpecialFX_Update_00146FF0();
extern void Func_001B7F30(void* object);
extern void Func_003523B0();
extern void Func_0028FAC8(void* object);
extern void CGameLogic_Update_00205640();
extern void Func_0035AA38();
extern void Func_00259B70();
extern void Func_00257F10();
extern void Func_002DF2D8();
extern void Func_002DF360();
extern void Func_00271678(void* object);
extern void Func_00212938();
extern void Func_003507B0();
extern void Func_00215548();
extern void Func_002156B0();

static constexpr std::uintptr_t kMemIdStack = 0x00428110;

void CGame_ProcessSimulationBody_002FBC50()
{
    Func_00320A70();
    Func_00320B00();
    Func_00164C08();
    Func_00327080();
    Func_00327090();
    Func_001709E8();
    CClock_Update_001F88C0();
    Func_00324C50();

    auto* memIds = reinterpret_cast<void*>(kMemIdStack);
    PushMemId_001CC5B8(memIds, 16);
    CTheScripts_Process_0010A288();
    PopMemId_001CC5C0(memIds);

    Func_001029F0();
    Func_0013D040();
    CTrain_UpdateTrains_00322DC8();
    CPlane_UpdatePlanes_00261D10();
    CHeli_UpdateHelis_002560E8();
    CDarkel_Update_0023AED0();
    CSkidmarks_Update_0034F3E0();
    CAntennas_Update_0025AA18();
    CGlass_Update_0011E260();
    CEventList_Update_0022B560();
    CParticle_Update_001CE1B0();

    Func_00306A50(reinterpret_cast<void*>(0x006329C0));

    Func_002B50D0();
    CPopulation_Update_002EC290(1);
    Func_002B5040();
    (void)Func_002B5030();

    CWeapon_UpdateWeapons_002A2618();
    Func_003205F0();
    Func_0014CB78();
    CClouds_Update_0016B080();
    Func_001013D0();
    CWaterCannons_Update_002CE178();
    CUserDisplay_Process_001FCF28();

    PushMemId_001CC5B8(memIds, 2);
    Func_00176CE8();
    PopMemId_001CC5C0(memIds);

    Func_003503C8(reinterpret_cast<void*>(0x00648AD0));
    Func_001CAF28();
    CPickups_Update_001C6D30();
    Func_00194CA0();
    CRubbish_Update_001F1C60();
    Func_00246438();
    CSpecialFX_Update_00146FF0();
    Func_001B7F30(reinterpret_cast<void*>(0x003D4AF8));
    Func_003523B0();

    Func_0028FAC8(reinterpret_cast<void*>(0x0044BBF0));
    CGameLogic_Update_00205640();
    Func_0035AA38();

    Func_00259B70();
    Func_00257F10();
    Func_002DF2D8();
    Func_002DF360();
    Func_00271678(reinterpret_cast<void*>(0x0044AB50));

    PushMemId_001CC5B8(memIds, 17);
    Func_00212938();
    Func_003507B0();
    Func_00215548();
    Func_002156B0();
    PopMemId_001CC5C0(memIds);
}

} // namespace lcs
