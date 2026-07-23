/* Converts a 64-bit value to a base-32 string (5 bits per character, MSB
 * first) with digit table "0123456789abcdefghijklmnopqrstuv" (data_0216f2b0).
 * n = (bits+4)/5 characters + NUL terminator in buf. Probably for
 * encoding/displaying ghost exchange codes. */
extern char data_0216f2b0[];

void func_0215286c(unsigned long long val, int bits, char *buf) {
    char * volatile vbuf = buf;
    int i;
    int n = (bits + 4) / 5;
    char *digits = data_0216f2b0;
    i = 0;
    if (i < n) {
        char *p = vbuf + n;
        do {
            *(p - 1 - i) = digits[val & 0x1f];
            val >>= 5;
            i++;
        } while (i < n);
    }
    vbuf[n] = 0;
}
