// PURPOSE: Adds a sound player entry when one is available.
// The handle points to a probably sound-player entry pointer.
// Empty handles are ignored; the entry and its priority are forwarded.

typedef unsigned char u8;

typedef struct SoundPlayerEntry SoundPlayerEntry;

extern void func_0212bcac(SoundPlayerEntry *newEntry, u8 priority);

void func_0212c5f4(SoundPlayerEntry **handle, u8 priority)
{
    if (*handle == 0) {
        return;
    }

    func_0212bcac(*handle, priority);
}
