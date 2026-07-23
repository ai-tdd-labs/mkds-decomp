// PURPOSE: Updates the mission splash explosion until its animation time ends.
// The argument is the splash effect instance.
// When its current frame reaches its probably configured limit, it is marked finished.
// Otherwise, its two animations are advanced.

typedef struct MissionSplashExplosion {
    unsigned char pad_00[0x88];
    unsigned int finished;      /* 0x88 */
    unsigned char pad_8c[4];
    void *animation0;           /* 0x90 */
    void *animation1;           /* 0x94 */
    unsigned char pad_98[0x10];
    unsigned int frameCounter;  /* 0xa8 */
    unsigned int frameLimit;    /* 0xac */
} MissionSplashExplosion;

extern void Animation_Update(void *animation);

void ExplosionKind_Splash_MissionSplash_UpdateFn(MissionSplashExplosion *explosion)
{
    if (explosion->frameCounter >= explosion->frameLimit) {
        explosion->finished = 1;
        return;
    }

    Animation_Update(explosion->animation0);
    if (explosion->animation1 == 0) {
        return;
    }

    Animation_Update(explosion->animation1);
}
