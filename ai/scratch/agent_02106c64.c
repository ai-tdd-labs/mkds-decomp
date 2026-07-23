/*
 * func_02106c64 — sound/race-state reset helper (probably "resume race audio").
 * Sets the sound-scene state word to 2, re-applies the master volume to the
 * music player, unmutes all tracks, then (if a pause flag was set) restores
 * tempo/fade of the music handle and clears the flag. Finally re-applies the
 * current volume to 12 fixed sound handles plus a dynamic table of handles.
 * No arguments, no return value.
 */

typedef unsigned int u32;
typedef unsigned char u8;

/* state block: +0xc = int state, +0x17 = byte flag */
typedef struct {
    u8 pad0[0xc];
    int stateC;      /* 0xc */
    u8 pad10[0x7];   /* 0x10..0x16 */
    u8 flag17;       /* 0x17 */
} Struct_0217c814;

/* fade/volume block: +0x4 = fx32 value (>>12 to int) */
typedef struct {
    int unk0;
    int fx4;         /* 0x4 */
} Struct_0217d234;

/* mode block: +0x4 = int mode */
typedef struct {
    int unk0;
    int mode4;       /* 0x4 */
} Struct_0217d084;

/* handle table: count @0, base ptr @0xc, stride @0x10 */
typedef struct {
    int count;       /* 0x0 */
    int unk4;
    int unk8;
    char *base;      /* 0xc */
    int stride;      /* 0x10 */
} Struct_0217c7c4;

extern Struct_0217c814 data_0217c814;
extern int data_0217d070;              /* music player object */
extern int data_0217d07c;              /* music sound handle */
extern int data_0217c81c;              /* a sound handle */
extern int data_0217c78c;              /* pause-pending flag */
extern Struct_0217d234 data_0217d234;
extern Struct_0217d084 data_0217d084;
extern int data_0217c838[12];          /* 12 sound handles (4 bytes each) */
extern Struct_0217c7c4 data_0217c7c4;

extern int func_0210dc48(void);                      /* get current volume */
extern void func_0210d590(int *player, int vol);
extern void NNS_SndPlayerSetTrackMute(int *handle, u32 trackBitMask, int flag);
extern void func_0212c6f0(int *handle, int vol);     /* set player volume */
extern void func_0210d5c0(int *player);
extern void func_0212c678(int *handle, int tempo);
extern void func_0212c494(int *handle, int frames);
extern void func_0210faac(void);
extern void func_0210d9a0(Struct_0217d084 *p, int mode);

void func_02106c64(void)
{
    int i;
    int vol;   /* declared before j: puts vol in r7, counter j in r6 */
    int j;
    char *p;

    data_0217c814.stateC = 2;
    func_0210d590(&data_0217d070, func_0210dc48());
    NNS_SndPlayerSetTrackMute(&data_0217d07c, 0xFFFF, 0);
    func_0212c6f0(&data_0217c81c, 0);

    if (data_0217c78c != 0) {
        if (data_0217c814.stateC == 1) {
            func_0210d5c0(&data_0217d070);
            func_0212c678(&data_0217d07c, data_0217d234.fx4 >> 12);
            func_0212c494(&data_0217d07c, 300);
            func_0210faac();
        }
        data_0217c78c = 0;
    }

    data_0217c814.flag17 = 0;
    if (data_0217d084.mode4 == 2) {
        func_0210d9a0(&data_0217d084, 3);
    }

    for (i = 0; i < 12; i++) {
        func_0212c6f0(&data_0217c838[i], func_0210dc48());
    }

    vol = func_0210dc48();
    p = data_0217c7c4.base;
    for (j = 0; j < data_0217c7c4.count; j++) {
        func_0212c6f0((int *)p, vol);
        p += data_0217c7c4.stride;
    }
}
