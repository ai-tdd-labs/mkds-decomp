// PURPOSE: Clears friend-list menu entries before saving the updated friend data.
// The shared menu state is reset and several groups of display entries are hidden.
// Two table-selected entries also have their primary value cleared before saving.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 field_00;
    u16 field_04;
    u8 _06[0x3a];
} FriendListDisplayEntry;

typedef struct {
    u8 _00[0x30];
    u16 *field_30;
    u8 _34[8];
    FriendListDisplayEntry *field_3c;
    u8 _40[0x10];
    int field_50;
    int field_54;
} FriendListState;

extern FriendListState *data_0217d348;
extern u16 data_0215c3e0[];
extern u16 data_0215c3ec[];
extern u16 data_0215c3f8[];
extern u16 data_0215c404[];
extern u16 data_0215c3bc[];
extern u16 data_0215c3ac[];
extern void WriteFriendListSaveDataSection(void);

void func_021132e4(void)
{
    int i;
    u16 selected;
    int j;

    data_0217d348->field_50 = 8;
    i = 0;
    data_0217d348->field_54 = i;
    selected = data_0217d348->field_30[3];

    data_0217d348->field_3c[0x14].field_04 = 0x100;
    data_0217d348->field_3c[0x15].field_04 = 0x100;
    data_0217d348->field_3c[0x18].field_04 = 0x100;
    data_0217d348->field_3c[0x19].field_04 = 0x100;
    data_0217d348->field_3c[0x19].field_00 = i;
    data_0217d348->field_3c[0x1a].field_04 = 0x100;
    data_0217d348->field_3c[selected + 5].field_04 = 0x100;

    for (; i < 5; i++) {
        data_0217d348->field_3c[data_0215c3e0[i]].field_04 = 0x100;
        data_0217d348->field_3c[data_0215c3ec[i]].field_04 = 0x100;
        data_0217d348->field_3c[data_0215c3f8[i]].field_04 = 0x100;
        data_0217d348->field_3c[data_0215c404[i]].field_04 = 0x100;
        data_0217d348->field_3c[selected + data_0215c3bc[i]].field_04 = 0x100;
    }

    for (j = 0; j < 2; j++) {
        data_0217d348->field_3c[data_0215c3ac[j]].field_00 = 0;
    }

    WriteFriendListSaveDataSection();
}
