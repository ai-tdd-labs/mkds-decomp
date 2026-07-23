// PURPOSE: Serializes one command packet into the output buffer, copying its payload.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PacketConfig {
    int payloadSize;
    int maxParam;
} PacketConfig;

extern PacketConfig data_0216fdf8;

extern void Mem_CpuCopy8(const void *source, void *destination, u32 size);

u8 *func_0200c16c(u8 *src, u8 *dst)
{
    u8 *out = dst;

    out++;
    *dst = *src;
    switch (*src) {
    case 7:
        *out++ = src[2];
        if (src[2] > data_0216fdf8.maxParam) {
            return 0;
        }
        Mem_CpuCopy8(src + 3, out, data_0216fdf8.payloadSize);
        out += data_0216fdf8.payloadSize;
        break;

    case 9: {
        u8 *lo = out;
        lo[0] = *(u16 *)(src + 2);
        out = lo + 2;
        lo[1] = (*(volatile u16 *)(src + 2) & 0xff00) >> 8;
    }
        Mem_CpuCopy8(src + 4, out, data_0216fdf8.payloadSize);
        out += data_0216fdf8.payloadSize;
        break;

    case 8:
    case 10:
    case 11:
        break;

    default:
        return 0;
    }
    return out;
}
