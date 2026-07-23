// PURPOSE: Clears a wave entry that points at the sound data being released.
// The data address, its size, and the wave entry are supplied by the caller.
// It probably removes the entry before sending the sound-system release command.

typedef unsigned int u32;
typedef signed int s32;

typedef struct SNDWaveArc SNDWaveArc;

extern const void *SND_GetWaveDataAddress(const SNDWaveArc *waveArc, s32 index);
extern void SND_SetWaveDataAddress(SNDWaveArc *waveArc, s32 index, const void *waveData);
extern void func_02020990(u32 parameter1, u32 parameter2);

void AndAndAnotherSoundDtorFn(u32 waveData, u32 size, SNDWaveArc *waveArc, s32 index)
{
    if (waveData == (u32)SND_GetWaveDataAddress(waveArc, index)) {
        SND_SetWaveDataAddress(waveArc, index, 0);
    }

    func_02020990(waveData, waveData + size);
}
