// PURPOSE: Enables alpha blending on the top screen.
// Configures the top display engine's blend targets and alpha values.
// The arguments select two target groups and their blend coefficients.

typedef signed short s16;
typedef unsigned short u16;

extern void G2x_SetBlendAlpha_(volatile u16 *blendRegisters,
                               s16 firstTargetPixels,
                               s16 secondTargetPixels,
                               s16 evaCoefficient,
                               s16 evbCoefficient);

void EnableAlphaSetTopBldcntBldalpha(s16 firstTargetPixels,
                                     s16 secondTargetPixels,
                                     s16 evaCoefficient,
                                     s16 evbCoefficient)
{
    G2x_SetBlendAlpha_((volatile u16 *)0x04000050,
                       firstTargetPixels,
                       secondTargetPixels,
                       evaCoefficient,
                       evbCoefficient);
}
