/* PURPOSE: Uploads prepared background graphics to the bottom screen.
 * The global work area holds a tile map and character data with their sizes.
 * This flushes both buffers from the CPU cache before copying them to VRAM.
 */

typedef unsigned int u32;

typedef struct {
    void *character_data;
    void *tile_map;
    u32 character_data_size;
    u32 tile_map_size;
} BackgroundGraphicsBuffers;

extern BackgroundGraphicsBuffers *data_0217b334;

extern void Arm_FlushRange(void *data, u32 size);
extern void TEQSub_Fn26Impl_Fn28Impl(void *src, u32 offset, u32 size);
extern void CopyBgData_Bg2_Bottom(void *src, u32 offset, u32 size);

void func_020aba9c(void)
{
    Arm_FlushRange(data_0217b334->tile_map, data_0217b334->tile_map_size);
    TEQSub_Fn26Impl_Fn28Impl(data_0217b334->tile_map, 0, data_0217b334->tile_map_size);

    Arm_FlushRange(data_0217b334->character_data, data_0217b334->character_data_size);
    CopyBgData_Bg2_Bottom(data_0217b334->character_data, 0, data_0217b334->character_data_size);
}
