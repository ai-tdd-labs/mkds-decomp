/* PURPOSE: Sets up the whole game when it boots: system libraries, screen
 * brightness, the main memory heap, and the main game thread.
 * No arguments. Initializes the SDK and brightness fade contexts, records
 * the main-RAM base (0x02000000) and the start of memory region 0 in the
 * global boot state, creates an expandable heap spanning region 0, creates
 * the main execution context (probably a thread/profiler context) and tags
 * it with the name "MainProc", then runs the remaining global init. */

extern void InitializeSDKModules(void);
extern void InitializeBrightnessContexts(void);
extern void *Os_GetMemoryRegionStartAddress(int region);
extern void *Os_GetMemoryRegionEndAddress(int region);
extern void MemoryRegionAddressAccess(void);
extern void *Mem_CreateExpHeap(void *start, unsigned int size);
extern void ExecutionContext_Create(void *ctx, int arg);
extern void InitializeGlobalG_M1(void);

/* Global boot/system state. The execution context (data_02174e88) overlaps
 * this struct at +0x10; the delinker split them into two symbols. */
struct BootState {
    int field_00;          /* not touched here */
    void *ramStart;        /* +0x04: main RAM base (0x02000000) */
    void *regionStart;     /* +0x08: start of memory region 0 */
    void *heap;            /* +0x0c: expanded-heap handle */
    const char *procName;  /* +0x10: "MainProc" (== data_02174e88 +0) */
};
extern struct BootState data_02174e78;
extern char func_01ff8000[]; /* ITCM start; only used to form 0x02000000 below */
extern int data_02174e88[];   /* execution context storage */
extern char data_021646ec[];  /* "MainProc" */

void InitializeEverything(void) {
    void *start;

    InitializeSDKModules();
    InitializeBrightnessContexts();
    /* Main RAM base 0x02000000. Written as a link-time symbol+offset so mwcc
     * emits a literal-pool load (like the ROM) instead of mov r2,#0x2000000;
     * func_01ff8000 + 0x8000 == 0x02000000 after linking. The original
     * probably referenced a linker-defined start symbol here. A symbol that
     * is also used elsewhere in this function would get CSE'd into an add. */
    data_02174e78.ramStart = func_01ff8000 + 0x8000;
    data_02174e78.regionStart = Os_GetMemoryRegionStartAddress(0);
    MemoryRegionAddressAccess();
    start = Os_GetMemoryRegionStartAddress(0);
    data_02174e78.heap = Mem_CreateExpHeap(
        start, (unsigned int)Os_GetMemoryRegionEndAddress(0) - (unsigned int)start);
    ExecutionContext_Create(data_02174e88, 0);
    data_02174e78.procName = data_021646ec;
    InitializeGlobalG_M1();
}
