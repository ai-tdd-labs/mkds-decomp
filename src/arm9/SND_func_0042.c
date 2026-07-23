// PURPOSE: Clears and frees every sound buffer linked to a sound object.
// The argument probably owns a linked list at offset 0x18.
// Each list entry is unlinked before it is passed to the cleanup routine.

typedef struct SoundBuffer SoundBuffer;

struct SoundBuffer {
    SoundBuffer *previous;
    SoundBuffer *next;
};

typedef struct SoundObject {
    char _00[0x18];
    SoundBuffer *buffers;
} SoundObject;

extern void Sound_LockMutex(void);
extern void Sound_UnlockMutex(void);
extern void DC_SomeClean(void *buffer, int size);

void SND_func_0042(SoundObject *sound)
{
    SoundBuffer *next;
    SoundBuffer *buffer;

    Sound_LockMutex();

    buffer = sound->buffers;
    if (buffer != 0) {
        do {
            next = buffer->next;
            buffer->previous = 0;
            buffer->next = 0;
            DC_SomeClean(buffer, 8);
            buffer = next;
        } while (buffer != 0);
    }

    Sound_UnlockMutex();
}
