// PURPOSE: Resets an object's timer/flag fields for a new race lap or checkpoint update.
// Copies two signed 16-bit values from a config sub-struct (pointed to by
// obj+0x9c, at offsets 0x28 and 0x2e) into the object, incrementing the
// second one by 1. Then calls func_020d28e0(obj) to apply the update,
// clears three flag bits, ORs in a global flag mask, and finally sets a
// "state" field to 31 (probably a fixed reset/idle state id).

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

// Config sub-struct reached through obj+0x9c; only the two used fields
// are named, the rest is padding to keep the offsets correct.
typedef struct {
    u8 pad0[0x28];
    s16 field28;   // 0x28
    u8 pad2a[0x4];
    s16 field2e;   // 0x2e
} SubConfig;

typedef struct {
    u8 pad0[0x2];
    u16 flags;         // 0x2
    u8 pad4[0x62];
    u16 state;          // 0x66
    u8 pad68[0x32];
    SubConfig *config;  // 0x9c
    u16 fieldA0;         // 0xa0
    u16 fieldA2;         // 0xa2
} Obj;

extern void func_020d28e0(Obj *obj);

// Global flag mask, read fresh each call (no reloc -> plain data symbol).
extern volatile u16 data_021565ec;

void func_0209ea90(Obj *obj)
{
    obj->flags = obj->flags | data_021565ec;

    obj->fieldA0 = (u16)obj->config->field28;
    obj->fieldA2 = (u16)(obj->config->field2e + 1);

    func_020d28e0(obj);

    obj->flags = obj->flags & ~1;
    obj->flags = obj->flags & ~2;
    obj->flags = obj->flags & ~8;

    obj->state = 0x1f;
}
