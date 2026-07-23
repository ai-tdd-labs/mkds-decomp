// PURPOSE: Formats text into a caller-provided buffer.
// The destination and format are passed directly to the formatter.
// Extra formatting arguments are collected and forwarded, probably like sprintf.

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((unsigned int)&(last) & ~3) + 4))

extern int Util_VSPrintF(char *dst, const char *format, va_list args);

int MaybeUtil_SPrintF(char *dst, const char *format, ...) {
    va_list args;

    va_start(args, format);
    return Util_VSPrintF(dst, format, args);
}
