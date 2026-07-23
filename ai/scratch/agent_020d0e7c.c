// PURPOSE: Returns the loaded cup graphic data once its worker is ready.
typedef struct CupGraphicData {
    unsigned char pad_00[0x14];
    void *rawData;
} CupGraphicData;

typedef struct CupPictureWork {
    unsigned char pad_00[4];
    CupGraphicData *graphicData;
} CupPictureWork;

extern CupPictureWork *gCupSelectWork;
extern int func_020d0ec4(void);

#pragma optimize_for_size on

void *func_020d0e7c(void)
{
    if (func_020d0ec4() != 0) {
        return gCupSelectWork->graphicData->rawData;
    }
    return 0;
}
