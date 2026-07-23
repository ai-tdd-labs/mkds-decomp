// PURPOSE: Updates a racer's animation and state when its flags allow it.
// The racer probably owns animation context and state fields at the offsets below.
// A pending flag starts the animation before the state callback is made.

typedef struct StructMQRacerEntry {
    unsigned char unknown_000[0x48];
    unsigned int flags_048;
    unsigned char unknown_04c[0x30];
    unsigned int flags_07c;
    unsigned char unknown_080[0x34c];
    void *state_3cc;
    unsigned char unknown_3d0[0x1c0];
    void *characterKartContext_590;
} StructMQRacerEntry;

extern void StructMQRacerEntry_SomeFn_7(StructMQRacerEntry *entry, int value,
                                        int zero);
extern void CharacterKartContext_SetNsbtpAnimationProgress(void *context,
                                                           int progress);
extern void StructMQRacerEntry_SomeFn_5(StructMQRacerEntry *entry, void *state,
                                        int zero);

void StructMQRacerEntry_SomeFn_10(StructMQRacerEntry *entry)
{
    if (entry->flags_07c & 0x10) {
        StructMQRacerEntry_SomeFn_7(entry, 1, 0);
        CharacterKartContext_SetNsbtpAnimationProgress(
            entry->characterKartContext_590, 1);
    }

    if (entry->flags_048 & 0x840) {
        return;
    }

    StructMQRacerEntry_SomeFn_5(entry, entry->state_3cc, 0);
}
