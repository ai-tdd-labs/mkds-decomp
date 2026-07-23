// PURPOSE: Records a racer entry unless it belongs to the active racer.
// The first argument is a racer entry and the second is saved with it.
// An already-initialized manager does nothing.  The active racer is handled by
// StructMQRacerEntry_SomeFn_13 instead of being queued.
typedef signed char s8;
typedef unsigned short u16;

typedef struct {
    unsigned char pad00[0x60];
    int count;
    int initialized;
    unsigned char pad68[4];
    int activeHandled;
} RacerEntryManager;

typedef struct {
    unsigned char pad00[0x62];
    s8 racerIndex;
} RaceConfig;

typedef struct {
    unsigned char pad00[0x74];
    u16 racerIndex;
} RacerEntry;

extern RacerEntryManager data_0217ccc0;
extern RaceConfig *gRaceConfig;
extern void StructMQRacerEntry_SomeFn_13(RacerEntry *entry, void *value, int flag, int reason);

void StructMQRacerEntry_SomeFn_41(RacerEntry *entry, void *value)
{
    RacerEntryManager *manager = &data_0217ccc0;

    if (manager->initialized != 0) return;

    if (entry->racerIndex == gRaceConfig->racerIndex) {
        StructMQRacerEntry_SomeFn_13(entry, value, 1, 0x6e);
        manager->activeHandled = 0;
        return;
    }

    ((RacerEntry **)manager)[manager->count] = entry;
    ((void **)((unsigned char *)manager + 0x20))[manager->count] = value;
    manager->count++;
}
