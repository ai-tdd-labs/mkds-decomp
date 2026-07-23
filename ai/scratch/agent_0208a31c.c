// PURPOSE: Resets the animations for the selected model group.
// The mode selects one of eight groups in the global model state.
// A missing group records fallback mode nine and stops.
// Modes zero and two probably also select fixed animation variants.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Animation {
    u16 state;
    u8 padding_02[0x10];
    u16 variant;
    u8 padding_14[0x24];
} Animation;

typedef struct AnimationGroup {
    int unknown_00;
    Animation *firstTrack;
    Animation *secondTrack;
    void *sharedTrack;
    u16 count;
} AnimationGroup;

typedef struct AnimationState {
    AnimationGroup *groups[8];
    AnimationGroup *currentGroup;
    u8 padding_24[0x718];
    int mode;
} AnimationState;

extern AnimationState *data_0217b034;
extern void Animation_SetAt(void *animation, int frame);

void func_0208a31c(int mode)
{
    AnimationGroup *group;
    u16 i;
    int frames[3];

    data_0217b034->currentGroup = data_0217b034->groups[mode];
    group = data_0217b034->currentGroup;

    if (group == 0) {
        data_0217b034->mode = 9;
        return;
    }

    data_0217b034->mode = mode;
    i = 0;
    if (i >= group->count) {
        return;
    }

    frames[0] = 0;
    frames[1] = 0;
    frames[2] = 0;

    do {
        int sharedFrame;
        int variant;

        if (group->firstTrack != 0) {
            Animation_SetAt(&group->firstTrack[i], frames[0]);
        }

        if (group->secondTrack != 0) {
            Animation_SetAt(&group->secondTrack[i], frames[1]);
        }

        if (mode == 0 || mode == 2) {
            sharedFrame = mode == 2 ? 1 : frames[2];
            variant = mode == 2 ? 5 : 3;

            Animation_SetAt(group->sharedTrack, (u16)sharedFrame);

            if (group->firstTrack != 0) {
                group->firstTrack[i].state = 2;
                group->firstTrack[i].variant = variant;
            }

            if (group->secondTrack != 0) {
                group->secondTrack[i].state = 2;
                group->secondTrack[i].variant = variant;
            }
        }

        i++;
    } while (i < group->count);
}
