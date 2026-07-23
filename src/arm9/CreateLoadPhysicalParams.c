/* PURPOSE: Sets up the memory that holds the karts' and characters' driving
 * stats and loads them from the game files.
 *
 * Arguments: heap handle (r0), kart/racer count (r1).
 * Allocates a small 0x14-byte state struct into the global gPhysicalParams,
 * then allocates one array of count*0x98 bytes (probably per-kart physical
 * params) and one of count*8 bytes (probably per-kart pointers/pairs).
 * Loads "kartphysicalparam.bin" and "charphysicalparam.bin" from the scene
 * archives and finally caches a field (+0x10, probably the entry table
 * pointer) out of the kart param file header.
 */

typedef unsigned int u32;

extern void *Mem_AllocateHeap(void *heap, u32 size);
extern void *FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(const char *path);

extern char data_021660c8[]; /* "kartphysicalparam.bin" */
extern char data_021660e0[]; /* "charphysicalparam.bin" */

/* Header of the loaded kartphysicalparam.bin file (only +0x10 used here). */
typedef struct KartParamFile {
    char pad_00[0x10];
    void *f10; /* probably pointer/offset to the param entry table */
} KartParamFile;

/* Global state struct for the physical parameters (size 0x14). */
typedef struct PhysicalParamState {
    void *kartParams;        /* 0x00: buffer of count*0x98 bytes */
    void *pairBuf;           /* 0x04: buffer of count*8 bytes */
    void *kartTable;         /* 0x08: copy of kartFile->f10 */
    KartParamFile *kartFile; /* 0x0c: loaded kartphysicalparam.bin */
    void *charFile;          /* 0x10: loaded charphysicalparam.bin */
} PhysicalParamState;

extern PhysicalParamState *gPhysicalParams;

void CreateLoadPhysicalParams(void *heap, int count)
{
    gPhysicalParams = (PhysicalParamState *)Mem_AllocateHeap(heap, 0x14);
    /* every store goes through the global so mwcc reloads the base pointer */
    gPhysicalParams->kartParams = Mem_AllocateHeap(heap, count * 0x98);
    gPhysicalParams->pairBuf = Mem_AllocateHeap(heap, count * 8);
    gPhysicalParams->kartFile =
        (KartParamFile *)FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(data_021660c8);
    gPhysicalParams->charFile = FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(data_021660e0);
    gPhysicalParams->kartTable = gPhysicalParams->kartFile->f10;
}
