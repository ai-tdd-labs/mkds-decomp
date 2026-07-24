// PURPOSE: Sends a command to the sound system.
// The five arguments become the command's payload words.
// If no command entry is available, the request is silently discarded.

typedef struct SoundCommand {
    int type;
    int argument0;
    int argument1;
    int argument2;
    int argument3;
    int argument4;
} SoundCommand;

extern SoundCommand *Sound_AllocateCommand(int type);
extern void func_020213a4(SoundCommand *command);

void MaybeSoundSendCommand(int argument0, int argument1, int argument2,
                           int argument3, int argument4)
{
    SoundCommand *command;

    command = Sound_AllocateCommand(1);
    if (command == 0) {
        return;
    }

    command->argument0 = argument0;
    command->argument1 = argument1;
    command->argument2 = argument2;
    command->argument3 = argument3;
    command->argument4 = argument4;
    func_020213a4(command);
}
