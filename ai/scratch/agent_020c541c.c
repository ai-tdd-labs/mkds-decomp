// PURPOSE: Draws the animated race-goal position sprite.
// The OAM buffer receives one sprite for the current finishing position.
// The shared race-goal state controls its cell, timing, and horizontal motion.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 attribute_0;
    u32 attribute_1;
} OamEntry;

typedef struct {
    OamEntry entries[128];
    u16 count;
    u16 padding_402;
} OamBuffer;

typedef struct {
    int unknown_00;
    int frame;
    int unknown_08[3];
    int threshold;
    int position;
} RaceGoalState;

extern RaceGoalState *data_0217b3f0;

extern int ComputeValueInterpolation_from_thumb(
    int mode, int start, int end, int frame, int duration);
extern void *GetB3C4_Cell_RaceGoalMrM(int position);
extern int MaybeMakeOamSlot(
    void *entry, u16 remaining, void *cell, int unused,
    int *attributes, int unused2, int enabled);

void func_020c541c(OamBuffer *oam)
{
    int attributes[2];
    int cell_index;
    int offset;
    int frame;
    int position;
    void *cell;

    frame = data_0217b3f0->frame;
    offset = ComputeValueInterpolation_from_thumb(
        1, -0x80, 0, frame, 0x14);

    if (data_0217b3f0->threshold != 9
        && data_0217b3f0->position > data_0217b3f0->threshold
        && frame >= 0x1e
        && frame - 0xa < 0x54
        && (frame - 0xa) % 0xc >= 8) {
        return;
    }

    position = data_0217b3f0->position;
    switch (position) {
    case 0:
        cell_index = 7;
        break;
    case 1:
        cell_index = 6;
        break;
    case 2:
        cell_index = 5;
        break;
    case 3:
        cell_index = 4;
        break;
    case 4:
        cell_index = 3;
        break;
    case 5:
        cell_index = 2;
        break;
    case 6:
        cell_index = 1;
        break;
    case 7:
        cell_index = 0;
        break;
    }

    if (position >= 8) {
        return;
    }

    cell = GetB3C4_Cell_RaceGoalMrM(cell_index);
    attributes[0] = (offset + 0x80) << 12;
    attributes[1] = 0x60000;

    oam->count += MaybeMakeOamSlot(
        &oam->entries[oam->count],
        (u16)(0x80 - oam->count),
        cell,
        0,
        attributes,
        0,
        1);
}
