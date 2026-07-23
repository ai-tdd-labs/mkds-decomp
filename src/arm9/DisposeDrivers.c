/* PURPOSE: Disposes every active driver context.
 *
 * Walks the global driver array using the current driver count and disposes
 * each fixed-size context. The array pointer is cleared after the loop.
 * Takes no arguments and returns no value.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct DriverContext {
    u8 data[0x5a8];
} DriverContext;

extern u16 data_0217ad14;
extern DriverContext *data_0217ad18;
extern void DriverContext_Dispose(DriverContext *driver);

void DisposeDrivers(void)
{
    int driverIndex;

    for (driverIndex = 0; driverIndex < data_0217ad14; driverIndex++) {
        DriverContext_Dispose(&data_0217ad18[driverIndex]);
    }

    data_0217ad18 = 0;
}
