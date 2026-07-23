/*
PURPOSE: Loads the picture file for the cup you have highlighted on the cup-select screen.

Detail: Builds a filename like "/data/CupPicture/select_cup_nitro03_m_picture.NSCR"
(uses "retro" instead of "nitro" when the per-cup flag table entry is nonzero,
and a two-digit picture number from a parallel table), reads that whole file
into a buffer inside the cup-select state object (offset 0x1038, max 0x824
bytes), then hands it to a screen-block reader together with a destination
area at offset +8 of the same object. Probably uploads the cup preview image
(NSCR screen data) to VRAM. Takes no arguments, returns nothing.
*/

/* cup-select state object; only the fields this function touches are known */
typedef struct {
    unsigned char unk0[8];
    unsigned char screenDest[4];   /* 0x8: passed as destination/screen struct to MaybeReadScreenBlock_0 */
    int cupIndex;                  /* 0xC: currently selected cup */
    unsigned char unk10[0x1028];
    unsigned char fileBuf[0x824];  /* 0x1038: raw NSCR file is read here */
} UnkCupSelect;

extern UnkCupSelect *gCupSelectWork;

/* two parallel per-cup tables with stride 8; column-struct form keeps one shared idx*8 */
typedef struct { int v; int pad; } Col8;
extern Col8 data_0216aea8[];   /* nonzero = retro cup (probably) */
extern Col8 data_0216aeac[];   /* picture number for the filename */

extern char data_0216ae78[];   /* "nitro" */
extern char data_0216ae80[];   /* "retro" */
extern char data_0216affc[];   /* "_m_picture.NSCR" */
extern char data_0216aff0[];   /* "%s%s%02d%s" */
extern char data_0216ae88[];   /* "/data/CupPicture/select_cup_" */

extern int _snprintf(char *buf, unsigned int n, const char *fmt, ...);
extern void OpenReadEntireFileBuffer_from_thumb(char *path, unsigned char *dst, unsigned int maxSize);
extern void MaybeReadScreenBlock_0(unsigned char *dst, unsigned char *src);

void Maybe_m_picture(void) {
    char path[0x100];
    int i = gCupSelectWork->cupIndex;
    /* volatile casts pin both loads at their statements in source order (flag then num);
       otherwise mwcc forward-propagates the single-use flag load into the ternary */
    int flag = ((volatile Col8 *)data_0216aea8)[i].v;
    int num = ((volatile Col8 *)data_0216aeac)[i].v;

    _snprintf(path, 0x100, data_0216aff0, data_0216ae88,
              (flag == 0) ? data_0216ae78 : data_0216ae80,  /* nitro on the ==0 fallthrough */
              num, data_0216affc);
    OpenReadEntireFileBuffer_from_thumb(path, gCupSelectWork->fileBuf, 0x824);
    /* single statement so the global's deref is CSEd into one load (obj in r2) */
    MaybeReadScreenBlock_0(gCupSelectWork->screenDest, gCupSelectWork->fileBuf);
}
