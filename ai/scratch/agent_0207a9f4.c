// PURPOSE: Marks the current racer and updates each listed driver.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct RaceConfig {
    u8 pad0[0x62];
    signed char racerIndex;
} RaceConfig;

typedef struct DriverState {
    u8 pad0[0x60];
    unsigned int active;
} DriverState;

typedef struct MQRacerEntry {
    u8 pad0[0x590];
    DriverState *state;
    u8 pad1[0x14];
} MQRacerEntry;

extern RaceConfig *gRaceConfig;
extern u16 data_0217ad14;
extern MQRacerEntry *data_0217ad18;
extern u16 *GetSomeAED0DriverIdList(void);
extern void StructMQRacerEntry_SomeFn_50(MQRacerEntry *entry);

void func_0207a9f4(void)
{
    int i;
    u16 *driverIds;

    i = 0;
    driverIds = GetSomeAED0DriverIdList();
    data_0217ad18[gRaceConfig->racerIndex].state->active = 1;

    while (i < data_0217ad14) {
        StructMQRacerEntry_SomeFn_50(&data_0217ad18[*driverIds]);
        driverIds++;
        i++;
    }
}
