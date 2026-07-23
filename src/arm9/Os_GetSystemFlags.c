// PURPOSE: Returns the cached system flags for the game.
// The flags are calculated once from debug and hardware state, probably during startup.
// A shared-WRAM halfword is included in the cached result.

typedef unsigned int u32;
typedef unsigned short u16;

extern int Os_GetDebugSystemFlags(void);
extern int Os_ExistsSioConnection(void);
extern int Os_IsEmulator(void);
extern u32 data_021617cc;

u32 Os_GetSystemFlags(void)
{
    u32 debugFlags;
    u32 systemFlags;

    if (data_021617cc == (u32)-1) {
        debugFlags = Os_GetDebugSystemFlags();

        if (Os_IsEmulator() != 0) {
            systemFlags = debugFlags | 0x10000000;
        } else if (Os_ExistsSioConnection() != 0) {
            systemFlags = debugFlags | 0x40000000;
        } else if (debugFlags & 0x01000000) {
            systemFlags = debugFlags | 0x20000000;
        } else {
            systemFlags = debugFlags | 0x80000000;
        }

        data_021617cc = systemFlags | *(volatile u16 *)0x027ffffa;
    }

    return data_021617cc;
}
