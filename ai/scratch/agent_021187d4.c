// PURPOSE: Queues the selected sound table entry for loading.
// This function takes no arguments.
// It probably skips the request while shared mode two is active, then marks
// the sound work as pending.

typedef struct SoundWork {
    unsigned char pad_00[0x44];
    int field_44;
    unsigned char pad_48[0x78 - 0x48];
    short field_78;
    unsigned char pad_7a[0x7c - 0x7a];
    int field_7c;
} SoundWork;

extern SoundWork *data_0217d360;
extern unsigned char data_0215ca1c[];
extern int func_020d0efc(int cupIndex);

#pragma optimize_for_size on

void func_021187d4(void)
{
    if (*(volatile unsigned short *)0x027FFC40 != 2) {
        func_020d0efc(((int *)(data_0215ca1c + (data_0217d360->field_44 << 4)))[data_0217d360->field_78]);
        data_0217d360->field_7c = 1;
    }
}
