/* PURPOSE: Updates the sub-screen's display blending settings.
 * The arguments select the first and second blend targets, the two alpha
 * coefficients, and the brightness coefficient. The function applies them
 * to the sub-engine blend registers beginning at 0x04001050.
 */

typedef signed short s16;
typedef unsigned short u16;

extern void UpdateBldcntBldalphaBldy(volatile u16 *blendRegisters,
                                     s16 firstTargetPixels,
                                     s16 secondTargetPixels,
                                     s16 evaCoefficient,
                                     s16 evbCoefficient,
                                     int brightnessCoefficient);

void UpdateBldcntBldalphaBldy_Sub(s16 firstTargetPixels,
                                  s16 secondTargetPixels,
                                  s16 evaCoefficient,
                                  s16 evbCoefficient,
                                  int brightnessCoefficient)
{
    UpdateBldcntBldalphaBldy((volatile u16 *)0x04001050,
                             firstTargetPixels,
                             secondTargetPixels,
                             evaCoefficient,
                             evbCoefficient,
                             brightnessCoefficient);
}
