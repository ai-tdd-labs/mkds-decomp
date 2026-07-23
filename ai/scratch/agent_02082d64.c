/* PURPOSE: Updates a kart/driver's on-screen position and status flags once per frame.
 *
 * Takes one object pointer (the kart's screen entity). It picks a driver id from
 * three small byte fields (probably: which slot/lane, and two candidate ids), asks
 * GetDriverEntry for that driver's data entry, then copies three scaled world-space
 * coordinates (>>4) into the object's position fields (0x28/0x2c/0x30).
 * It also folds a "valid/visible" bit (bit 3 of flags at 0x24) based on the id
 * checks plus a driver capability mask (0x00402000), sets bit 0 once a frame
 * counter reaches 50, and advances that counter (0x94).
 */

typedef unsigned char u8;

typedef struct {
    int f0, f4, f8, fc;
} PosT;

typedef struct DriverEntry {
    char pad7c[0x7c];
    int f7c;                    /* 0x7c  capability/flags mask source */
    char pad1d8[0x1d8 - 0x80];
    int f1d8;                   /* 0x1d8 world x */
    int f1dc;                   /* 0x1dc world y */
    int f1e0;                   /* 0x1e0 world z */
} DriverEntry;

typedef union Flags24 {
    int w;
    struct {
        unsigned int b0 : 1;
        unsigned int pad12 : 2;
        unsigned int b3 : 1;
    } bits;
} Flags24;

typedef struct Obj {
    char pad20[0x20];
    PosT **f20;                 /* 0x20 -> pointer to base-position struct */
    Flags24 f24;                /* 0x24 status flags */
    int f28;                    /* 0x28 screen x */
    int f2c;                    /* 0x2c screen y */
    int f30;                    /* 0x30 screen z */
    char pad94[0x94 - 0x34];
    int f94;                    /* 0x94 frame counter */
    u8 f98;                     /* 0x98 */
    u8 f99;                     /* 0x99 */
    u8 f9a;                     /* 0x9a select flag */
} Obj;

extern DriverEntry *GetDriverEntry(int id);

void func_02082d64(Obj *obj)
{
    DriverEntry *entry;
    volatile u8 *p = &obj->f98; /* shared base pointer obj+0x98 */
    int c = p[2];               /* 0x9a select flag */
    unsigned int a = p[1];      /* 0x99 */
    int f94 = obj->f94;
    int e = (c == 0) ? p[0] : p[1];  /* ldrbeq 0x98 then ldrbne 0x99 */
    int valid = 1;
    int arg = e;
    int d1d8, d1dc, d1e0;

    if (a > 8) {
        if (e > 8) valid = 0;
        arg = p[0];             /* reload 0x98 */
    }

    entry = GetDriverEntry(arg);

    d1d8 = entry->f1d8;
    d1dc = entry->f1dc;
    d1e0 = entry->f1e0;
    obj->f28 = (d1d8 >> 4) + (*obj->f20)->f4;
    obj->f2c = (*obj->f20)->f8 + (d1dc >> 4);
    obj->f30 = (*obj->f20)->fc + (d1e0 >> 4);

    if (entry->f7c & 0x00402000)
        valid = 0;

    {
        int *fp;
        obj->f24.bits.b3 = (valid == 0);   /* bitfield -> and #1, bic #8, orr <<3 */
        fp = &obj->f24.w;

        if ((unsigned)(f94 + 1) >= 0x32u)
            *fp = (*fp & ~1) | 1;
    }

    obj->f94 = f94 + 1;
}
