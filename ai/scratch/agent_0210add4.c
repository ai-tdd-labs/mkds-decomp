// PURPOSE: Starts queued racer actions after their delays expire.
// The function returns while the racer-entry manager is initialized.
// It pauses briefly after handling the active racer, then scans eight slots.
// Each ready entry probably receives its saved value and a staggered delay.

typedef unsigned int u32;

typedef struct RacerEntry RacerEntry;

typedef struct {
    RacerEntry *entries[8];
    void *values[8];
    u32 timers[8];
    int count;
    int initialized;
    int delay;
    int activeHandled;
} RacerEntryManager;

extern RacerEntryManager data_0217ccc0;
extern void StructMQRacerEntry_SomeFn_13(RacerEntry *entry, void *value,
                                         int flag, int delay);

void func_0210add4(void)
{
    RacerEntryManager *manager = &data_0217ccc0;
    int i;
    int *delay;
    int initialDelay;
    int minimumDelay;
    int flag;

    if (manager->initialized != 0) {
        return;
    }

    if (manager->activeHandled != -1) {
        manager->activeHandled++;
        if (manager->activeHandled >= 0x19) {
            manager->activeHandled = -1;
        }
        return;
    }

    i = 0;
    flag = i;
    delay = &manager->delay;
    initialDelay = 0x5f;
    minimumDelay = 0x1e;

    for (; i < 8; i++) {
        if (manager->entries[i] == 0) {
            continue;
        }

        if (manager->timers[i] == 0) {
            if (i != 0 && manager->timers[i - 1] < 0x14) {
                continue;
            }

            if (i != 0 && manager->timers[i - 1] == 0x14) {
                *delay -= 0xf;
            } else {
                manager->delay = initialDelay;
            }

            if (manager->delay < minimumDelay) {
                manager->delay = minimumDelay;
            }

            StructMQRacerEntry_SomeFn_13(manager->entries[i],
                                         manager->values[i], flag,
                                         manager->delay);
            manager->timers[i]++;
        } else {
            manager->timers[i]++;
        }
    }
}
