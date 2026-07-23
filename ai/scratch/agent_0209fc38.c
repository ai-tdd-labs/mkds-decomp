/*
 * PURPOSE: Reset the 19-slot counter table and re-seed slot 0 with a fresh value.
 */

extern int data_0217b1ac[19];

extern int func_0209bf8c(void);

void func_0209fc38(void)
{
    int i;

    for (i = 0; i < 0x13; i++)
    {
        data_0217b1ac[i] = 0;
    }

    data_0217b1ac[0] = func_0209bf8c();
}
