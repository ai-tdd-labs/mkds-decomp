// PURPOSE: Formats text into a limited buffer.
// Arguments: destination buffer, buffer size, format text, and extra values.
// This wrapper probably prepares the variable arguments for the formatter.

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((unsigned int)&(last) & ~3) + 4))

extern int SomeSnprintfImpl(char *dst, unsigned int size, const char *fmt, va_list args);

int _snprintf(char *dst, unsigned int size, const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    return SomeSnprintfImpl(dst, size, fmt, args);
}
