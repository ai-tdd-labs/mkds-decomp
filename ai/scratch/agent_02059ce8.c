// PURPOSE: Starts the pending overlay once its file operation has completed.
typedef struct OverlayManager {
    unsigned char padding_00[4];
    int state;
    unsigned char padding_08[0x24];
    unsigned char overlay_info[0x2c];
    unsigned char file[0xc];
    int flags_64;
} OverlayManager;

extern OverlayManager *data_0217aa10;
extern void Fs_OverlayInfo_Start(void *info);
extern int Fs_File_Close(void *file);

int func_02059ce8(void)
{
    int pending;

    if (data_0217aa10->state == 2) {
        return 1;
    }
    if (data_0217aa10->state != 1) {
        return 0;
    }

    if (data_0217aa10->flags_64 & 1) {
        pending = 1;
    } else {
        pending = 0;
    }
    if (pending != 0) {
        return 0;
    }

    Fs_OverlayInfo_Start(data_0217aa10->overlay_info);
    Fs_File_Close(data_0217aa10->file);
    data_0217aa10->state = 2;
    return 1;
}
