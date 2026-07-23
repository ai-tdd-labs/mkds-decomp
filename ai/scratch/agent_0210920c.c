// PURPOSE: Converts a direction vector into a clamped steering value.

extern int FX_Atan2(int y, int x);

int func_0210920c(void *vector)
{
    int angle;

    angle = FX_Atan2(*(int *)((char *)vector + 8) << 12,
                     -*(int *)((char *)vector + 12) << 12);
    if ((unsigned int)angle > 0x7FFF) {
        angle = (unsigned short)(0xFFFF - angle);
    }

    angle = (int)(((long long)(angle << 12) * -32 + 0x800) >> 12) >> 12;
    angle += 0x7F;
    if (angle < -128) {
        return -128;
    }
    if (angle > 0x7F) {
        angle = 0x7F;
    }
    return angle;
}
