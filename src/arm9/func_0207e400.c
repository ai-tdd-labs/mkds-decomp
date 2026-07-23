// PURPOSE: Initializes a reaction object and its embedded direction tracker.
// The first argument is the object being initialized and the second is its source data.
// It copies the source index, prepares the embedded tracker, and calculates a scaled value.
// The exact meaning of the source's nested fixed-point value is probably a tuning parameter.

typedef int fx32;
typedef long long fx64;

typedef struct SourceValue {
    char pad00[0x10];
    fx32 value;
} SourceValue;

typedef struct Source {
    char pad00[0x74];
    unsigned short index;
    char pad76[0x2cc - 0x76];
    SourceValue *value;
} Source;

typedef struct DirectionTracker {
    char data[0x20];
} DirectionTracker;

typedef struct ReactionObject {
    Source *source;
    unsigned short index;
    unsigned short mode;
    char pad08[0x88 - 0x08];
    int limit;
    int counter;
    char pad90[0x9c - 0x90];
    fx32 scaled;
    char padA0[0xcc - 0xa0];
    int active;
} ReactionObject;

extern void func_02080d34(DirectionTracker *t, int flag);
extern void func_0207f9cc(ReactionObject *obj, int mode);

void func_0207e400(ReactionObject *obj, Source *source)
{
    int zero = 0;

    obj->source = source;
    obj->index = source->index;
    obj->mode = obj->index % 4;
    obj->limit = 0x1000;
    obj->counter = zero;
    obj->scaled = (fx32)(((fx64)obj->source->value->value * 0x99a + 0x800) >> 12);
    func_02080d34((DirectionTracker *)((char *)obj + 8), obj->index);
    func_0207f9cc(obj, zero);
    obj->active = 1;
}
