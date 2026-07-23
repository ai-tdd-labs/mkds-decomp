// PURPOSE: Sets the sub-screen alpha blending values.
/*
 * The arguments select blend targets and their two alpha coefficients.
 * This wrapper probably forwards them to the sub-engine blend registers.
 */

typedef signed short s16;
typedef unsigned short u16;

extern void G2x_SetBlendAlpha_(volatile u16 *blendRegisters,
                               s16 firstTargetPixels,
                               s16 secondTargetPixels,
                               s16 evaCoefficient,
                               s16 evbCoefficient);

void func_020caaac(s16 firstTargetPixels, s16 secondTargetPixels,
                   s16 evaCoefficient, s16 evbCoefficient)
{
    G2x_SetBlendAlpha_((volatile u16 *)0x04001050,
                       firstTargetPixels, secondTargetPixels,
                       evaCoefficient, evbCoefficient);
}
