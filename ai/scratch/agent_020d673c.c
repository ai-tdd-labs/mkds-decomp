// PURPOSE: Updates the object's rotation matrix from the current time.
// The time helper probably supplies an animation phase.
// The phase selects a sine/cosine pair for the matrix at offset 0x2c.

typedef signed short s16;
typedef unsigned int u32;

extern int GetSomeTimeOrDuration(void);
extern void *data_0217b650;
extern s16 data_0215d4b4[];
extern void MTX_RotY33__from_thumb(void *mtx, s16 sinv, s16 cosv);

void func_020d673c(void)
{
    int angle = (int)((u32)(GetSomeTimeOrDuration() << 25) >> 16) >> 4;

    MTX_RotY33__from_thumb((char *)data_0217b650 + 0x2c,
                            data_0215d4b4[angle * 2],
                            data_0215d4b4[angle * 2 + 1]);
}
