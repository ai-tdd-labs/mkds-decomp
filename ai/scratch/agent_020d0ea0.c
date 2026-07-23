// PURPOSE: Returns the cup picture value when the cup work is ready.
// Arguments: none. The readiness check gates access to a nested cup-picture object.
// Returns zero while the work is unavailable.

typedef struct CupPictureValue {
    unsigned char padding_00[0xc];
    int value;
} CupPictureValue;

typedef struct CupPictureWork {
    CupPictureValue *picture;
} CupPictureWork;

extern CupPictureWork *gCupSelectWork;
extern int func_020d0ec4(void);

#pragma optimize_for_size on
int func_020d0ea0(void)
{
    if (func_020d0ec4() != 0) {
        return gCupSelectWork->picture->value;
    }
    return 0;
}
