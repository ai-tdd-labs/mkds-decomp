/* Initializes the global "CE" structure (kart/emblem menu data, 0x26c bytes):
 * allocates it on the given heap, sets data_0217ad00 to 0, zeroes nearly
 * all fields, sets index field 0x266 to 0 and points pointer 0x20 at
 * subs[0]. Then loads the emblem palette and "kartoffsetdata.bin" (into +0x1c8),
 * initializes the two 0xb8-sized sub-structs (at +0x58) and calls an
 * init function on +0x24. Finishes with heap group id 9.
 * Field names are tentative; the layout follows the used offsets exactly. */

typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct StructCESub {
    unsigned char raw[0xb8];
} StructCESub;

typedef struct StructCE {
    unsigned char pad_00[0x18];
    s32 f18;                  /* 0x018 */
    s32 f1c;                  /* 0x01c */
    StructCESub *cur;         /* 0x020: points at subs[f266] */
    unsigned char f24[0x34];  /* 0x024: passed to StructCE0_SomeFn */
    StructCESub subs[2];      /* 0x058 */
    unsigned char f1c8[8];    /* 0x1c8: destination of kartoffsetdata.bin */
    s32 f1d0;                 /* 0x1d0 */
    unsigned char pad_1d4[4];
    s32 f1d8;                 /* 0x1d8 */
    s32 f1dc;                 /* 0x1dc */
    unsigned char pad_1e0[4];
    s32 f1e4;                 /* 0x1e4 */
    s32 f1e8;                 /* 0x1e8 */
    s32 f1ec;                 /* 0x1ec */
    u16 f1f0;                 /* 0x1f0 */
    unsigned char pad_1f2[0x6a];
    s32 f25c;                 /* 0x25c */
    s32 f260;                 /* 0x260 */
    s16 f264;                 /* 0x264 */
    s16 f266;                 /* 0x266: signed index (ldrsh) */
    s32 f268;                 /* 0x268 */
} StructCE;                   /* sizeof == 0x26c */

extern void *Mem_AllocateHeap(void *heap, u32 size);
extern void ReadEmblemPalette_from_thumb(void *heap);
extern void ReadKartModelMenuFile_from_thumb(void *heap, void *name, void *dst);
extern void StructCESub_Initialize_from_thumb(void *heap, StructCESub *sub);
extern void StructCE0_SomeFn_from_thumb(void *arg, int a1);
extern void SetActiveExecutionContextHeapGroupId_from_thumb(int id);

extern int data_0217ad00;
extern StructCE *data_0217ad08;
extern char data_02165724[]; /* "kartoffsetdata.bin" */

void InitializeGlobalCE_from_thumb(void *heap) {
    u16 i;

    data_0217ad00 = 0;
    data_0217ad08 = (StructCE *)Mem_AllocateHeap(heap, 0x26c);
    data_0217ad08->f264 = -1;
    data_0217ad08->f266 = 0;
    /* every statement reloads the global pointer (aliasing), as in the ROM */
    data_0217ad08->cur = &data_0217ad08->subs[data_0217ad08->f266];
    data_0217ad08->f1d0 = 0;
    data_0217ad08->f1dc = 0;
    data_0217ad08->f1d8 = 0;
    data_0217ad08->f1e4 = 0;
    data_0217ad08->f18 = 0;
    data_0217ad08->f1c = 0;
    data_0217ad08->f25c = 0;
    data_0217ad08->f260 = 0;
    data_0217ad08->f268 = 0;
    data_0217ad08->f1f0 = 0;
    data_0217ad08->f1ec = 0;
    data_0217ad08->f1e8 = data_0217ad08->f1ec;
    ReadEmblemPalette_from_thumb(heap);
    ReadKartModelMenuFile_from_thumb(heap, data_02165724, data_0217ad08->f1c8);
    for (i = 0; i < 2; i++) {
        StructCESub_Initialize_from_thumb(heap, &data_0217ad08->subs[i]);
    }
    StructCE0_SomeFn_from_thumb(data_0217ad08->f24, 1);
    SetActiveExecutionContextHeapGroupId_from_thumb(9);
}
