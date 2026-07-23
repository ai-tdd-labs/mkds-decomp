// PURPOSE: Sets a randomized delay value for the shared scene state.
// In system mode 2, it derives the delay from the current tick count.
// Other modes use the fixed delay value 180.

typedef unsigned short u16;
typedef unsigned long long u64;

extern u64 Os_GetTick(void);
extern u64 Multiply64(u64 left, u64 right);
extern unsigned char *data_0217aa00;

void StructZE_E7Fn_22_1_from_thumb(void)
{
    if (*(volatile u16 *)0x027ffc40 == 2) {
        *(u16 *)(data_0217aa00 + 0x1620) =
            (u16)(Multiply64(
                ((Os_GetTick() << 8) & 0xffffffffULL) *
                    0x5d588b656c078965ULL +
                    0x269ec3ULL >> 32,
                180) >> 32) + 120;
    } else {
        *(u16 *)(data_0217aa00 + 0x1620) = 180;
    }
}
