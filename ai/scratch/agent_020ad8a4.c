/* PURPOSE: Enables alpha blending on the sub screen.
 * Configures the sub-engine blend targets and alpha coefficients.
 * The four arguments select the two targets and their blend values.
 */

typedef signed short s16;
typedef unsigned short u16;

extern void G2x_SetBlendAlpha_(volatile u16 *blendRegisters,
                               s16 firstTargetPixels,
                               s16 secondTargetPixels,
                               s16 evaCoefficient,
                               s16 evbCoefficient);

void EnableAlphaSetSubBldcntBldalpha(s16 firstTargetPixels,
                                     s16 secondTargetPixels,
                                     s16 evaCoefficient,
                                     s16 evbCoefficient)
{
    G2x_SetBlendAlpha_((volatile u16 *)0x04001050,
                       firstTargetPixels,
                       secondTargetPixels,
                       evaCoefficient,
                       evbCoefficient);
}
