// PURPOSE: Updates a sound player's track settings.
// The first argument is probably an unused update context.
// The second argument supplies the sound player handle and its track fields.
// It applies the shared track mask with two different player settings.

typedef struct SfxUpdateWork {
    unsigned char padding0[0x14];
    short mute;
    unsigned char padding1[4];
    unsigned char command_index;
} SfxUpdateWork;

extern unsigned short data_0216cb20;
extern void func_0212c554(void *handle, int track_mask, int command_index);
extern void func_0212c524(void *handle, unsigned int track_bit_mask, int mute);

void SfxUpdate_Unk(int unused, SfxUpdateWork *work)
{
    func_0212c554(work, data_0216cb20, work->command_index);
    func_0212c524(work, data_0216cb20, work->mute);
}
