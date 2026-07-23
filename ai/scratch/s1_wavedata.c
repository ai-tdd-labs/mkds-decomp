typedef unsigned int u32;
typedef unsigned char u8;
typedef signed int s32;

void Sound_LockMutex(void);
void Sound_UnlockMutex(void);

/* MKDS revision of the SDK: waveOffsets at +0x3C (pokediamond has a different layout) */
typedef struct SNDWaveArc {
    u8 pad[0x3c];
    u32 waveOffsets[1];
} SNDWaveArc;

const void *SND_GetWaveDataAddress(const SNDWaveArc *waveArc, s32 index) {
    u32 retval;
    Sound_LockMutex();
    retval = waveArc->waveOffsets[index];
    if (retval != 0) {
        if (retval < 0x2000000)
            retval = (u32)&((u8 *)waveArc)[retval];
    } else {
        retval = 0;
    }
    Sound_UnlockMutex();
    return (const void *)retval;
}
