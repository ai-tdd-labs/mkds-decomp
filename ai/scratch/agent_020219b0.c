// PURPOSE: Sets the address used for a wave sound's data.
// Arguments select a wave entry and supply its data address.
// The address is stored and its cache range is cleaned while the sound mutex is held.

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;

typedef struct SNDWaveArc {
    u8 pad[0x3c];
    u32 waveOffsets[1];
} SNDWaveArc;

extern void Sound_LockMutex(void);
extern void Sound_UnlockMutex(void);
extern s32 DC_SomeClean(void *ptr, s32 size);

void SND_SetWaveDataAddress(SNDWaveArc *waveArc, s32 index, const void *waveData) {
    Sound_LockMutex();
    waveArc->waveOffsets[index] = (u32)waveData;
    DC_SomeClean(&waveArc->waveOffsets[index], sizeof(u32));
    Sound_UnlockMutex();
}
