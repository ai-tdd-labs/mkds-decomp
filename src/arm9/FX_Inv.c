extern void *FX_InvAsync(void *a0);
extern void FX_GetDivResult(void *a0);

void FX_Inv(void *a0) {
    FX_GetDivResult(FX_InvAsync(a0));
}
