/*
 * PURPOSE: Register a game-state handler with its callbacks and tag it with id 0x156.
 *
 * Allocates/registers a handler record via CreateAllocateSomeObject_from_thumb with three callback
 * functions (init/update/draw by position), priority 1 and heap-id 1, then
 * stores the identifier 0x156 into the record.
 */

typedef unsigned short u16;

typedef struct StateHandler {
    void (*initFunc)(void);   /* 0x00 */
    void (*updateFunc)(void); /* 0x04 */
    int unk08;                /* 0x08 */
    int unk0c;                /* 0x0c */
    int unk10;                /* 0x10 */
    int unk14;                /* 0x14 */
    void (*drawFunc)(void);   /* 0x18 */
    int heapId;               /* 0x1c */
    int priority;             /* 0x20 */
    int unk24;                /* 0x24 */
    int stateId;              /* 0x28 */
} StateHandler;

StateHandler *CreateAllocateSomeObject_from_thumb(void (*initFunc)(void), void (*updateFunc)(void),
                            void (*drawFunc)(void), int priority, u16 heapId);

void func_0209c9fc(void);
void func_0209c964(void);
void func_0209c8b0(void);

void func_0209c198(void) {
    StateHandler *handler = CreateAllocateSomeObject_from_thumb(func_0209c9fc, func_0209c964, func_0209c8b0, 1, 1);

    handler->stateId = 0x156;
}
