/* Registers a "finish/kill" style event for the local racer, then walks every
 * active racer to notify them, and finally resets a few race-state fields.
 *
 * data_0217d384 points to a large race-state struct. Relevant fields:
 *   +0x1c    : array of per-racer sub-structs (stride 0x80)
 *   +0x1950  : int  (reset to 0xa at the end)
 *   +0x1980  : int  (reset to 0)
 *   +0x19aa  : u8   (reset to 0)
 *   +0x19ab  : u8   (reset to 0)
 *   +0x1e10  : array of 0x44-byte event entries
 *   +0x1f53  : u8   racer count
 *   +0x1f55  : u8   active-racer bitmask
 *
 * If the local racer index is valid (< count) an event entry is filled in for
 * a racer picked by func_0219bb50() and func_021a32a0 is invoked. Then, when
 * func_021225ac(0x78) returns non-zero, every active racer other than the one
 * returned by func_0219bb50() is notified via func_021a3264 (a zero return
 * aborts early). Finally the race-state fields are reset. */

typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* one 0x44-byte event entry at struct+0x1e10 */
typedef struct {
    int f0;         /* 0x00: event type (7) */
    int f4;         /* 0x04: 0x44 (probably entry size) */
    u8 f8;          /* 0x08: racer chosen by func_0219bb50 */
    u8 f9;          /* 0x09: local racer index */
    u8 fa;          /* 0x0a: active-racer bitmask snapshot */
    u8 rest[0x44 - 0x0b];
} Entry;

extern u8 *data_0217d384;

extern int GetSomeRacerIndex(void);
extern int func_0219bb50(void);
extern void func_021a32a0(int racer, Entry *e);
extern int func_021225ac(int a);
extern int func_021a3264(int racer, u8 *sub, int size);

void func_02122bf0(void)
{
    int index;
    int a;
    u8 i;

    index = GetSomeRacerIndex();
    if ((u32)index < data_0217d384[0x1f53]) {
        int b;
        u8 *ep;
        a = func_0219bb50();
        b = func_0219bb50();
        /* cache the entry-array base (global + 0x1e10) as a byte pointer so all
         * field stores of entry b share one base load; the (Entry *)ep cast
         * indexing keeps the first field store reg+reg indexed and the array
         * scaling constant (0x44) in the same register the ROM uses */
        ep = data_0217d384 + 0x1e10;
        ((Entry *)ep)[b].f0 = 7;
        ((Entry *)ep)[b].f4 = 0x44;
        ((Entry *)ep)[b].f8 = a;
        ((Entry *)ep)[b].f9 = index;
        /* flags read goes through the global -> ROM reloads the base here */
        ((Entry *)ep)[b].fa = data_0217d384[0x1f55];
        /* notify a second racer picked by func_0219bb50 (fresh global reload) */
        func_021a32a0(index, &((Entry *)(data_0217d384 + 0x1e10))[func_0219bb50()]);
    }

    if (func_021225ac(0x78) == 0)
        return;

    for (i = 0; (u32)i < data_0217d384[0x1f53]; i++) {
        if (i == func_0219bb50())
            continue;
        if (!(data_0217d384[0x1f55] & (1 << i)))
            continue;
        if (func_021a3264(i, data_0217d384 + 0x1c + (i << 7), 0x80) == 0)
            return;
    }

    data_0217d384[0x19aa] = 0;
    data_0217d384[0x19ab] = 0;
    *(int *)(data_0217d384 + 0x1950) = 0xa;
    *(int *)(data_0217d384 + 0x1980) = 0;
}
