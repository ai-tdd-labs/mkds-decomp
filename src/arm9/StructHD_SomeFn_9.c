// PURPOSE: Updates a high-detail object before its regular processing.
// The object contains a pointer at offset 0x218 to a probably configuration-like record.
// Its signed halfword at offset 0x42 is passed to the first update step.
// The following two steps operate on the same object.

typedef signed short s16;

typedef struct StructHD {
    char _pad[0x218];
    void *field_218;
} StructHD;

extern void StructHD_SomeFn_11(StructHD *obj, s16 value);
extern void StructHD_SomeFn_8(StructHD *obj);
extern void StructHD_SomeFn_10(StructHD *obj);

void StructHD_SomeFn_9(StructHD *obj) {
    StructHD_SomeFn_11(obj, *(s16 *)((char *)obj->field_218 + 0x42));
    StructHD_SomeFn_8(obj);
    StructHD_SomeFn_10(obj);
}
