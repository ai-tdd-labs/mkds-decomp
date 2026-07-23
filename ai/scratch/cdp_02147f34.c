extern void *FX_DivAsync(void *a0);
extern void FX_GetDivResult(void *a0);

void FX_Div(void *a0) {
    FX_GetDivResult(FX_DivAsync(a0));
}
