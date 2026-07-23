/* PURPOSE: Initializes the global mission driver state.
 *
 * This clears the global CA structure, resets eight driver records, and marks
 * the current mission level and stage as active. It probably loads mission.mr
 * only when the current state allows it, then stores a pointer eight bytes in.
 */

#pragma optimize_for_size on

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct DriverInfo {
    u32 character_id;
    u32 kart_id;
    u32 type;
    u32 team;
    u32 c5;
    u32 c6;
} DriverInfo;

typedef struct GlobalCA {
    DriverInfo driver_infos[8];
    u8 pad_c0[0x34];
    void *mission_mr_buf;
    u32 mission_mr_buf_p8;
    u8 cur_mission_level;
    u8 cur_mission_stage;
} GlobalCA;

extern GlobalCA *data_02174e1c;
extern char data_0216212c[]; /* "mission.mr" */

extern int CpuFastMemoryZero(void *destination, int size);
extern int GetPMaybeState(void);
extern int func_020299e4(void);
extern void *find_buf_fn_from_thumb(char *name);

void DoInitializeGlobalCA_from_thumb(void)
{
    int i;

    CpuFastMemoryZero(data_02174e1c, 0x110);

    for (i = 0; i < 8; i++) {
        data_02174e1c->driver_infos[i].character_id = -1;
        data_02174e1c->driver_infos[i].kart_id = -1;
        data_02174e1c->driver_infos[i].type = 4;
        data_02174e1c->driver_infos[i].team = -1;
        data_02174e1c->driver_infos[i].c5 = 3;
    }

    data_02174e1c->cur_mission_level = 1;
    data_02174e1c->cur_mission_stage = 1;

    if (GetPMaybeState() == 0) {
        if (func_020299e4() == 0) {
            data_02174e1c->mission_mr_buf =
                find_buf_fn_from_thumb(data_0216212c);
        } else {
            data_02174e1c->mission_mr_buf = 0;
        }
    }

    if (data_02174e1c->mission_mr_buf != 0) {
        data_02174e1c->mission_mr_buf_p8 =
            (u32)((u8 *)data_02174e1c->mission_mr_buf + 8);
    } else {
        data_02174e1c->mission_mr_buf_p8 = 0;
    }
}
