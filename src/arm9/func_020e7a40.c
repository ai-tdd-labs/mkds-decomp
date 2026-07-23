/*
 * PURPOSE: Advances a race state handler unless the staff roll is active.
 *
 * Takes no arguments. If the current scene is 6, probably the staff roll,
 * it does nothing; otherwise it moves the global handler to state 4.
 */

typedef struct RaceConfig {
    void *courseName;
    int field_04;
    int raceMode;
    int sceneId;
} RaceConfig;

typedef struct StateDualHandler StateDualHandler;

extern RaceConfig *gRaceConfig;
extern StateDualHandler data_0217b9ec;

extern void StateDualHandler_SetState(StateDualHandler *handler, int state);

void func_020e7a40(void)
{
    if (gRaceConfig->sceneId == 6) {
        return;
    }

    StateDualHandler_SetState(&data_0217b9ec, 4);
}
