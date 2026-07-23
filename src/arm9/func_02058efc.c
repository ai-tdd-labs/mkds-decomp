// PURPOSE: Marks the scene as ready after the sound data is unavailable.
// The sound-data routine probably reports whether shared audio data is present.
// When it reports failure, this sets a byte flag in the shared scene context.

typedef struct UnkStruct_0217aa00 {
    unsigned char padding_000[0x164f];
    unsigned char sound_data_missing;
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern int Maybe_data_Sound_sound_data(void);

void func_02058efc(void)
{
    if (Maybe_data_Sound_sound_data() == 0) {
        data_0217aa00->sound_data_missing = 1;
    }
}
