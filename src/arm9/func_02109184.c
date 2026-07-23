// PURPOSE: Updates display values from the current position and returns the hardware division result.

typedef int fx32;
typedef unsigned short u16;

typedef struct {
    char pad_00[0x0c];
    int value;
} FallbackData;

typedef struct {
    char pad_00[0x40];
    int value;
} ObjectData;

typedef struct {
    ObjectData *object;
    void *position;
    int horizontal;
    int vertical;
    char pad_10[0x10];
    FallbackData *fallback;
} DisplayData;

extern fx32 func_02073e4c(const void *position);
extern fx32 func_02073e04(const void *position);

int func_02109184(DisplayData *data)
{
    int value;
    void *position;

    if (data->object != 0) {
        value = data->object->value;
    } else {
        value = data->fallback->value;
    }

    *(volatile u16 *)0x040002b0 = 0;
    *(volatile int *)0x040002b8 = value;

    position = data->position;
    data->horizontal = func_02073e4c(position) >> 12;
    data->vertical = func_02073e04(position) >> 12;

    while ((*(volatile u16 *)0x040002b0 & 0x8000) != 0) {
    }

    return *(volatile int *)0x040002b4;
}
