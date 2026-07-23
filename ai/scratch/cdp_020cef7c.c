extern void Mem_CpuFastMemorySet(void *dst, int val);

void SpecialMemoryMemsetV2(int val, void *dst) {
    void *volatile d = dst;
    Mem_CpuFastMemorySet(d, val);
}
