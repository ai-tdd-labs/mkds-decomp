// PURPOSE: Formats text into a bounded destination buffer.
// Arguments are the destination, its size, the format string, and extra values.
// This wrapper probably forwards the collected values to Util_VSNPrintF.

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((unsigned int)&(last) & ~3) + 4))

extern int Util_VSNPrintF(char *dst, int size, const char *fmt, va_list args);

int Util_SNPrintF(char *dst, int size, const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    return Util_VSNPrintF(dst, size, fmt, args);
}
