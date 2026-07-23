// PURPOSE: Updates ROB's kart palette colors for the current character.
// The first argument is probably the active character-kart record.
// The second argument selects the requested ROB palette variant.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern char data_021550e8[];
extern char data_02155108[];
extern char data_02155008[];
extern void *data_0217ad0c;
extern char data_02155028[];
extern char data_02155038[];
extern char data_02155128[];
extern char data_02155148[];
extern char data_02155058[];
extern char data_02155078[];
extern char data_021550c8[];
extern char data_02154fe8[];

extern int Dict_SomeFn_0(void *dict, char *name);
extern void func_0214c48c(void);
extern void SomeDmaCopy_0(void *dst, u32 offset, u32 size);
extern void func_0214c3c0(void);

void CharacterKart_PatchRobPalette_from_thumb(void *arg, int isP)
{
    u8 *res;
    int faceIdx;
    u8 *dict;
    u8 *entbase;
    int idx;
    u32 eofs;
    u8 *ent;
    u32 esz;
    u32 plttOfs;
    void *dst;
    void *volatile faceDst;
    u32 faceSize;

    if (*(void **)((u8 *)arg + 0xb0) == 0) {
        return;
    }

    if ((u32)(*(int *)((u8 *)arg + 4) - 0x22) <= 1) {
        dst = 0;
        res = *(u8 **)((u8 *)*(void **)((u8 *)arg + 0x14) + 4);

        switch (*(int *)((u8 *)arg + 4)) {
        case 0x22:
            dst = data_021550e8;
            break;
        case 0x23:
            dst = data_02155108;
            break;
        }

        idx = Dict_SomeFn_0(res + *(int *)(res + 8) + 4, data_02155008);
        dict = res + *(int *)(res + 8);
        entbase = dict + 4;
        eofs = *(u16 *)(dict + 0xa);
        ent = entbase + eofs;
        esz = *(u16 *)(entbase + eofs);
        data_0217ad0c = dict + *(int *)(ent + esz * idx + 4);
        plttOfs = (u32)*(u16 *)((u8 *)data_0217ad0c + 0x1c) << 4;

        func_0214c48c();
        SomeDmaCopy_0(dst, plttOfs, 0x20);
        func_0214c3c0();
    }

    if (*(int *)arg == 0xb) {
        res = *(u8 **)((u8 *)*(void **)((u8 *)arg + 0x10) + 4);

        if (isP != 0) {
            idx = Dict_SomeFn_0(res + *(int *)(res + 8) + 4, data_02155028);
            faceIdx = Dict_SomeFn_0(res + *(int *)(res + 8) + 4, data_02155038);
            dst = data_02155128;
            faceDst = data_02155148;
            faceSize = 0x40;
        } else {
            idx = Dict_SomeFn_0(res + *(int *)(res + 8) + 4, data_02155058);
            faceIdx = Dict_SomeFn_0(res + *(int *)(res + 8) + 4, data_02155078);
            dst = data_021550c8;
            faceDst = data_02154fe8;
            faceSize = 0x10;
        }

        dict = res + *(int *)(res + 8);
        entbase = dict + 4;
        eofs = *(u16 *)(dict + 0xa);
        ent = entbase + eofs;
        esz = *(u16 *)(entbase + eofs);
        res = dict + *(int *)(ent + esz * faceIdx + 4);
        dict = dict + *(int *)(ent + esz * idx + 4);
        plttOfs = (u32)*(u16 *)(dict + 0x1c) << 4;

        func_0214c48c();
        SomeDmaCopy_0(dst, plttOfs, 0x20);
        func_0214c3c0();

        plttOfs = (u32)*(u16 *)(res + 0x1c) << 4;
        func_0214c48c();
        SomeDmaCopy_0(faceDst, plttOfs, faceSize);
        func_0214c3c0();
    }
}
