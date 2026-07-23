/* PURPOSE: Builds the course point connection graph.
 *
 * Takes the course heap, allocates one graph node per POIT record, and clears
 * every node. It then follows the PATH records to connect all reachable nodes,
 * including disconnected paths that were not reached from the first path.
 */

typedef struct NkmPointRecord {
    unsigned char data[0x18];
} NkmPointRecord;

typedef struct NkmPathRecord {
    unsigned short firstPointIndex;
    unsigned short pointCount;
    unsigned char nextPathIndices[3];
    unsigned char previousPathIndices[3];
    unsigned char pad_0a[2];
} NkmPathRecord;

typedef struct CoursePointNode CoursePointNode;

struct CoursePointNode {
    CoursePointNode *nextNodes[3];
    CoursePointNode *previousNodes[3];
    NkmPointRecord *point;
    void *pointData;
    void *pointSettings;
    unsigned short nextNodeCount;
    unsigned short previousNodeCount;
};

typedef struct CoursePointGraph {
    CoursePointNode *nodes;
    CoursePointNode *firstNode;
    CoursePointNode *loopEndNode;
} CoursePointGraph;

typedef struct CoursePathState {
    unsigned char pad_000[0x64];
    NkmPointRecord *points;
    unsigned short pointCount;
    unsigned short pad_06a;
    NkmPathRecord *paths;
    unsigned short pathCount;
    unsigned char pad_072[0x2e];
    CoursePointGraph pointGraph;
} CoursePathState;

extern CoursePathState *data_02175620;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void func_02042d34(CoursePointNode *previousNode,
                         NkmPathRecord *path,
                         unsigned short pointIndex);

void func_02042c3c(void *heap)
{
    CoursePathState *state = data_02175620;
    NkmPathRecord *firstPath = state->paths;
    CoursePointGraph *graph = &state->pointGraph;
    int pointIndex;

    graph->nodes = Mem_AllocateHeap(
        heap, state->pointCount * sizeof(CoursePointNode));
    graph->firstNode = &graph->nodes[firstPath->firstPointIndex];

    for (pointIndex = 0; pointIndex < data_02175620->pointCount; pointIndex++) {
        CoursePointNode *node = &graph->nodes[pointIndex];
        int connectionIndex;

        for (connectionIndex = 0; connectionIndex < 3; connectionIndex++) {
            node->nextNodes[connectionIndex] = 0;
            node->previousNodes[connectionIndex] = 0;
        }

        node->nextNodeCount = 0;
        node->previousNodeCount = 0;
        node->point = 0;
        node->pointSettings = 0;
        node->pointData = 0;
    }

    {
        NkmPathRecord *loopEndPath =
            &data_02175620->paths[firstPath->previousPathIndices[0]];

        graph->loopEndNode =
            &graph->nodes[loopEndPath->firstPointIndex
                          + loopEndPath->pointCount - 1];
    }

    func_02042d34(graph->loopEndNode, firstPath,
                  firstPath->firstPointIndex);

    {
        unsigned short pathIndex;

        for (pathIndex = 0; pathIndex < data_02175620->pathCount; pathIndex++) {
            NkmPathRecord *path = &data_02175620->paths[pathIndex];

            if (graph->nodes[path->firstPointIndex].nextNodeCount == 0) {
                func_02042d34(0, path, path->firstPointIndex);
            }
        }
    }
}
