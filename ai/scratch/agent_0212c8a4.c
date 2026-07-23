// PURPOSE: Sets the volume values for each enabled sound channel.
// The first argument is probably a sound-channel list and the second is its
// source data base. Each listed channel selects an offset from a shared table.

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct ChannelOffset {
    u32 unused;
    s32 offset;
} ChannelOffset;

typedef struct SoundChannelList {
    u8 unknown_00[0x3c];
    s32 source_base;
    u8 unknown_40[8];
    s32 count;
    u8 channels[1];
} SoundChannelList;

extern ChannelOffset data_0217dd28[];
extern u16 Maybe_helper_0218f4(s32 x);
extern void SND_SetChannelVolume(int channel, int volume, int parameter);

void func_0212c8a4(SoundChannelList *list, s32 source_base)
{
    int index;
    u8 channel;
    u16 value;

    list->source_base = source_base;

    for (index = 0; index < list->count; index++) {
        channel = list->channels[index];
        value = Maybe_helper_0218f4(list->source_base + data_0217dd28[channel].offset);
        SND_SetChannelVolume(1 << channel, value & 0xff, value >> 8);
    }
}
