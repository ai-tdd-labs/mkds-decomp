typedef unsigned int u32;

typedef struct GammaFuncsStruct {
    u32 fn1;
    u32 fn2;
    u32 fn3;
    u32 fn4;
    u32 fn5;
    u32 fn6;
} GammaFuncsStruct;

extern u32 *GetAlphaFlagsRef(void);
extern GammaFuncsStruct *GetGammaFuncsRef(void);

void Crt0_Reset32sAndAlphaFlags(void)
{
    // PURPOSE: Clears the alpha flag and all gamma callback slots.
    GammaFuncsStruct *gamma_funcs;

    *GetAlphaFlagsRef() = 0;
    gamma_funcs = GetGammaFuncsRef();
    gamma_funcs->fn1 = 0;
    gamma_funcs->fn2 = 0;
    gamma_funcs->fn3 = 0;
    gamma_funcs->fn4 = 0;
    gamma_funcs->fn5 = 0;
    gamma_funcs->fn6 = 0;
}
