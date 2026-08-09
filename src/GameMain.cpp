// Semantic decompilation of the PS2 executable startup path.
// Source addresses are kept in names/comments until their real symbols are proven.

namespace lcs {

extern void RuntimeGlobalConstructors_0035B420();
extern void StartupHook_001F30F8();
extern int  GameBootstrap_001F3518();

// Original address: 0x001F3628
int GameMain(int argc, char** argv)
{
    // The original main preserves argc/argv around the constructor call, then
    // passes both arguments to the next two routines. 0x001F30F8 currently
    // does not appear to consume them directly.
    RuntimeGlobalConstructors_0035B420();

    // Keep the original signature until the callees are fully typed.
    (void)argc;
    (void)argv;
    StartupHook_001F30F8();
    return GameBootstrap_001F3518();
}

} // namespace lcs
