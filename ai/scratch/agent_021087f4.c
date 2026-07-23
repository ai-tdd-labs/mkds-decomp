// PURPOSE: Reloads the selected racer's sound banks when needed.
// The racer identifier is probably zero when no racer-specific sound set is needed.
// It avoids reloading an already active set, otherwise disposing the old resources first.

typedef unsigned short u16;
typedef unsigned int u32;

typedef union RacerSoundLoadValue {
    void *loadedStuff;
    u16 racerId;
} RacerSoundLoadValue;

typedef struct RacerSoundLoadContext {
    RacerSoundLoadValue value;
    u32 state;
} RacerSoundLoadContext;

typedef struct RacerSoundRequest {
    u16 racerId;
    u16 padding;
    u32 state;
} RacerSoundRequest;

extern RacerSoundRequest data_0216c7d8;
extern RacerSoundLoadContext data_0217c77c;
extern void Sound_Context_DisposeLoadedStuff(void *loadedStuff);
extern int MaybeLoadRacerSbnksSwars(int racerId);

int MaybeReloadRacerSbnksSwars(int racerId)
{
    if (racerId == 0) {
        return 1;
    }

    if (data_0216c7d8.state != 0xFF00) {
        if (data_0216c7d8.racerId == racerId) {
            return 1;
        }
    }

    Sound_Context_DisposeLoadedStuff(data_0217c77c.value.loadedStuff);

    data_0216c7d8.state = 0xFF00;
    data_0216c7d8.racerId = 0;
    data_0216c7d8.racerId = racerId;
    data_0216c7d8.state = 0xFE00;

    if (MaybeLoadRacerSbnksSwars(racerId) == 0) {
        return 0;
    }
    return 1;
}
