// PURPOSE: Creates the main frame memory area.
// The fixed memory region is probably reserved for system frame allocations.
// The new frame is retained in a global system context.

typedef unsigned int u32;

typedef struct {
    char padding[0xa0];
    void *frame;
} SystemContext;

extern void *data_0217aa10;
extern void *Mem_Frame_Create(void *start, u32 size, int direction);

void func_0205a108(void) {
    ((SystemContext *)data_0217aa10)->frame =
        Mem_Frame_Create((void *)0x02180500, 0x50000, 0);
}
