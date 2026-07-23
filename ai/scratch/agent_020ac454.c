/* PURPOSE: Unpacks a 4bpp packed image into 8x8-tiled bytes, one pixel per byte.
 * Arguments: src = packed 4bpp pixel data (2 pixels per byte), dst = output
 * buffer (1 byte per pixel), size = image width/height in pixels (square,
 * probably a texture/character bitmap).
 * For each pixel (x,y) the nibble is written to the NDS 8x8-tile layout:
 * tile index (y/8)*(size/8)+(x/8), 64 bytes per tile, (y&7)*8+(x&7) inside.
 */

typedef unsigned char u8;

void func_020ac454(u8 *src, u8 *dst, int size)
{
    int y;       /* sp+0x0c */
    int half;    /* sp+0x10 */
    int rowbase; /* sp+0x14 */
    int h8;      /* sp+0x18 */
    int c;       /* sp+0x1c */
    int yoff;    /* sp+0x20 */
    int i;       /* r6 */
    int x;       /* r5 */
    int x1;      /* r4 */
    int si;      /* r7 */
    int t;

    half = size / 2; /* bytes per row of packed source */
    y = 0;
    if (size > 0) {
        rowbase = y;
        h8 = size / 8; /* tiles per row */
        do {
            i = 0;
            if (half > 0) {
                x = i;
                x1 = 1;
                c = h8;
                c = ((y / 8) << 6) * c; /* byte offset of the tile row */
                yoff = (y & 7) << 3;
                do {
                    si = i + rowbase;
                    t = x / 8;
                    /* '+ i - i' is a no-op value-wise but forces the adds operand order */
                    dst[yoff + ((x & 7) + (t << 6)) + (c + i - i)] = src[si] & 0xf;
                    t = x1 / 8;
                    dst[yoff + ((x1 & 7) + (t << 6)) + (c + i - i)] = (src[si] >> 4) & 0xf;
                    x += 2;
                    x1 += 2;
                    i++;
                } while (i < half);
            }
            rowbase = rowbase + half;
            y++;
        } while (y < size);
    }
}
