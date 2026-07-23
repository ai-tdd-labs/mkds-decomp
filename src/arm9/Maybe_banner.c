/* Banner text preparation around a screen transition: in mode 2 a
 * direct call; otherwise load "/banner.bmg". If the status field is 1 or 2,
 * it processes the banner buffer and allocates extra state. Finishes with
 * PopulateNextRaceConfig(). */
extern char data_0216478c[];

struct S021759d0 { char pad[0x20]; int f20; };
extern struct S021759d0 *data_021759d0;

extern void func_0204f240(void *a, int b);
extern void *find_buf_fn_from_thumb(char *name);
extern void func_0204e928(void *a, int b, void *c);
extern void AllocateSomeZEStuff_from_thumb(void *a);
extern void PopulateNextRaceConfig(void);

void Maybe_banner(void *arg)
{
    void *buf = 0;

    if ((*(volatile unsigned short *)0x027ffc40) == 2) {
        func_0204f240(arg, 1);
    } else {
        buf = find_buf_fn_from_thumb(data_0216478c);
    }

    int f = data_021759d0->f20;
    int cond = 1;
    if (f != 1) {
        if (f != 2) {
            cond = 0;
        }
    }
    if (cond) {
        func_0204e928(arg, f == 1, buf);
        AllocateSomeZEStuff_from_thumb(arg);
    }

    PopulateNextRaceConfig();
}
