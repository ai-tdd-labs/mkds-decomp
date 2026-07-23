// PURPOSE: Detaches and cleans every populated link list owned by a sound object.
// The object contains four link lists starting at offset 0x18.
// Each non-empty list is detached and cleaned while the sound mutex is held.
// The exact ownership fields are probably part of the sound allocator's link metadata.

typedef struct SoundLink SoundLink;

struct SoundLink {
    char _00[4];
    SoundLink *next;
    char _08[0x10];
    SoundLink *owner;
};

typedef struct SoundList {
    SoundLink *head;
    SoundLink *tail;
} SoundList;

typedef struct SoundObject {
    char _00[0x18];
    SoundList lists[4];
} SoundObject;

extern void Sound_LockMutex(void);
extern void Sound_UnlockMutex(void);
extern void DC_SomeClean(void *buffer, int size);

void func_02021c34(SoundObject *sound)
{
    SoundObject *obj = sound;
    int cleanSize = 0x3c;
    int releaseSize = 8;
    int i;
    SoundList *list;

    Sound_LockMutex();

    for (i = 0, list = obj->lists; i < 4; i++, list++) {
        SoundLink *link;

        link = obj->lists[i].head;
        if (link != 0) {
            SoundLink *previous = link->owner;

            if ((SoundLink *)&list->head == previous) {
                link->owner = obj->lists[i].tail;
                DC_SomeClean(link, cleanSize);
            } else {
                if (previous != 0) {
                    do {
                        if ((SoundLink *)&list->head == previous->next)
                            break;
                        previous = previous->next;
                    } while (previous != 0);
                }
                previous->next = obj->lists[i].tail;
                DC_SomeClean(previous, releaseSize);
            }
        }
    }

    Sound_UnlockMutex();
}
