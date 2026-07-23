// PURPOSE: Copies an image into the DS tiled pixel layout.
typedef unsigned char u8;

void func_020ac2fc(u8 *src, u8 *dst, int size)
{
    int y;
    int h8;
    int c;
    int yoff;
    int half;
    int i;
    int x;
    int rowbase;
    int idx;

    half = size / 2;
    y = 0;
    if (size > 0) {
        rowbase = y;
        h8 = size / 8;
        do {
            i = 0;
            if (half > 0) {
                x = i;
                c = h8;
                c = ((y / 8) << 6) * c;
                yoff = (y & 7) << 3;
                do {
                    idx = (yoff + ((x & 7) + ((x / 8) << 6))) + (c + (i - i));
                    idx = idx / 2;
                    dst[idx] = src[i + rowbase];
                    x += 2;
                    i++;
                } while (i < half);
            }
            rowbase = rowbase + half;
            y++;
        } while (y < size);
    }
}
