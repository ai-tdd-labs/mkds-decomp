// PURPOSE: Configures a driver context's sound callbacks for the current race state.

typedef struct DriverContext {
    char pad_00[0x2c];
    void (*start_callback)(void);
    void (*update_callback)(void);
    char pad_34[0x74 - 0x34];
    unsigned short racer_id;
    char pad_76[0x7c - 0x76];
    unsigned int flags;
} DriverContext;

typedef struct PitchCallbackTarget {
    char pad_00[0x3c];
    void (*pitch_callback)(void);
} PitchCallbackTarget;

extern int GetCurrentSceneId(void);
extern void SfxStart_ForGhost(void);
extern void SfxStart_ForNonGhost(void);
extern void SfxUpdate_Fn(void);
extern void ComputePitchOffset_Race(void);
extern void ComputePitchOffset_NonRace(void);
extern void *data_021759c0;

void DriverContext_CreateSub450_1(DriverContext *context, PitchCallbackTarget *target)
{
    if ((context->flags & 4) != 0) {
        context->start_callback = SfxStart_ForGhost;
    } else {
        context->start_callback = SfxStart_ForNonGhost;
    }
    context->update_callback = SfxUpdate_Fn;

    if (GetCurrentSceneId() != 2 &&
        context->racer_id == *(signed char *)((char *)data_021759c0 + 0x62)) {
        target->pitch_callback = ComputePitchOffset_Race;
    } else {
        target->pitch_callback = ComputePitchOffset_NonRace;
    }
}
