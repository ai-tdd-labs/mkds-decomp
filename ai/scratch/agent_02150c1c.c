/* Streaming hash "Update" step (probably SHA-1/MD5-style context, size ctx>=0x60).
 * Args: r0=ctx, r1=src data, r2=len. Maintains a 64-bit processed-bit counter
 * (ctx+0x14 lo / ctx+0x18 hi, incremented by len*8), a partial-block fill count
 * (ctx+0x1c) and a 0x40-byte block buffer (ctx+0x20). Full 64-byte blocks are
 * fed to the block-transform through the global function pointer data_0216f26c;
 * unaligned bulk input is staged through the context buffer first. */
typedef unsigned char u8;
typedef unsigned int u32;

extern void Mem_CpuCopy8(const void *src, void *dst, u32 size);

typedef struct HashCtx {
    u8 unk0[0x14];   /* 0x00: probably hash state words */
    u32 count_lo;    /* 0x14: total bits processed, low word */
    u32 count_hi;    /* 0x18: total bits processed, high word */
    u32 fill;        /* 0x1c: bytes currently buffered (< 0x40) */
    u8 buf[0x40];    /* 0x20: partial block staging buffer */
} HashCtx;

/* global pointer to the block transform: (*fn)(ctx, block, 0x40) */
extern void (*data_0216f26c)(HashCtx *ctx, const u8 *block, u32 size);

void func_02150c1c(HashCtx *ctx, const u8 *src, u32 len) {
    u8 *buf = ctx->buf;
    u32 fill;
    u32 lo;
    int blocks;
    u32 n;

    if (len == 0) {
        return;
    }

    /* 64-bit bit counter += len * 8, with manual carry */
    lo = ctx->count_lo + (len << 3);
    if (lo < ctx->count_lo) {
        ctx->count_hi++;
    }
    ctx->count_hi += len >> 29;
    ctx->count_lo = lo;

    fill = ctx->fill;
    if (fill != 0) {
        if (fill + len >= 0x40) {
            /* complete the buffered block, transform it */
            n = 0x40 - fill;
            Mem_CpuCopy8(src, buf + fill, n);
            len -= n;
            src += n;
            (*data_0216f26c)(ctx, buf, 0x40);
            ctx->fill = 0;
        } else {
            /* still not a full block: just append and return */
            Mem_CpuCopy8(src, buf + fill, len);
            ctx->fill += len;
            return;
        }
    }

    if (len >= 0x40) {
        blocks = len & ~0x3f;
        len -= blocks;
        if (((u32)src & 3) == 0) {
            /* aligned: transform straight from the source */
            (*data_0216f26c)(ctx, src, blocks);
            src += blocks;
        } else {
            /* unaligned: stage each block through the context buffer */
            do {
                Mem_CpuCopy8(src, buf, 0x40);
                src += 0x40;
                (*data_0216f26c)(ctx, buf, 0x40);
                blocks -= 0x40;
            } while (blocks > 0);
        }
    }

    ctx->fill = len;
    if (len == 0) {
        return;
    }
    Mem_CpuCopy8(src, buf, len);
}
