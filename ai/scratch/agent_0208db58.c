// PURPOSE: Updates the Bakubaku Wave explosion until its animation time runs out.
// The argument is the effect instance.
// When its current frame reaches its probably configured frame limit, it is marked finished.
// Otherwise, the effect's two animations are advanced.

typedef struct BakubakuWaveExplosion {
    unsigned char pad_00[0x88];
    unsigned int finished;      /* 0x88 */
    unsigned char pad_8c[4];
    void *animation0;           /* 0x90 */
    void *animation1;           /* 0x94 */
    unsigned char pad_98[0x10];
    unsigned int frameCounter;  /* 0xa8 */
    unsigned int frameLimit;    /* 0xac */
} BakubakuWaveExplosion;

extern void Animation_Update(void *animation);

void ExplosionKind_BakubakuWave_UpdateFn(BakubakuWaveExplosion *explosion)
{
    if (explosion->frameCounter >= explosion->frameLimit) {
        explosion->finished = 1;
        return;
    }

    Animation_Update(explosion->animation0);
    Animation_Update(explosion->animation1);
}
