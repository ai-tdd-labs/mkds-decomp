// PURPOSE: Resets the player input units and enables wireless input for active players.
// All eight input units receive the standard key-repeat configuration and have
// their recorder, touch state, virtual keys, and mode reset. If the wireless
// context is active, participating players are probably switched to mode 4.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct InputRecorder {
    u8 bytes[0x10];
} InputRecorder;

typedef struct InputTouchState {
    u8 bytes[0x14];
} InputTouchState;

typedef struct InputUnit {
    u8 padding_00[0x28];
    InputRecorder recorder;
    u32 field_38;
    u32 mode;
    u16 virtual_keys;
    u16 key_mask;
    u32 field_44;
    InputTouchState touch;
} InputUnit;

typedef struct WirelessContext {
    u32 state;
    u32 mode;
    u8 padding_0008[0x15f6 - 0x8];
    u8 active_player_mask;
    u8 padding_15f7[0x1e8c - 0x15f7];
    u16 player_ids[8];
} WirelessContext;

typedef struct InputAccumulator {
    u8 padding_00[8];
    u32 field_08;
    u32 field_0c;
} InputAccumulator;

extern InputUnit data_02175628[];
extern InputAccumulator *volatile data_02175624;
extern WirelessContext *data_0217aa00;

extern void StructCY_SomeFn(InputUnit *unit);
extern void StructCY_SomeFn_0(InputUnit *unit, u16 mask, u16 first_delay,
                              u16 repeat_delay);
extern void StructCYB_SomeFn(InputRecorder *recorder);
extern void StructCYA_SomeFn(InputTouchState *touch);

void func_02043410(void)
{
    u16 i;
    WirelessContext *context;
    int active;

    for (i = 0; i < 8; i++) {
        StructCY_SomeFn(&data_02175628[i]);
        StructCY_SomeFn_0(&data_02175628[i], 0xff3, 0x1e, 0xa);
        data_02175628[i].mode = 0;
        data_02175628[i].virtual_keys = 0;
        data_02175628[i].field_44 = 0;
        data_02175628[i].key_mask = 0x2fff;
        StructCYB_SomeFn(&data_02175628[i].recorder);
        StructCYA_SomeFn(&data_02175628[i].touch);
    }

    context = data_0217aa00;
    active = 0;
    if (((context == 0) ? 0 : context->state) != 0) {
        if (context->mode != 13) {
            active = 1;
        }
    }

    if (active != 0) {
        for (i = 0; i < 8; i++) {
            if ((context->active_player_mask &
                 (1 << context->player_ids[i])) != 0) {
                data_02175628[i].mode = 4;
            }
        }
    }

    data_02175624->field_08 = 0;
    data_02175624->field_0c = 0;
}
