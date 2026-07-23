typedef unsigned int u32;

extern void func_0214b4dc(void *ptr, u32 offset, u32 size);
extern void func_0214b468(void *ptr, u32 offset, u32 size);
extern void GXS_EndLoadBGExtPltt(void);

void TEQSub_Fn33(void *ptr, u32 offset, u32 size) {
    func_0214b4dc(ptr, offset, size);
    func_0214b468(ptr, offset, size);
    GXS_EndLoadBGExtPltt();
}
