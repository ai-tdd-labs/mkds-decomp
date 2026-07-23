// PURPOSE: Searches forward through connected checkpoint paths for a matching course point.
// The first three arguments describe the driver and position being tested.
// The checkpoint-path and point indices select where the recursive search starts.
// The final argument limits how deeply linked paths are followed.

typedef signed char s8;
typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct DriverStatus DriverStatus;
typedef struct VecFx32 VecFx32;

typedef struct NkmCPOI {
    u8 padding_00[0x1c];
    s16 sectionData1;
    s16 sectionData2;
    u8 padding_20[4];
} NkmCPOI;

typedef struct NkmCPAT {
    u16 pointStart;
    u16 pointCount;
    s8 nextGroups[3];
    s8 previousGroups[3];
    u8 sectionOrderA;
    u8 sectionOrderB;
} NkmCPAT;

typedef struct CoursePathState {
    u8 padding_000[0x44];
    NkmCPOI *cpoiEntries;
    u16 cpoiCount;
    u16 padding_04a;
    NkmCPAT *cpatEntries;
} CoursePathState;

extern CoursePathState *data_02175620;
extern int DriverStatus_SomeFn_0(DriverStatus *driverStatus,
                                 int *value,
                                 VecFx32 *position,
                                 int cpatIndex,
                                 int cpoiIndex);

int StructRC_SomeFn(DriverStatus *driverStatus,
                    int *value,
                    VecFx32 *position,
                    int cpatIndex,
                    int cpoiIndex,
                    int remainingDepth)
{
    s16 sectionData =
        data_02175620->cpoiEntries[cpoiIndex].sectionData1;
    int result;
    int linkIndex;
    NkmCPAT *cpat;

    if (DriverStatus_SomeFn_0(driverStatus, value, position, cpatIndex,
                              cpoiIndex) != 0) {
        return (s16)cpoiIndex;
    }

    if (remainingDepth == 0) {
        return -1;
    }

    result = -1;
    if (sectionData != -1) {
        cpat = &data_02175620->cpatEntries[cpatIndex];

        for (linkIndex = 0; linkIndex < 3; linkIndex++) {
            s8 nextCpat = cpat->nextGroups[linkIndex];

            if (nextCpat != -1) {
                result = StructRC_SomeFn(
                    driverStatus, value, position, (u16)nextCpat,
                    data_02175620->cpatEntries[(u16)nextCpat].pointStart,
                    remainingDepth - 1);
                if (result != -1) {
                    return result;
                }
            }
        }
        return result;
    }

    return StructRC_SomeFn(driverStatus, value, position, cpatIndex,
                           (u16)(cpoiIndex + 1), remainingDepth - 1);
}
