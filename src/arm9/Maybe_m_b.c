/* PURPOSE: Loads the picture of the currently selected cup on the cup-select
 * screen.
 * No arguments. Looks up the currently highlighted cup index in the menu
 * work object (gCupSelectWork, field +0xc), then builds the file path
 * "/data/CupPicture/select_cup_<nitro|retro><NN>_m_b.NCGR" from two parallel
 * word tables (data_0216aea8 = nitro/retro flag, data_0216aeac = the two-digit
 * cup number). The file is read whole into the object's file buffer (+0x238,
 * max 0xe00 bytes) and its character graphics are unpacked into the object's
 * graphics area (+0x4). "m_b" is probably "main/bottom" screen variant. */

/* menu work object pointed to by gCupSelectWork */
typedef struct CupPictureWork {
    int unk_00;             /* 0x000 */
    char char_gfx[8];       /* 0x004: destination for Gfx_ReadCharGraphicsV2 */
    int cup_index;          /* 0x00c: currently selected cup */
    char unk_10[0x228];     /* 0x010 */
    char file_buf[0xe00];   /* 0x238: raw NCGR file is loaded here */
} CupPictureWork;

/* column view of an 8-byte-stride table: one pool symbol per field,
 * shared idx<<3 between the two loads (matches ROM's single lsls) */
typedef struct CupTabCol {
    int volatile v;   /* volatile pins the flag-before-number load order */
    int pad;
} CupTabCol;

extern CupPictureWork *gCupSelectWork;
extern CupTabCol data_0216aea8[];   /* 0 = nitro cup, nonzero = retro cup */
extern CupTabCol data_0216aeac[];   /* cup number used for the %02d */
extern char data_0216ae78[];        /* "nitro" */
extern char data_0216ae80[];        /* "retro" */
extern char data_0216b018[];        /* "_m_b.NCGR" */
extern char data_0216b00c[];        /* "%s%s%02d%s" */
extern char data_0216ae88[];        /* "/data/CupPicture/select_cup_" */

extern int _snprintf(char *buf, unsigned int len, const char *fmt, ...);
extern int OpenReadEntireFileBuffer_from_thumb(char *path, void *dst, unsigned int size);
extern void Gfx_ReadCharGraphicsV2(void *dst, void *ncgr);

void Maybe_m_b(void) {
    char path[0x100];
    int idx;
    int num;
    char *era;

    idx = gCupSelectWork->cup_index;
    era = (char *)data_0216aea8[idx].v;  /* borrow era as the flag temp */
    num = data_0216aeac[idx].v;
    era = ((int)era == 0) ? data_0216ae78 : data_0216ae80;  /* nitro : retro */
    _snprintf(path, 0x100, data_0216b00c, data_0216ae88, era, num, data_0216b018);
    OpenReadEntireFileBuffer_from_thumb(path, gCupSelectWork->file_buf, 0xe00);
    Gfx_ReadCharGraphicsV2(gCupSelectWork->char_gfx, gCupSelectWork->file_buf);
}
