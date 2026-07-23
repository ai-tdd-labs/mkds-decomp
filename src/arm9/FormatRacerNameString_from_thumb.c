// PURPOSE: Formats the name shown for a racer.
// The racer id selects either a saved player name, a character name, or a CPU label.
// The output is cleared first and is probably limited to the display width.

typedef unsigned int u32;
typedef unsigned short u16;

extern u32 IsRacerPlayerOrGhostOrNet(u32 racerId);
extern u32 GetRacerName(u32 racerId);
extern u32 GetRacerCharacterId_0(u32 racerId);
extern u32 GetCurrentRaceMode_0(void);
extern u32 GetRacerCpuIndex(u32 racerId);
extern u32 GetClampedString10LengthForFontIndex0_from_thumb(u16 *string, u16 *scratch);
extern u16 *GetCharacterNameString_from_thumb(u32 characterId, u32 language);
extern void *func_020b47cc(char *path);
extern u16 *Bmg_GetRawStringPointer_from_thumb(void *archive, int messageId);
extern void CopyString16(u16 *dst, u16 *src, int count);
extern void ParticularSnprintf16(u16 *dst, int count, char *format, ...);
extern void SomeStrcat16(u16 *dst, u16 *src, int count);

extern char data_02168100[];
extern char data_0216810c[];

void FormatRacerNameString_from_thumb(u32 racerId, u16 *dst, u32 language)
{
    u16 buffer[22];
    u16 *name;
    u16 i;
    int count;

    for (i = 0; i < 11; i++) {
        dst[i] = 0;
    }

    if (IsRacerPlayerOrGhostOrNet(racerId) != 0) {
        name = (u16 *)GetRacerName(racerId);
        if (name == 0) {
            return;
        }
        if (language != 0) {
            count = 10;
        } else {
            count = GetClampedString10LengthForFontIndex0_from_thumb(name, buffer + 13);
        }
    } else if ((GetCurrentRaceMode_0() == 0) || (GetCurrentRaceMode_0() == 4)) {
        name = GetCharacterNameString_from_thumb(GetRacerCharacterId_0(racerId), language);
        count = 20;
    } else {
        CopyString16(buffer + 2,
                     Bmg_GetRawStringPointer_from_thumb(func_020b47cc(data_02168100), 0x72),
                     9);
        ParticularSnprintf16(buffer, 2, data_0216810c, GetRacerCpuIndex(racerId));
        SomeStrcat16(buffer + 2, buffer, 1);
        name = buffer + 2;
        count = 10;
    }

    if (name != 0) {
        CopyString16(dst, name, count);
    }
}
