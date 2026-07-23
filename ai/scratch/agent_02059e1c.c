// PURPOSE: Waits until the current overlay has started loading.
typedef struct OverlayManager {
    char pad_00[4];
    int state;
    char pad_08[0x2c - 8];
    char overlay_info[0x2c];
    char file[0xc];
    int flags_64;
} OverlayManager;

extern OverlayManager *data_0217aa10;
extern void Fs_OverlayInfo_Start(void *info);
extern int Fs_File_Close(void *file);

void WaitOverlayLoadedStarted(void)
{
    int done;

    do {
        done = 0;
        if (data_0217aa10->state == 2) {
            done = 1;
        } else if (data_0217aa10->state == 1) {
            if ((data_0217aa10->flags_64 & 1) == 0) {
                Fs_OverlayInfo_Start(data_0217aa10->overlay_info);
                Fs_File_Close(data_0217aa10->file);
                data_0217aa10->state = 2;
                done = 1;
            }
        }
    } while (done == 0);
}
