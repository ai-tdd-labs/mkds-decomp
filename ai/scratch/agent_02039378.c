// PURPOSE: Keeps a scrolling position inside its allowed range.
/* The first argument is an index and the second selects one of three origins.
 * The position probably wraps by the configured step when it reaches the end.
 */

typedef struct ScrollBounds {
    unsigned int start;
    unsigned int end;
    unsigned int alternateStart;
    unsigned int reverseStart;
    unsigned int unused10;
    unsigned int step;
} ScrollBounds;

extern ScrollBounds data_021755c0;
extern int MaybeBoundsCheck(int value, int limit);

void func_02039378(int index, int mode)
{
    unsigned int position;
    int step = data_021755c0.step;

    switch (mode) {
    case 0:
        position = index * step + data_021755c0.start;
        break;
    case 1:
        position = index * step + data_021755c0.alternateStart;
        break;
    case 2:
        position = data_021755c0.reverseStart - index * step;
        break;
    }

    {
        unsigned int start = data_021755c0.start;
        if (position < start) {
            position = start;
        }
        if (data_021755c0.end < position + step) {
            position = MaybeBoundsCheck(data_021755c0.end - start, step) * step + start;
        }
    }
    data_021755c0.alternateStart = position;
}
