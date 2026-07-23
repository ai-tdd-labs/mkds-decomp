// PURPOSE: Sets up a fade/wobble animation effect on every active object in
// a list, driven by the current animation-frame position of a shared model.
// Loops entries in the struct at data_0217b0fc (a {void **list; u16 count; ...}
// holder) until either count entries are done or a null entry is hit. Reads
// the shared object pointer at data_0217b100 and, depending on whether its
// current BCA animation has more than one frame, computes a random-ish value
// from the (frameCount-1) position (scaled to fx32) and feeds it plus a
// constant 0.5f into one of two setup functions (order of the two args
// differs between the two calls). Each processed entry then gets a handful
// of fixed fields reset (probably alpha/scale/offset animation state).
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;

typedef struct {
    void **list;   // 0x00: pointer to array of entry pointers
    u16 count;     // 0x04: number of entries in the list
} ObjectListHolder;

typedef struct {
    u32 pad0[0x29];    // up to +0xa4
    u32 f0xa4;
    u32 f0xa8;
    u32 f0xac;
    u32 f0xb0;
    u32 pad1[(0x1e0 - 0xb4) / 4];
    fx32 f0x1e0;
} Entry;

extern ObjectListHolder *data_0217b0fc;
extern void *data_0217b100;

extern int StructMapObject_GetAnimationBCAFrameCount(void *obj);
extern fx32 func_02132440(fx32 frame);          // mid-function label target, module main
extern void func_02131234(float scale, fx32 randVal);
extern void func_021329f8(fx32 randVal, float scale);
extern u32 func_021322c8(void);

void func_0209886c(void)
{
    if (data_0217b0fc == 0) {
        return;
    }

    int sl;
    Entry *sb;
    for (sl = 0; sl < data_0217b0fc->count && (sb = (Entry *)data_0217b0fc->list[sl]) != 0; sl++) {
        int frameCount = StructMapObject_GetAnimationBCAFrameCount(data_0217b100);
        if (frameCount - 1 > 0) {
            fx32 randVal = func_02132440((StructMapObject_GetAnimationBCAFrameCount(data_0217b100) - 1) << 0xc);
            func_02131234(0.5f, randVal);
        } else {
            fx32 randVal = func_02132440((StructMapObject_GetAnimationBCAFrameCount(data_0217b100) - 1) << 0xc);
            func_021329f8(randVal, 0.5f);
        }

        sb->f0xa4 = 0;
        sb->f0xa8 = 0x1000;
        sb->f0xac = 0;
        sb->f0xb0 = func_021322c8();
        sb->f0x1e0 = (fx32)(~0xa3);
    }
}
