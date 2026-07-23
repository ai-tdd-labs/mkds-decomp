// PURPOSE: Initializes a kart racer data block to its default values.
/*
 * The argument is one racer entry, probably used for the kart model state.
 * It clears its status fields and creates the nested setup block.
 * The small signed fields are probably transform or animation values.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct StructAD00Sub {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    u8 unk_24[0x30];
    int unk_54;
    int unk_58;
    int unk_5C;
    int unk_60;
    int unk_64;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
    s16 unk_76;
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    s16 unk_86;
    s16 unk_88;
    s16 unk_8A;
    s16 unk_8C;
    s16 unk_8E;
    s16 unk_90;
    s16 unk_92;
    s16 unk_94;
    u8 unk_96[0x16];
    int unk_AC;
    int unk_B0;
} StructAD00Sub;

extern void StructAD00SubSub_Create_from_thumb(void *sub);

void StructAD00Sub_Initialize_from_thumb(StructAD00Sub *sub)
{
    sub->unk_00 = -1;
    sub->unk_04 = -1;
    sub->unk_08 = 0;
    sub->unk_0C = 0;
    sub->unk_10 = 0;
    sub->unk_14 = 0;
    sub->unk_18 = 0;
    sub->unk_1C = 0;
    sub->unk_20 = 0;
    StructAD00SubSub_Create_from_thumb(sub->unk_24);
    sub->unk_54 = 0;
    sub->unk_58 = 0;
    sub->unk_5C = 0;
    sub->unk_60 = 0;
    sub->unk_64 = 0;
    sub->unk_68 = 0;
    sub->unk_AC = 0;
    sub->unk_B0 = 0;
    sub->unk_6E = 0;
    sub->unk_6C = sub->unk_6E;
    sub->unk_6A = sub->unk_6C;
    sub->unk_74 = 0;
    sub->unk_72 = sub->unk_74;
    sub->unk_70 = sub->unk_72;
    sub->unk_7A = 0;
    sub->unk_78 = sub->unk_7A;
    sub->unk_76 = sub->unk_78;
    sub->unk_80 = 0;
    sub->unk_7E = sub->unk_80;
    sub->unk_7C = sub->unk_7E;
    sub->unk_86 = 0;
    sub->unk_84 = sub->unk_86;
    sub->unk_82 = sub->unk_84;
    sub->unk_8C = 0;
    sub->unk_8A = sub->unk_8C;
    sub->unk_88 = sub->unk_8A;
    sub->unk_92 = 0;
    sub->unk_90 = sub->unk_92;
    sub->unk_8E = sub->unk_90;
    sub->unk_94 = 0;
}
