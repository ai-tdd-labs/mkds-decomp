extern void Mem_CpuFastMemorySet(void *dst, int val);

void Mem_CpuFastMemorySet2(int val, void *dst) {
    void *volatile d = dst;
    Mem_CpuFastMemorySet(d, val);
}
