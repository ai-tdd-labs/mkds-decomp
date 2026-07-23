void Crt0_MemorySet32(int value, int *dst, int size) {
    int *end = (int *)((char *)dst + size);
    for (; dst < end; dst++) {
        *dst = value;
    }
}
