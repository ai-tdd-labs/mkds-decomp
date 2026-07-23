typedef unsigned char u8;
typedef unsigned int u32;
typedef volatile u8 vu8;
typedef volatile u32 vu32;

#define reg_CARD_CNT        (*(vu32 *)0x040001a4)
#define reg_CARD_MASTERCNT  (*(vu8 *)0x040001a1)
#define reg_CARD_CMD0       (*(vu8 *)0x040001a8)
#define reg_CARD_CMD1       (*(vu8 *)0x040001a9)
#define reg_CARD_CMD2       (*(vu8 *)0x040001aa)
#define reg_CARD_CMD3       (*(vu8 *)0x040001ab)
#define reg_CARD_CMD4       (*(vu8 *)0x040001ac)
#define reg_CARD_CMD5       (*(vu8 *)0x040001ad)
#define reg_CARD_CMD6       (*(vu8 *)0x040001ae)
#define reg_CARD_CMD7       (*(vu8 *)0x040001af)

#define CARD_START          0x80000000
#define CARDMST_IF_ENABLE   0x40
#define CARDMST_SEL_ROM     0x00
#define CARDMST_ENABLE      0x80

void Card_WriteRomOperation(u32 cmd1, u32 cmd2)
{
    while ((reg_CARD_CNT & CARD_START) != 0) {}

    reg_CARD_MASTERCNT = CARDMST_SEL_ROM | CARDMST_ENABLE | CARDMST_IF_ENABLE;
    reg_CARD_CMD0 = (u8)(cmd1 >> (8 * 3));
    reg_CARD_CMD1 = (u8)(cmd1 >> (8 * 2));
    reg_CARD_CMD2 = (u8)(cmd1 >> (8 * 1));
    reg_CARD_CMD3 = (u8)(cmd1 >> (8 * 0));
    reg_CARD_CMD4 = (u8)(cmd2 >> (8 * 3));
    reg_CARD_CMD5 = (u8)(cmd2 >> (8 * 2));
    reg_CARD_CMD6 = (u8)(cmd2 >> (8 * 1));
    reg_CARD_CMD7 = (u8)(cmd2 >> (8 * 0));
}
