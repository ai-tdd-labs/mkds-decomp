/* PURPOSE: Builds fast lookup entries for the course paths.
 *
 * Takes the heap used to allocate one lookup entry per PATH record.
 * Each entry pairs a PATH record with the first POIT record that belongs to it.
 * The function then recalculates the total path distance.
 */

typedef struct NkmPathRecord {
    unsigned short firstPointIndex;
    unsigned short pointCount;
} NkmPathRecord;

typedef struct NkmPointRecord {
    unsigned char data[0x14];
} NkmPointRecord;

typedef struct LoadedNkmPathEntry {
    NkmPathRecord *path;
    NkmPointRecord *points;
} LoadedNkmPathEntry;

typedef struct CoursePathState {
    unsigned char pad_000[8];
    NkmPathRecord *paths;
    unsigned short pathCount;
    unsigned short pad_00e;
    NkmPointRecord *points;
    unsigned char pad_014[0x80];
    LoadedNkmPathEntry *loadedPaths;
} CoursePathState;

extern CoursePathState *data_02175620;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void ComputeTotalCpatDistance_from_thumb(void);

void PopulatePathEntries_from_thumb(void *heap)
{
    unsigned short pathCount = data_02175620->pathCount;
    unsigned int allocationSize = pathCount * sizeof(LoadedNkmPathEntry);
    NkmPointRecord *points = data_02175620->points;

    if (allocationSize != 0) {
        LoadedNkmPathEntry *entry = Mem_AllocateHeap(heap, allocationSize);
        unsigned short pathIndex;

        data_02175620->loadedPaths = entry;

        for (pathIndex = 0; pathIndex < pathCount; pathIndex++) {
            NkmPathRecord *path = &data_02175620->paths[pathIndex];

            entry->path = path;
            entry->points = points;
            points += path->pointCount;
            entry++;
        }
    } else {
        data_02175620->loadedPaths = 0;
    }

    ComputeTotalCpatDistance_from_thumb();
}
