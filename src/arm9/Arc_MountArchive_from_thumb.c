/* Mounts one archive from the static archive table (0x021543e0, stride 0x18)
 * by index, unless it is already mounted (runtime entry +0x68 != 0). Builds
 * the .carc path into a local 0x80 buffer (per-index formatting: course,
 * scene, result, race variants — some depend on the scene id argument),
 * picks a donor heap from a parent entry, mounts via MountArchiveEntryImpl,
 * and recurses on the 'next' field (+0x04, -1 terminated) to mount chained
 * archives. arg0 = archive index (0..18), arg1 = probably current scene id. */

/* Runtime per-archive entry inside the state struct (stride 0x70). */
typedef struct ArcRuntimeEntry {
    char pad_00[0x68];
    void *loaded;   /* +0x68: non-zero when this archive is mounted */
    int f6c;
} ArcRuntimeEntry;

/* Heap references at +0x9b4 (stride 0xc); first word is the heap pointer. */
typedef struct ArcHeapRef {
    void *heap;     /* +0x0 */
    int f4;
    int f8;
} ArcHeapRef;

typedef struct ArcRuntimeState {
    ArcRuntimeEntry entries[22];   /* +0x000 */
    char pad_9a0[0x14];
    ArcHeapRef subs[16];           /* +0x9b4 */
} ArcRuntimeState;
extern ArcRuntimeState *data_021759c8;

/* Probably the current race/scene configuration. */
typedef struct RaceConfig {
    char *courseName;  /* +0x0 */
    int f4;
    int raceMode;      /* +0x8 */
    int sceneId;       /* +0xc: 6 = staff roll */
} RaceConfig;
extern RaceConfig *gRaceConfig;

/* Static archive descriptor table, stride 0x18; each field is accessed via
 * its own base symbol with the full 0x18 stride (column view of the table,
 * so mwcc computes idx*0x18 once and reuses it for every field). */
typedef struct PtrCol18 { char *v; char pad[0x14]; } PtrCol18;
typedef struct IntCol18 { int v; char pad[0x14]; } IntCol18;
typedef struct UintCol18 { unsigned int v; char pad[0x14]; } UintCol18;
typedef struct ScharCol18 { signed char v; char pad[0x17]; } ScharCol18;
extern PtrCol18 data_021543e0[];      /* +0x00: archive path/name */
extern IntCol18 data_021543e4[];      /* +0x04: next archive index or -1 */
extern ScharCol18 data_021543e8[];    /* +0x08: donor heap index or -1 */
extern IntCol18 data_021543ec[];      /* +0x0c: mount arg */
extern IntCol18 data_021543f0[];      /* +0x10: mount arg */
extern UintCol18 data_021543f4[];     /* +0x14: probably heap size */

/* Scene name/size table, stride 8 (same column trick). */
typedef struct PtrCol8 { char *v; int pad; } PtrCol8;
typedef struct UintCol8 { unsigned int v; int pad; } UintCol8;
extern PtrCol8 data_021541a8[];       /* +0x0: scene name */
extern UintCol8 data_021541ac[];      /* +0x4: probably heap size */

extern char data_02165058[];          /* "/data/Scene/StaffRoll.carc" */

extern void FormatCourseCarc_from_thumb(char *dst, char *name, int flag);
extern void FormatResultCarc_from_thumb(char *dst);
extern void FormatSceneArchive_from_thumb(char *dst, char *name);
extern void FormatResultCarcWithLanguage_from_thumb(char *dst);
extern void FormatStaffRollCarcWithLanguage_from_thumb(char *dst);
extern void FormatCarcWithLanguage2_from_thumb(char *dst, char *name);
extern void FormatSceneArchiveWithRaceMode_from_thumb(char *dst, char *name, int mode);
extern void FormatRaceCarcWithLanguage_from_thumb(char *dst, const char *name, int idx);
extern void FormatArchiveWithLanguage_from_thumb(char *name, char *dst);
extern void Util_SNPrintF(char *dst, unsigned int size, const char *fmt, ...);
extern void SomeStrncpy_0(char *dst, const char *src, unsigned int n);
extern void MountArchiveEntryImpl_from_thumb(int idx, char *path, void *heap,
                                             int a4, int a5, int a6,
                                             unsigned int a7);

void Arc_MountArchive_from_thumb(int idx, int scene)
{
    ArcRuntimeState *st;
    void *heap;
    unsigned int size;
    int parent;
    int next;
    int v_f3f0;   /* stack local, later 5th call arg */
    int v_f3ec;   /* stack local, later 6th call arg */
    char buf[0x80] = {0};  /* mwcc emits the inline byte-clear loop */

    heap = 0;
    st = data_021759c8;
    if (st->entries[idx].loaded != 0) {
        return;
    }

    v_f3ec = data_021543ec[idx].v;
    v_f3f0 = data_021543f0[idx].v;
    size = data_021543f4[idx].v;
    parent = data_021543e8[idx].v;
    if (parent != -1) {
        heap = st->subs[parent].heap;
    }

    switch (idx) {
    case 3:
    case 13:
        /* Course archive; flag probably distinguishes multiplayer variant. */
        FormatCourseCarc_from_thumb(buf, gRaceConfig->courseName,
                                    idx != 3 ? 1 : 0);
        break;
    case 5:
        switch (scene) {
        case 2:
            heap = st->subs[2].heap;
            break;
        case 1:
            heap = st->subs[0].heap;
            break;
        case 10:
            heap = st->subs[14].heap;
            break;
        }
        switch (scene) {
        case 10:
            FormatResultCarc_from_thumb(buf);
            break;
        case 2:
            if (gRaceConfig->sceneId == 6) {
                Util_SNPrintF(buf, 0x80, data_02165058);
            } else {
                FormatSceneArchive_from_thumb(buf, data_021541a8[scene].v);
            }
            break;
        default:
            FormatSceneArchive_from_thumb(buf, data_021541a8[scene].v);
            break;
        }
        size = data_021541ac[scene].v;
        break;
    case 9:
        switch (scene) {
        case 2:
            heap = st->subs[3].heap;
            break;
        case 1:
            heap = st->subs[1].heap;
            break;
        case 10:
            heap = st->subs[15].heap;
            break;
        }
        switch (scene) {
        case 10:
            FormatResultCarcWithLanguage_from_thumb(buf);
            break;
        case 2:
            if (gRaceConfig->sceneId == 6) {
                FormatStaffRollCarcWithLanguage_from_thumb(buf);
            } else {
                FormatCarcWithLanguage2_from_thumb(buf, data_021541a8[scene].v);
            }
            break;
        default:
            FormatCarcWithLanguage2_from_thumb(buf, data_021541a8[scene].v);
            break;
        }
        break;
    case 11:
        FormatSceneArchiveWithRaceMode_from_thumb(buf, data_021541a8[scene].v,
                                                  gRaceConfig->raceMode);
        break;
    case 12:
        FormatRaceCarcWithLanguage_from_thumb(buf, data_021541a8[scene].v,
                                              gRaceConfig->raceMode);
        break;
    case 2:
    case 15:
    case 17:
        FormatArchiveWithLanguage_from_thumb(data_021543e0[idx].v, buf);
        break;
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
    case 10:
    case 14:
    case 16:
    case 18:
        /* Byte-offset form (not the column form): keeps mwcc from CSE'ing
         * idx*0x18 with the prologue loads, matching the ROM's recompute. */
        SomeStrncpy_0(buf, *(char **)((char *)data_021543e0 + idx * 0x18),
                      0x80);
        break;
    case 4:
        break;
    }

    if (*(unsigned char *)buf != 0) {
        MountArchiveEntryImpl_from_thumb(idx, buf, heap, 0, v_f3f0, v_f3ec,
                                         size);
    }
    /* Int-cast base + byte offset: not the column form, so idx*0x18 is
     * recomputed here (ROM: muls r5 in place, no callee-saved temp), and the
     * int add makes mwcc load the table base first (pool ldr before muls). */
    next = *(int *)((int)data_021543e4 + idx * 0x18);
    if (next != -1) {
        Arc_MountArchive_from_thumb(next, scene);
    }
}
