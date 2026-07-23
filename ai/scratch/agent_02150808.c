/*
 * HMAC-SHA1: computes HMAC of (msg, msglen) with (key, keylen) into out (20 bytes).
 * Args: r0=out digest buffer, r1=msg, r2=msglen, r3=key, [sp]=keylen.
 * Returns early (no output) if any pointer is NULL or any length is 0.
 * Keys longer than the 0x40-byte block are first reduced with SHA1.
 * Callees: func_02150d78=SHA1Init, func_02150c1c=SHA1Update, func_02150a10=SHA1GetHash.
 */

typedef unsigned char u8;

extern void func_02150d78(void *ctx);                    /* SHA1 init */
extern void func_02150c1c(void *ctx, void *data, int n); /* SHA1 update */
extern void func_02150a10(void *ctx, void *digest);      /* SHA1 final (20-byte digest) */

void func_02150808(u8 *out, u8 *msg, int msglen, u8 *key, int keylen)
{
    u8 ipad[0x40];   /* sp+0x00 */
    u8 opad[0x40];   /* sp+0x40 */
    u8 digest[0x14]; /* sp+0x80, kept in r4 */
    u8 ctx[0x68];    /* sp+0x94, SHA1 context */
    int i;
    u8 *dp = digest; /* digest address cached in r4 for the whole function */

    /* five separate guards -> five predicated epilogues in the ROM */
    if (out == 0) {
        return;
    }
    if (msg == 0) {
        return;
    }
    if (msglen == 0) {
        return;
    }
    if (key == 0) {
        return;
    }
    if (keylen == 0) {
        return;
    }

    /* long key: replace by its SHA1 digest */
    if (keylen > 0x40) {
        func_02150d78(ctx);
        func_02150c1c(ctx, key, keylen);
        func_02150a10(ctx, dp);
        key = dp;
        keylen = 0x14;
    }

    /* build inner/outer pads; key advanced as a cursor (post-inc ldrb in ROM),
       key byte loaded twice (u8* aliasing, no CSE) */
    for (i = 0; i < keylen; i++) {
        ipad[i] = *key ^ 0x36;
        opad[i] = *key ^ 0x5c;
        key++;
    }
    for (; i < 0x40; i++) {
        ipad[i] = 0x36;
        opad[i] = 0x5c;
    }

    /* inner hash: H(ipad || msg) */
    func_02150d78(ctx);
    func_02150c1c(ctx, ipad, 0x40);
    func_02150c1c(ctx, msg, msglen);
    func_02150a10(ctx, dp);

    /* outer hash: H(opad || inner) */
    func_02150d78(ctx);
    func_02150c1c(ctx, opad, 0x40);
    func_02150c1c(ctx, dp, 0x14);
    func_02150a10(ctx, out);
}
