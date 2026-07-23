// PURPOSE: Enables alpha blending on the top screen.
typedef unsigned int u32;

extern void G2x_SetBlendAlpha_(volatile u32 *bldcnt_bldalpha,
                               int first_target_pixels,
                               int second_target_pixels,
                               int eva_coefficient,
                               int evb_coefficient);

void EnableAlphaSetBldcntBldalphaTop(int first_target_pixels,
                                     int second_target_pixels,
                                     int eva_coefficient,
                                     int evb_coefficient)
{
    G2x_SetBlendAlpha_((volatile u32 *)0x04000050,
                       first_target_pixels,
                       second_target_pixels,
                       eva_coefficient,
                       evb_coefficient);
}
