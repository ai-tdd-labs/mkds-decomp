extern void *Fs_OverlayInfo_End(void *a0);
extern void func_02028db8(void *a0);

void Fs_OverlayInfo_UnloadImage(void *a0) {
    func_02028db8(Fs_OverlayInfo_End(a0));
}
