/* PURPOSE: Decides whether to fire a driver's crash/reaction effect and, if
 * so, triggers it.
 *
 * arg1 is a pointer to a driver/object struct. The function bails out early
 * (does nothing) if any of these hold:
 *   - f12c is 0 (feature disabled / not applicable),
 *   - f78 with its top two bits and bottom five bits masked off is already
 *     >= 1000000 (some counter has saturated),
 *   - the u16 field at f118 is 0, or is greater than 0x1c (out of range).
 * Otherwise it calls func_020e53ac on the sub-object at offset 0xe8 with a
 * mode of 0, which probably starts the actual reaction/effect.
 */

typedef struct {
    unsigned char pad000[0x78];
    unsigned int f78; /* flags/counter; masked with ~0xc000001f and compared to 1000000 */
    unsigned char pad07c[0xe8 - 0x7c];
    unsigned char fe8[0x118 - 0xe8]; /* sub-object passed to func_020e53ac */
    unsigned short f118; /* range/state value, must be in (0, 0x1c] */
    unsigned char pad11a[0x12c - 0x11a];
    int f12c; /* enable flag */
} Obj020a9c54;

extern void func_020e53ac(void *obj, int mode);

void func_020a9c54(int unused, Obj020a9c54 *obj) {
    if (obj->f12c == 0) {
        return;
    }

    unsigned short state;

    if ((int)(obj->f78 & ~0xc000001fu) >= 1000000) {
        return;
    }

    state = obj->f118;
    if (state == 0) {
        return;
    }

    if (state > 0x1c) {
        return;
    }

    func_020e53ac(&obj->fe8, 0);
}
