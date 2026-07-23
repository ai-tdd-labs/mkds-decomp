// PURPOSE: Update per-item race data by computing state based on global config.
// Iterates over an array of items and updates fields based on calculations
// from a per-item calculator function and the gRaceConfig global state at offset 0x8.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
typedef long long s64;
typedef unsigned long long u64;

// Structure returned by the calculator
typedef struct {
    u32 field0;      // 0x0
    u32 field4;      // 0x4
    u32 field8;      // 0x8
    u32 fieldC;      // 0xC
    u32 field10;     // 0x10
    u32 field14;     // 0x14
} CalcResult;

// Per-item data
typedef struct {
    u8 unk0[0x9c];      // 0x0-0x9b
    u32 *config_ptr;    // 0x9c - pointer to config/state
    u32 value_a0;       // 0xa0
    u32 value_a4;       // 0xa4
    u32 value_a8;       // 0xa8
    u16 value_ac;       // 0xac
    u8 unk_ae[0x2];     // 0xae-0xaf
    u32 value_b0;       // 0xb0
} Item;

typedef struct {
    Item **array;       // 0x0 - array of Item pointers
    u16 count;          // 0x4 - item count
    u8 pad[2];          // 0x6-0x7
} ItemList;

extern CalcResult *func_020d22d0(void);
extern u32 *gRaceConfig;  // BSS global at 0x021759c0

void func_020968f4(ItemList *list)
{
    u32 counter;
    Item *item_ptr;
    volatile u32 stored_zero;

    if (list == 0) {
        return;
    }

    counter = 0;
    stored_zero = 0;

    goto loop_test;

loop_body:
    item_ptr->value_a8 = 0x1000;

    volatile CalcResult *calc = (volatile CalcResult *)func_020d22d0();

    u64 result = ((u64)calc->field8 * (u64)calc->field0 +
                  (u64)calc->field8 * (u64)calc->field4 +
                  (u64)calc->fieldC * (u64)calc->field0);

    calc->field0 = (u32)result + calc->field10;
    calc->field4 = (u32)(result >> 32) + calc->field14;

    s16 config_val = *(s16 *)((u8 *)item_ptr->config_ptr + 0x28);
    u32 mult_val = calc->field4 * 60;
    s32 calc_val = config_val + ((s32)(mult_val << 16) >> 16) - 30;
    item_ptr->value_ac = (u16)calc_val;

    counter++;

    u32 race_cfg = gRaceConfig[0x8];
    if (race_cfg == 4) {
        item_ptr->value_b0 = 3;
        item_ptr->value_a0 = 0x2000;
        item_ptr->value_a4 = ~0xd000;
    } else {
        item_ptr->value_b0 = stored_zero;
        item_ptr->value_a0 = 0x2000;
        item_ptr->value_a4 = ~0xd000;
    }

loop_test:
    u16 count = list->count;
    if (counter >= count) {
        return;
    }

    item_ptr = list->array[counter];
    if (item_ptr != 0) {
        goto loop_body;
    }
}
