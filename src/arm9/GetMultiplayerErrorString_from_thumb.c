/* PURPOSE: Returns the message for the current multiplayer connection error.
 * Arguments: none.  It chooses a string from the common message archive.
 * In download-play mode, the archive is probably supplied by the active 2D
 * screen object instead of being loaded from the normal filesystem.
 */

typedef unsigned short u16;

typedef struct {
    int errorCode; /* +0x00 */
} MultiplayerErrorState;

typedef struct {
    unsigned char padding[0x20];
    void *messageArchive; /* +0x20 */
} Global2DObject;

extern char data_0216ea6c[];
extern MultiplayerErrorState *data_0217d408;

extern void *FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(char *name);
extern void *Bmg_GetRawStringPointer_from_thumb(void *bmg, int index);
extern Global2DObject *GetGlobal2DObject(void);

void *GetMultiplayerErrorString_from_thumb(void)
{
    void *messageArchive = 0;
    int errorCode;

    if (*(volatile u16 *)0x027ffc40 != 2) {
        messageArchive = FindFileBuffer_G2L_GE2_CKL_CKS_S2D_M2L_MA2_from_thumb(data_0216ea6c);
    }

    errorCode = data_0217d408->errorCode;
    if (errorCode == 4) {
        return Bmg_GetRawStringPointer_from_thumb(messageArchive, 0x86);
    }
    if (errorCode == 5) {
        return Bmg_GetRawStringPointer_from_thumb(messageArchive, 0x87);
    }
    if (errorCode == 6) {
        return Bmg_GetRawStringPointer_from_thumb(messageArchive, 0x88);
    }
    if (errorCode == 1) {
        return Bmg_GetRawStringPointer_from_thumb(messageArchive, 0x83);
    }
    if (errorCode == 2) {
        return Bmg_GetRawStringPointer_from_thumb(messageArchive, 0x84);
    }
    if (errorCode == 3) {
        return Bmg_GetRawStringPointer_from_thumb(messageArchive, 0x85);
    }
    if (errorCode == 0) {
        if (*(volatile u16 *)0x027ffc40 == 2) {
            return Bmg_GetRawStringPointer_from_thumb(GetGlobal2DObject()->messageArchive, 0);
        }
        return Bmg_GetRawStringPointer_from_thumb(messageArchive, 0x82);
    }
    return 0;
}
