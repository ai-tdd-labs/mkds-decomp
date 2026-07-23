// PURPOSE: Copies the selected saved time record and reports whether it succeeded.
// The first argument selects one of two destinations in the save-data root.
// The second argument supplies the time record to copy; other selectors return zero.

typedef struct SaveDataRoot {
    unsigned char unknown_00[0x14];
    void *time_0;
    void *time_1;
} SaveDataRoot;

extern SaveDataRoot *data_0217aa08;

extern int StructNKPG_CopyToTime_from_thumb(void *destination, void *source);

int func_02056574(int selector, void *source)
{
    int result = 0;

    switch (selector) {
    case 0:
        result = StructNKPG_CopyToTime_from_thumb(data_0217aa08->time_0, source);
        break;
    case 1:
        result = StructNKPG_CopyToTime_from_thumb(data_0217aa08->time_1, source);
        break;
    case 2:
        break;
    }

    return result;
}
