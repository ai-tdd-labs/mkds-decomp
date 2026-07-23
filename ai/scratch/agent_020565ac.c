// PURPOSE: Copies the selected saved time value and returns the result.

typedef struct SaveDataRoot {
    unsigned char unknown_00[0x14];
    void *time_0;
    void *time_1;
} SaveDataRoot;

extern SaveDataRoot *data_0217aa08;

extern int StructNKPG_AnotherCopyToTime_from_thumb(void *time);

int func_020565ac(int selector)
{
    int result = 0;

    switch (selector) {
    case 0:
        result = StructNKPG_AnotherCopyToTime_from_thumb(data_0217aa08->time_0);
        break;
    case 1:
        result = StructNKPG_AnotherCopyToTime_from_thumb(data_0217aa08->time_1);
        break;
    case 2:
        break;
    }

    return result;
}
