typedef unsigned int u32;

extern void func_0214b3f8(void *ptr, u32 offset, u32 size);
extern void func_0214b384(void *ptr, u32 offset, u32 size);
extern void GXS_EndLoadOBJExtPltt(void);

void TEQSub_Fn32(void *ptr, u32 offset, u32 size) {
    func_0214b3f8(ptr, offset, size);
    func_0214b384(ptr, offset, size);
    GXS_EndLoadOBJExtPltt();
}
