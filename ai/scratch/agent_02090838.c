// PURPOSE: Updates the tracked source object when it changes.
// The first argument probably stores the currently tracked source at offset 0x04.
// If the source differs, its stored halfword at offset 0x24 is passed to the setup routine.

#pragma optimize_for_size on

typedef struct Source Source;

typedef struct Tracker {
    unsigned char pad_00[0x04];
    Source *source;
    unsigned char pad_08[0x1c];
    unsigned short flag;
} Tracker;

extern void func_0207ffa4(Tracker *tracker, unsigned short flag, Source *source);

void func_02090838(Tracker *tracker, Source *source)
{
    if (tracker->source != source) {
        func_0207ffa4(tracker, tracker->flag, source);
    }
}
