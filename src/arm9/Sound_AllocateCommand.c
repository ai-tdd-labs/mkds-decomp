// PURPOSE: Gets a free sound command for the sound system.
// The flag probably permits waiting for a command when none is immediately free.
// It returns the allocated command handle, or zero when commands are unavailable.

extern int Sound_IsCommandAvailable(void);
extern int Sound_AllocateCommandImpl(void);
extern int SND_CountWaitingCommand(void);
extern void Sound_FlushCommand(int a0);
extern void SoundInternal_RequestCommandProc(void);
extern int Sound_CommandReceiveAndReply(int a0);

int Sound_AllocateCommand(int wait)
{
    int command;

    if (Sound_IsCommandAvailable() == 0) {
        return 0;
    }

    command = Sound_AllocateCommandImpl();
    if (command != 0) {
        return command;
    }

    if ((wait & 1) == 0) {
        return 0;
    }

    if (SND_CountWaitingCommand() > 0) {
        while (Sound_CommandReceiveAndReply(0) != 0) {
        }

        command = Sound_AllocateCommandImpl();
        if (command != 0) {
            return command;
        }
    } else {
        Sound_FlushCommand(1);
    }

    SoundInternal_RequestCommandProc();
    do {
        Sound_CommandReceiveAndReply(1);
        command = Sound_AllocateCommandImpl();
    } while (command == 0);

    return command;
}
