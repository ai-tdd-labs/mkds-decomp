/* PURPOSE: Construct a racer-entry object: run its base initializer, allocate
 * and set up a heap-backed sub-block, cache a config value, and derive an
 * initial value from its linked target.
 */

typedef struct {
    unsigned char pad00[0x34];
    short f34; /* value read from the linked target and fed into func_020d2178 */
} MQRacerEntryTarget;

typedef struct {
    int w0;
    int w1;
    int w2;
} InitBlock020a9e04;

typedef struct {
    unsigned char pad000[0x70];
    int f70;             /* cached from data_0217ca6c->f188 */
    unsigned char pad074[0x94 - 0x74];
    void *f94;            /* heap-allocated sub-block */
    unsigned char pad098[0x9c - 0x98];
    MQRacerEntryTarget *f9c; /* linked target object */
    unsigned char pad0a0[0x128 - 0xa0];
    int f128;             /* derived from f9c->f34 */
} MQRacerEntry;

typedef struct {
    unsigned char pad000[0x188];
    void *f188;
} ConfigTable0217ca6c;

extern InitBlock020a9e04 data_02167974;
extern ConfigTable0217ca6c data_0217ca6c;

extern void func_020d29cc(MQRacerEntry *self, InitBlock020a9e04 *init);
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heapHandle, int size);
extern void StructMQRacerEntry_SomeFn_45(void *heap, int count, void *dst);
extern int func_020d2178(int value);

void func_020a9e04(MQRacerEntry *self)
{
    InitBlock020a9e04 init = data_02167974;

    func_020d29cc(self, &init);

    self->f94 = Mem_AllocateHeap(ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x44);
    StructMQRacerEntry_SomeFn_45(self->f94, 0xa, (char *)self + 4);

    self->f70 = (int)data_0217ca6c.f188;

    self->f128 = func_020d2178(self->f9c->f34);
}
