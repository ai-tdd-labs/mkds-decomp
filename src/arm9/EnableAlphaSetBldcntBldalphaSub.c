// PURPOSE: Sets the sub-screen alpha blend settings.
// This wrapper forwards four blend values to the sub display engine.
// The hardware register address is fixed by the Nintendo DS display layout.

extern void G2x_SetBlendAlpha_(volatile unsigned short *blendRegisters,
                               int firstTargetPixels,
                               int secondTargetPixels,
                               int evaCoefficient,
                               int evbCoefficient);

void EnableAlphaSetBldcntBldalphaSub(int firstTargetPixels,
                                     int secondTargetPixels,
                                     int evaCoefficient,
                                     int evbCoefficient)
{
    G2x_SetBlendAlpha_((volatile unsigned short *)0x04001050,
                       firstTargetPixels, secondTargetPixels,
                       evaCoefficient, evbCoefficient);
}
