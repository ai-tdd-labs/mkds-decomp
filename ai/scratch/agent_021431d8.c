// PURPOSE: Returns the current wireless message result when it is ready.

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct WmGlobal {
    void *unknown_00;
    void *buffer;
} WmGlobal;

typedef struct WmMessage {
    u16 type;
    unsigned char unknown_02[0xb6];
    u16 result;
    unsigned char unknown_ba[0xc4];
    u16 ready;
} WmMessage;

extern void DC_InvalidateRangeNoClean(void *start, u32 length);
extern int Wm_CheckInitialized(void);
extern WmGlobal *Wm_GetGlobal(void);

int func_021431d8(void)
{
    WmGlobal *global;

    global = Wm_GetGlobal();
    if (Wm_CheckInitialized() != 0) {
        return 0;
    }

    DC_InvalidateRangeNoClean(global->buffer, 2);
    if (((WmMessage *)global->buffer)->type == 9) {
        DC_InvalidateRangeNoClean(&((WmMessage *)global->buffer)->ready, 2);
        if (((WmMessage *)global->buffer)->ready == 0) {
            return 0;
        }
    } else if (((WmMessage *)global->buffer)->type != 10 &&
               ((WmMessage *)global->buffer)->type != 11) {
        return 0;
    }

    DC_InvalidateRangeNoClean(&((WmMessage *)global->buffer)->result, 2);
    return ((WmMessage *)global->buffer)->result;
}
