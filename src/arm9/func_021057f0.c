// PURPOSE: Configures the sound banks for a selected mode.
// The first argument updates the active sound mode and enables loading only for mode 3.
// The second argument selects one of several related banks and a small state value.
// The function then probably restores the sound heap before loading shared resources.

typedef unsigned int u32;
typedef unsigned short u16;

extern int data_0217c784;
extern int data_0217c79c;
extern int data_0217c7a0;
extern u16 data_0217c774;
extern u32 data_0217c798;
extern void *data_0217d130;

extern void Sound_MaybeRestoreHeapState(void *context, u32 state);
extern void Sound_Context_GetMaybeSavedFrameHeapStateId(void *context);
extern int Sound_LoadSbnk(int bankId, void *heap);
extern int Sound_LoadSarc(int archiveId, void *heap);

void func_021057f0(int mode, int selection)
{
    int bankId = 0xff;

    data_0217c784 = mode;
    data_0217c79c = 0;
    data_0217c7a0 = 0;
    data_0217c774 = bankId;

    if (mode != 3) {
        return;
    }

    switch (selection) {
    case 0:
        break;
    case 1:
        data_0217c774 = 1;
        bankId = 0x25;
        break;
    case 2:
        data_0217c774 = 2;
        bankId = 0x26;
        break;
    case 3:
        data_0217c774 = 3;
        bankId = 0x27;
        break;
    case 4:
        data_0217c774 = 4;
        bankId = 0x28;
        break;
    case 5:
        data_0217c774 = 5;
        bankId = 0x29;
        break;
    case 6:
        data_0217c774 = 6;
        bankId = 0x25;
        break;
    case 7:
        data_0217c774 = 7;
        bankId = 0x17;
        break;
    }

    Sound_MaybeRestoreHeapState(data_0217d130, data_0217c798);
    Sound_Context_GetMaybeSavedFrameHeapStateId(data_0217d130);
    Sound_LoadSbnk(bankId, data_0217d130);
    Sound_LoadSbnk(0x2a, data_0217d130);
    Sound_LoadSarc(4, data_0217d130);
}
