/*
 * PURPOSE: Builds a friend-code-style text string from a packed value, a
 * checksum, and a 4-byte tag, formatted as "<32-char><char><char><char><char><32-char>".
 *
 * arg0 (r0/r5): source object passed to FriendCode_GetSomePackedValue_from_thumb
 *               and FriendCode_GetCrcChecksum_from_thumb.
 * arg1 (r1/r4): probably a 32-bit tag value whose 4 bytes are unpacked into
 *               separate printable characters (big-endian byte order).
 * arg2 (r2/r6): destination buffer for the formatted output string.
 *
 * Encodes the packed value into a 43-bit base-32 string (buf1) and the CRC
 * checksum into a 32-bit base-32 string (buf2, offset by 1 char), then
 * formats everything with Util_SNPrintF using "%s%c%c%c%c%s".
 */

extern unsigned long long FriendCode_GetSomePackedValue_from_thumb(int obj);
extern unsigned int FriendCode_GetCrcChecksum_from_thumb(int obj);
extern void func_0215286c(unsigned long long val, int bits, char *buf);
extern int Util_SNPrintF(char *dst, int size, const char *fmt, ...);

extern char data_0216f2a0[]; /* "%s%c%c%c%c%s" */

void FriendCode_SomeFn_7_from_thumb(int a0, unsigned int a1, char *a2)
{
    char buf1[0x14];
    char buf2[0x14];

    func_0215286c(FriendCode_GetSomePackedValue_from_thumb(a0), 0x2b, buf1);
    func_0215286c(FriendCode_GetCrcChecksum_from_thumb(a0), 0x20, buf2 + 1);

    unsigned char c0 = (unsigned char)(a1 >> 0x18);
    unsigned char c1 = (unsigned char)(a1 >> 0x10);
    unsigned char c2 = (unsigned char)(a1 >> 8);
    unsigned char c3 = (unsigned char)(a1);

    Util_SNPrintF(a2, 0x15, data_0216f2a0, buf1, c0, c1, c2, c3, buf2 + 1);
}
