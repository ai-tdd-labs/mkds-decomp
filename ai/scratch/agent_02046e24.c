/* PURPOSE: Resumes race state after the system wakes.
 * Takes no arguments and uses the global race-scene state.
 * It does nothing when sleep handling is disabled.
 * It probably wakes the sub-object only when it was put to sleep, then clears that marker.
 */

typedef struct SceneRaceState {
    unsigned char unknown_00[0x30];
    int unknownFlag : 1;
    int sleepHandlingEnabled : 1;
    int subObjectWasPutToSleep : 1;
    int unknownFlags : 29;
    unsigned char unknown_34[8];
    void *subObject;
} SceneRaceState;

extern SceneRaceState *data_021759c4;
extern void Struct59C4Sub_SomeFn_3(void *subObject);

void Scene_Race_PostSleepImpl(void)
{
    SceneRaceState *raceScene = data_021759c4;

    if (!raceScene->sleepHandlingEnabled)
        return;

    if (raceScene->subObjectWasPutToSleep)
        Struct59C4Sub_SomeFn_3(raceScene->subObject);

    /* Do not try to wake the sub-object again on the next post-sleep pass. */
    data_021759c4->subObjectWasPutToSleep = 0;
}
