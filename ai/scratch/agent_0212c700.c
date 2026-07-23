// PURPOSE: Allocates and registers a sound object for a sound-state slot.
// The state index selects the global intrusive list that owns the object.
// The requested size is used to construct the object's embedded sound context.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct IntrusiveListWrapper {
    void *first;
    void *last;
    u16 count;
    u16 linkOffset;
} IntrusiveListWrapper;

typedef struct SoundContext {
    void *heap;
    IntrusiveListWrapper allocationStates;
} SoundContext;

typedef struct SoundObject {
    char pad00[8];
    SoundContext *context;
    void *owner;
    int listIndex;
    char contextStorage[1];
} SoundObject;

typedef struct SoundState {
    char pad00[0xc];
    IntrusiveListWrapper objects;
    char pad18[0xc];
} SoundState;

typedef void (*SoundDisposeCallback)(void *payload, u16 payloadSize,
                                     void *soundArchive, u32 customArgument);

extern void SoundDtorFn(SoundObject *sound);
extern void *Sound_Context_Allocate(SoundContext *context, unsigned int payloadSize,
                                    SoundDisposeCallback disposeCallback,
                                    void *soundArchive, void *customArgument);
extern SoundContext *Sound_InitializeContext(void *start, u32 size);
extern void IntrusiveListWrapper_InsertLast(IntrusiveListWrapper *list, void *item);
extern SoundState data_0217d89c[];

int func_0212c700(int stateIndex, SoundContext *allocator, u32 contextSize)
{
    SoundObject *sound;

    sound = Sound_Context_Allocate(allocator, contextSize + 0x14,
                                   (SoundDisposeCallback)SoundDtorFn, 0, 0);
    if (sound == 0) {
        return 0;
    }

    sound->owner = 0;
    sound->listIndex = stateIndex;
    sound->context = 0;
    sound->context = Sound_InitializeContext(sound->contextStorage, contextSize);
    if (sound->context == 0) {
        return 0;
    }

    IntrusiveListWrapper_InsertLast(&data_0217d89c[stateIndex].objects, sound);
    return 1;
}
