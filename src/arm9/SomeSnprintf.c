// PURPOSE: Formats text into a destination buffer without a size limit.
// The function receives a destination, a format string, and extra format values.
// It probably forwards the format work to the shared formatter implementation.

typedef char *va_list;
#define va_start(ap, last) \
    ((ap) = (char *)(((unsigned int)&(last)) & ~3) + 4)

extern int SomeSnprintfImpl(char *dst, unsigned int size, const char *fmt, va_list args);

int SomeSnprintf(char *dst, const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    return SomeSnprintfImpl(dst, (unsigned int)-1, fmt, args);
}
