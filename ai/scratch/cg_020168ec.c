typedef unsigned int u32;

extern void func_0214c48c(void *ptr, u32 offset, u32 size);
extern void SomeDmaCopy_0(void *ptr, u32 offset, u32 size);
extern void func_0214c3c0(void);

void TEQSub_Fn1(void *ptr, u32 offset, u32 size) {
    func_0214c48c(ptr, offset, size);
    SomeDmaCopy_0(ptr, offset, size);
    func_0214c3c0();
}
