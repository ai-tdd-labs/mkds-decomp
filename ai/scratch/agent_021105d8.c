// PURPOSE: Initializes seven shared sound-entry lists from a copied configuration.
// The function copies a seven-word global configuration onto the stack.
// Each word becomes the count for one consecutive sound-entry list.
// The shared sound context is probably stored in the third global.

typedef unsigned int u32;

typedef struct SoundContext SoundContext;

typedef struct SoundEntry {
    int id;
    int unknown_04;
    int unknown_08;
    int unknown_0c;
} SoundEntry;

typedef struct SoundEntryList {
    int count;
    SoundEntry *entries;
} SoundEntryList;

typedef struct SoundEntryConfig {
    u32 words[7];
} SoundEntryConfig;

extern SoundEntryList data_0217d26c[];
extern SoundEntryConfig data_0217d130;
extern SoundContext *data_0216cba4;
extern void func_0210e094(SoundEntryList *list, int count, SoundContext *context);

void func_021105d8(void)
{
    SoundEntryConfig config = data_0217d130;
    int i;

    for (i = 0; i < 7; i++) {
        func_0210e094(&data_0217d26c[i], config.words[i], data_0216cba4);
    }
}
