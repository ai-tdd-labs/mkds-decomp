void Os_SetMemoryRegionStartAddress(int region, unsigned int addr) {
    *(unsigned int *)(0x027ff000 + (region << 2) + 0xda0) = addr;
}
