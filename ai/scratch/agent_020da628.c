// PURPOSE: Initializes the state data for this game object.
// The object receives two default four-word blocks and a state handler is set to mode one.
// Several counters are cleared; the exact purpose of the two copied blocks is probably setup data.

typedef struct StateDualHandler StateDualHandler;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} DataBlock;

typedef struct {
    char pad00[0x10];
    int f10;
    int f14;
    int f18;
    char pad1c[0x64];
    char stateHandler[0x24];
    DataBlock fA4;
    DataBlock fB4;
    char padC4[0x34];
    unsigned short fF8;
} ObjectState;

extern const DataBlock data_02158140;
extern const DataBlock data_02158150;
extern void StateDualHandler_SetState(StateDualHandler *handler, int state);

void func_020da628(ObjectState *object)
{
    object->fF8 = 0x1000;
    object->fA4 = data_02158140;
    object->fB4 = data_02158150;
    StateDualHandler_SetState((StateDualHandler *)object->stateHandler, 1);
    object->f10 = 0;
    object->f14 = 0;
    object->f18 = 0;
}
