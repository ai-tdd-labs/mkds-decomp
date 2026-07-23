typedef signed short s16;

typedef struct StructHD {
    char pad_000[0x1C];
    int field_01C;
    char pad_020[0x200 - 0x20];
    unsigned short field_200;
    char pad_202[0x218 - 0x202];
    void *field_218;
} StructHD;

extern void *data_021759c0;
extern void StructHD_SomeFn_11(StructHD *obj, s16 value);
extern void GetDriverMaybeSfxPosition(void *position, unsigned short index);
extern void StructHD_SomeLookAt(void *obj);

void StructHD_SomeFn_3(StructHD *obj)
{
    // PURPOSE: Updates the high-detail object's sound position and view state.
    StructHD_SomeFn_11(obj, *(s16 *)((char *)obj->field_218 + 0x42));

    if (*(int *)((char *)data_021759c0 + 0xC) == 5) {
        obj->field_200 = (*(int *)((char *)obj->field_218 + 0x2C) >> 12) - 1;
        GetDriverMaybeSfxPosition((char *)obj + 0x18, obj->field_200);
        obj->field_01C += *(int *)((char *)obj->field_218 + 0x1C);
    } else {
        GetDriverMaybeSfxPosition((char *)obj + 0x18, obj->field_200);
        obj->field_01C += 0x6000;
    }

    StructHD_SomeLookAt(obj);
}
