typedef unsigned int u32;

extern void func_0214b5cc(void *ptr, u32 offset, u32 size);
extern void func_0214b558(void *ptr, u32 offset, u32 size);
extern void GX_EndLoadOBJExtPltt(void);

void TEQSub_Fn16(void *ptr, u32 offset, u32 size) {
    func_0214b5cc(ptr, offset, size);
    func_0214b558(ptr, offset, size);
    GX_EndLoadOBJExtPltt();
}
