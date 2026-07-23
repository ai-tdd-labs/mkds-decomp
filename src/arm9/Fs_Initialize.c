// PURPOSE: Initializes the file system once.
// This routine has no arguments and probably prepares ROM file access.
// It skips the mount setup after the initialization flag is set.

extern int data_0216f350;
extern void Fs_InitializeMountRom(int);

void Fs_Initialize(int unused) {
    if (data_0216f350 == 0) {
        data_0216f350 = 1;
        Fs_InitializeMountRom(unused);
    }
}
