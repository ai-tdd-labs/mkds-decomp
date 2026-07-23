// PURPOSE: Converts the driver's yaw rotation into the opposing angle.
// Probably returns the angle in the game's unsigned 16-bit turn format.

extern int GetDriverYRotation(void);

unsigned short func_020b6338(void) {
    return (unsigned short)((0x18000 - GetDriverYRotation()) % 0x10000);
}
