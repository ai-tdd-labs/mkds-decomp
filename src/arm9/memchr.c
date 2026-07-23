typedef unsigned int u32;
typedef unsigned char u8;

void *memchr(const void *src, int val, u32 n) {
    const u8 *p = (const u8 *)src;
    u32 v = val & 0xff;

    while (n != 0) {
        u32 c = *(const u32 *)p & 0xff;
        p += 1;
        if (c == v) {
            return (void *)(p - 1);
        }
        n--;
    }
    return 0;
}
