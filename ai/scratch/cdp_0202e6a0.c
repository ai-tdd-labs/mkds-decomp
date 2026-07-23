extern void Mem_CpuFastMemorySet(void *dst, int val);

void Maybe_call_Mem_CpuFastMemorySet_2(int val, void *dst) {
    void *volatile d = dst;
    Mem_CpuFastMemorySet(d, val);
}
