// PURPOSE: Destroys a sound object and removes it from its list.
// The object holds a disposable sound context and may point to an owner.
// If it has no owner, it is probably unlinked from the shared sound list.

typedef struct {
    unsigned char pad00[8];
    void *context;
    void *owner;
    int listIndex;
} SoundObject;

extern void Sound_Context_Dispose(void *context);
extern void IntrusiveListWrapper_RemoveItem(void *item, void *object);
extern unsigned char data_0217d89c[];

void SoundDtorFn(SoundObject *sound)
{
    if (sound->context == 0)
        return;

    Sound_Context_Dispose(sound->context);

    if (sound->owner != 0) {
        *(int *)((unsigned char *)sound->owner + 8) = 0;
        return;
    }

    IntrusiveListWrapper_RemoveItem(
        data_0217d89c + sound->listIndex * 0x24 + 0xc, sound);
}
