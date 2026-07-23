/* PURPOSE: For each item in a list, run a check on it and flag it if the check failed.
 *
 * Arguments: r0=arg0 (per-item context passed straight through), r1=count
 * (how many items to process), r2=arg2 (passed straight through, probably a
 * pointer to the list/owner). Calls func_020d34d4(arg2, arg0) once per item
 * to get a status word back; if bit 0x100 of the status halfword at offset
 * +2 is clear, it calls func_020d2398() to handle/flag the failing item.
 * Does nothing if count <= 0.
 */

typedef struct {
    unsigned short unk0;
    unsigned short flags;
} Status;

extern Status *func_020d34d4(void *a0, void *a1);
extern void func_020d2398(void);

void func_020ac588(void *arg0, int count, void *arg2)
{
    int i = 0;

    if (i < count) {
        do {
            Status *status = func_020d34d4(arg2, arg0);
            if ((status->flags & 0x100) == 0) {
                func_020d2398();
            }
            i++;
        } while (i < count);
    }
}
