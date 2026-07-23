// PURPOSE: Updates an object's state every other frame.
// The object is updated only when the mode argument is zero.
// Its byte flags probably select an alternating animation or status state.

typedef unsigned char u8;

typedef struct Obj {
    u8 pad_00[0x9A];
    u8 state;
    u8 frame_count;
} Obj;

extern void func_02082d64(Obj *obj);

void func_02082f94(Obj *obj, int mode)
{
    if (mode != 0) {
        return;
    }

    func_02082d64(obj);

    obj->frame_count++;
    if (obj->frame_count < 2) {
        return;
    }

    obj->state = obj->state == 0 ? 1 : 0;
    obj->frame_count = 0;
}
