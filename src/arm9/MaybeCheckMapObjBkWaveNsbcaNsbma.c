/* PURPOSE: Checks whether the map-object "bk_wave" animation files are present and remembers the result.
 *
 * If the explosion/splash wave model (nsbmd) is loaded, this looks up the
 * "/MapObj/bk_wave.nsbca" (joint animation) and "/MapObj/bk_wave.nsbma"
 * (material animation) file buffers and records in a global status struct:
 *   +0x0 (u16): 1 = wave model available, 0 = not
 *   +0x4 (int): 1 = bk_wave.nsbca found
 *   +0x8 (int): 1 = bk_wave.nsbma found
 * If the wave model is not loaded, all three flags are cleared.
 * No arguments, no return value (probably; r0 residue is incidental).
 */

typedef struct BkWaveAnimStatus {
    unsigned short haveWaveModel; /* 0x0: strh in ROM -> 16-bit field */
    unsigned short pad2;          /* 0x2 */
    int haveNsbca;                /* 0x4 */
    int haveNsbma;                /* 0x8 */
} BkWaveAnimStatus;

extern BkWaveAnimStatus data_02166210;   /* global status block */
extern int data_02166268;                /* string "/MapObj/bk_wave.nsbca" */
extern int data_02166280;                /* string "/MapObj/bk_wave.nsbma" */

extern void *GetExplosionSplashWaveNsbmd_from_thumb(void);
extern void *FindFileBuffer_CRS_CST_from_thumb(void *desc);

void MaybeCheckMapObjBkWaveNsbcaNsbma(void)
{
    /* base pointer cached in callee-saved r5 across both calls (single pool load) */
    BkWaveAnimStatus *st = &data_02166210;

    if (GetExplosionSplashWaveNsbmd_from_thumb() != 0) {
        /* nsbca result survives the second call (r4); nsbma result stays in r0 */
        void *nsbca = FindFileBuffer_CRS_CST_from_thumb(&data_02166268);
        void *nsbma = FindFileBuffer_CRS_CST_from_thumb(&data_02166280);
        st->haveWaveModel = 1;
        /* if/else (not ternary) so mwcc if-converts the STORES themselves:
           cmp; strne (reusing the constant 1 from above); moveq; streq */
        if (nsbca != 0) {
            st->haveNsbca = 1;
        } else {
            st->haveNsbca = 0;
        }
        if (nsbma != 0) {
            st->haveNsbma = 1;
        } else {
            st->haveNsbma = 0;
        }
    } else {
        st->haveWaveModel = 0;
        st->haveNsbca = 0;
        st->haveNsbma = 0;
    }
}
