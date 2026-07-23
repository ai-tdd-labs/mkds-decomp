/* PURPOSE: Creates the global HD5 race state for the current driver.
 * The function has no arguments. It selects the driver stored in the race
 * configuration, allocates the probably camera-related state, initializes
 * shared HD data, copies the driver's direction vector, and finalizes HD5.
 */

typedef struct DriverEntry DriverEntry;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct RaceConfig {
    char pad_00[0x62];
    signed char currentDriver;
} RaceConfig;

typedef struct GlobalHD5 {
    char pad_000[0x260];
    VecFx32 driverVector;
} GlobalHD5;

extern RaceConfig *gRaceConfig;
extern GlobalHD5 *data_0217ac94;

extern DriverEntry *GetDriverEntry(int index);
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void func_02076a5c(void);
extern void GetMQRacerVector333(DriverEntry *driver, VecFx32 *out);
extern void StructHD_SomeFn_2(GlobalHD5 *state);

void CreateGlobalHD5_from_thumb(void)
{
    DriverEntry *driver = GetDriverEntry(gRaceConfig->currentDriver);

    data_0217ac94 = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x270);
    func_02076a5c();
    GetMQRacerVector333(driver, &data_0217ac94->driverVector);
    StructHD_SomeFn_2(data_0217ac94);
}
