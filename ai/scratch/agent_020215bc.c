// PURPOSE: Initializes the sound command queues and shared work area.
// This links every command buffer into the free list and resets queue state.
// It also tells the sound processor where the shared work area is located.

typedef unsigned int u32;

typedef struct SoundCommand {
    struct SoundCommand *next;
    u32 id;
    u32 args[4];
} SoundCommand;

typedef struct SoundSharedWork SoundSharedWork;

extern SoundCommand *data_021732c8;
extern u32 data_021732cc;
extern SoundCommand *data_021732d0;
extern SoundCommand *data_021732d4;
extern SoundCommand *data_021732d8;
extern int data_021732dc;
extern int data_021732e0;
extern int data_021732e4;
extern u32 data_021732e8;
extern SoundSharedWork data_02173320;
extern SoundCommand data_021735a0[256];
extern SoundSharedWork *data_02174e00;

extern void Sound_RegisterFifoHandler(void);
extern SoundCommand *Sound_AllocateCommand(int wait);
extern void Sound_FlushCommand(int flags);
extern void func_020213a4(SoundCommand *command);
extern void func_020217b4(SoundSharedWork *work);

void Sound_InitializeCommands(void)
{
    SoundCommand *command;

    Sound_RegisterFifoHandler();

    data_021732c8 = data_021735a0;
    for (int i = 0; i < 255; i++) {
        data_021735a0[i].next = &data_021735a0[i + 1];
    }

    data_021735a0[255].next = 0;
    data_021732d8 = &data_021735a0[255];
    data_021732d0 = 0;
    data_021732d4 = 0;
    data_021732e4 = 0;
    data_021732dc = 0;
    data_021732e0 = 0;
    data_021732e8 = 1;
    data_021732cc = 0;

    data_02174e00 = &data_02173320;
    func_020217b4(data_02174e00);

    command = Sound_AllocateCommand(1);
    if (command == 0) {
        return;
    }

    command->id = 0x1d;
    command->args[0] = (u32)data_02174e00;
    func_020213a4(command);
    Sound_FlushCommand(1);
}
