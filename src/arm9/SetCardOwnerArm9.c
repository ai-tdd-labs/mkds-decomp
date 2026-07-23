void SetCardOwnerArm9(void) {
    *(volatile unsigned short *)0x04000204 &= ~0x0800;
}
