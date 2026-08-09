// Semantic lift of the inner TheGame frame function.
// Original function: 0x001F5BC0
//
// The detailed MIPS listing is analysis/1f5b80_1f5fa8.asm.  This lift keeps
// platform/front-end conditionals coarse until the involved globals are typed,
// but the core process/render ordering is now recovered.

namespace lcs {

extern void FramePreamble_001F6C78();
extern void Func_0014F2B8();
extern void Func_0014F928(void*);
extern void Func_00320B00();
extern void Func_00164C08();
extern void PushMemId_001CC5B8(void*, int);
extern void PopMemId_001CC5C0(void*);

extern void CGame_Process_002FBAF0();
extern void DMAudio_Service_00184280(); // high-confidence sequence name

extern void SetLightsWithTimeOfDayColour_0017C408(); // provisional
extern bool DoRWStuffStartOfFrame_Horizon_001F4100(
    int topR, int topG, int topB, int bottomR, int bottomG, int bottomB, int alpha);
extern void RenderScene_001F6138();
extern void RenderEffects_001F61C8();
extern void RenderDebugShit_001F6198();
extern void Camera_RenderMotionBlur_00292AE0(void* camera);
extern void Render2dStuff_001F6338();
extern void RenderMenus_001F65C8();
extern void DoFade_001F4280();
extern void Func_002EB538();
extern void Render2dStuffAfterFade_001F66D0();
extern void DoRWStuffEndOfFrame_001F4C88(bool present);
extern void CTimer_Update_002B4CF8();

static auto* const gMemIdStack = reinterpret_cast<void*>(0x00428110);

// This is deliberately a semantic outline rather than pretend-compilable game
// code. Conditions at 0x001F5C58..0x001F5F84 still depend on partially typed
// MemoryCard/Frontend/Camera globals.
int TheGame_Frame_001F5BC0()
{
    FramePreamble_001F6C78();

    // Several PS2/RenderWare per-frame helpers execute here before game logic.
    Func_0014F2B8();
    Func_00320B00();
    Func_00164C08();

    PushMemId_001CC5B8(gMemIdStack, 15);
    CGame_Process_002FBAF0();
    PopMemId_001CC5C0(gMemIdStack);

    // The actual binary performs restart/load checks before servicing audio.
    // If one of those flags is set it returns 0 immediately.
    DMAudio_Service_00184280();

    PushMemId_001CC5B8(gMemIdStack, 18);

    // Normal world-render branch (0x001F5D4C..0x001F5E30):
    //   construct/pre-render lists
    //   begin frame using lightning white or CTimeCycle sky colours
    //   DefinedState / camera far clip + fog
    //   RenderScene -> RenderEffects -> RenderDebugShit
    //   camera motion blur -> Render2dStuff
    // The alternate branch prepares a camera frame for menu-only rendering.
    RenderScene_001F6138();
    RenderEffects_001F61C8();
    RenderDebugShit_001F6198();
    Render2dStuff_001F6338();

    RenderMenus_001F65C8();
    DoFade_001F4280();

    // A load transition can exit here before the final present operations.
    Func_002EB538();
    Render2dStuffAfterFade_001F66D0();
    DoRWStuffEndOfFrame_001F4C88(true);

    CTimer_Update_002B4CF8();
    PopMemId_001CC5C0(gMemIdStack);

    // The MIPS returns 1 for a normal frame and 0 when TheGame must leave the
    // inner loop to perform restart/load/quit handling.
    return 1;
}

} // namespace lcs
