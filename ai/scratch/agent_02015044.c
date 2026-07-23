// Decompresses one joint's 3x3 rotation matrix from the current resource blob
// into the object at arg0 (matrix stored at +0x28 as 9 fx32 words).
// Looks up a per-joint record via a dictionary in the resource (probably an
// NNS G3D .nsbmd/.nsbca style joint record). Depending on the record's flag
// word it either: marks the object (flag bit1), builds a pivot-compressed
// matrix via permutation tables (bit3), or copies 9 s16 values directly.

typedef signed short s16;
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;
typedef int fx32;

typedef struct {
    u32 flags;      // 0x00: status bits; bit1 set when record says "identity/skip"
    u8 pad[0x24];   // 0x04
    fx32 m[9];      // 0x28: 3x3 matrix, row major, fx32
} JointObj;

typedef struct {
    u8 *jntInfo;    // 0x00: pointer; byte at +1 is the current joint index
    u8 pad[0xd0];   // 0x04
    u8 *res;        // 0xd4: resource blob with dictionary at *(u16*)(res+6)
} GlobalCtx;

// Four parallel byte tables with stride 4: matrix-cell permutation tables for
// pivot decompression. Column-struct form keeps the *4 folded into the ldrb
// addressing mode (plain [pivot<<2] indexing gets CSEd into a separate lsl).
typedef struct {
    u8 v;
    u8 pad[3];
} PivotCol;

extern GlobalCtx *data_02170500;
extern PivotCol data_02152c30[];
extern PivotCol data_02152c31[];
extern PivotCol data_02152c32[];
extern PivotCol data_02152c33[];

extern void func_0214d32c(fx32 *m); // probably zeroes the 3x3 matrix (thumb callee)

void func_02015044(JointObj *jnt)
{
    GlobalCtx *g;
    u8 *res;
    int idx;
    u16 dictOfs;
    u16 entrySize;
    u32 dataOfs;
    u16 flags;
    s16 *src;
    // declaration order below steers callee-saved coloring:
    // reverse order -> entry=r4, pivot=r5, b=r6, a=r7 as in ROM
    fx32 a;
    fx32 b;
    int pivot;
    u8 *entry;

    g = data_02170500;
    res = g->res;
    idx = g->jntInfo[1];
    dictOfs = *(u16 *)(res + 6);
    entrySize = *(u16 *)(res + dictOfs);
    dataOfs = *(u32 *)((res + dictOfs) + entrySize * idx + 4);
    entry = res + dataOfs;
    flags = *(u16 *)entry;
    src = (s16 *)(entry + 4);

    if (!(flags & 1)) {
        src += 6; // wide record: values start 12 bytes further
    }
    if (!(flags & 2)) {
        if (flags & 8) {
            // pivot-compressed matrix
            pivot = (flags & 0xf0) >> 4;
            a = src[0];
            b = src[1];
            func_0214d32c(jnt->m);
            // flag word re-read from memory each time (ROM reloads [entry])
            jnt->m[pivot] = (*(u16 *)entry & 0x100) ? -0x1000 : 0x1000;
            jnt->m[data_02152c30[pivot].v] = a;
            jnt->m[data_02152c31[pivot].v] = b;
            if (*(u16 *)entry & 0x200) {
                b = -b;
            }
            jnt->m[data_02152c32[pivot].v] = b;
            if (*(u16 *)entry & 0x400) {
                a = -a;
            }
            jnt->m[data_02152c33[pivot].v] = a;
        } else {
            // full matrix: 9 s16 values widened to fx32
            jnt->m[0] = *(s16 *)(entry + 2);
            jnt->m[1] = src[0];
            jnt->m[2] = src[1];
            jnt->m[3] = src[2];
            jnt->m[4] = src[3];
            jnt->m[5] = src[4];
            jnt->m[6] = src[5];
            jnt->m[7] = src[6];
            jnt->m[8] = src[7];
        }
    } else {
        jnt->flags |= 2; // record marked as skip/identity
    }
}
