/* PURPOSE: Calculates the total distance along the course's CPAT route.
 *
 * Takes no arguments and stores both the raw and checked distances globally.
 * The recursive calculation probably applies only when at most one CPAT route
 * is loaded; otherwise both stored distances remain zero.
 */

typedef struct CoursePathState {
    char pad_000[0x20];
    unsigned short cpatRouteCount;
    char pad_022[0xe2];
    int totalCpatDistance;
    int checkedCpatDistance;
} CoursePathState;

extern CoursePathState *data_02175620;

extern int ComputeTotalDistanceRecursively_from_thumb(int pathIndex);
extern int MaybeBoundsCheck(int value, int limit);

void ComputeTotalCpatDistance_from_thumb(void)
{
    int totalDistance = 0;
    int checkedDistance = 0;

    if (data_02175620->cpatRouteCount <= 1) {
        totalDistance = ComputeTotalDistanceRecursively_from_thumb(0);
        checkedDistance = MaybeBoundsCheck(totalDistance, 15000);
    }

    data_02175620->totalCpatDistance = totalDistance;
    data_02175620->checkedCpatDistance = checkedDistance;
}
