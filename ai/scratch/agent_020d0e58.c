// PURPOSE: Returns the selected cup graphic data when it is ready.

#pragma optimize_for_size on

typedef struct CupSelectWork {
    unsigned char padding_00[8];
    unsigned char *graphic;
} CupSelectWork;

extern int func_020d0ec4(void);
extern CupSelectWork *gCupSelectWork;

void *func_020d0e58(void)
{
    if (func_020d0ec4() != 0) {
        return gCupSelectWork->graphic + 0xc;
    }
    return 0;
}
