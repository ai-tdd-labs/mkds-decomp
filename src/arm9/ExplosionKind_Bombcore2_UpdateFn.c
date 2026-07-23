/* PURPOSE: Advances the bomb-core explosion until its lifetime ends.
 * The argument is the explosion instance. Once its probably frame counter
 * reaches 55, the function marks the effect as finished and stops updating.
 * Otherwise, it advances each of the explosion's three animations.
 */

typedef struct Bombcore2Explosion {
    unsigned char pad_00[0x88];
    unsigned int finished;          /* 0x88 */
    unsigned char pad_8c[4];
    void *animation0;               /* 0x90 */
    void *animation1;               /* 0x94 */
    void *animation2;               /* 0x98 */
    unsigned char pad_9c[0x0c];
    unsigned int frameCounter;      /* 0xa8 */
} Bombcore2Explosion;

extern void Animation_Update(void *animation);

void ExplosionKind_Bombcore2_UpdateFn(Bombcore2Explosion *explosion)
{
    if (explosion->frameCounter >= 0x37) {
        explosion->finished = 1;
        return;
    }

    Animation_Update(explosion->animation0);
    Animation_Update(explosion->animation1);
    Animation_Update(explosion->animation2);
}
