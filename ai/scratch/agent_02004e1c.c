// PURPOSE: Mounts the game ROM as the default file-system archive.
// The argument selects the DMA channel used for ROM reads.
// It initializes the ROM archive and records both overlay-table regions.
// Multiboot systems install disabled handlers because they cannot read the card.

typedef unsigned int u32;
typedef unsigned short u16;

typedef struct CardRomRegion {
    u32 offset;
    u32 length;
} CardRomRegion;

typedef struct FSArchive {
    unsigned char fields[0x5c];
} FSArchive;

extern u32 data_0216f358;
extern int data_0216f354;
extern CardRomRegion data_0216f35c;
extern CardRomRegion data_0216f364;
extern FSArchive data_0216f36c;
extern char data_02161764[];

extern int Os_AllocateLockId(void);
extern void Card_Initialize(void);
extern void Fs_Archive_Initialize(FSArchive *archive);
extern int Fs_RegisterArchive(FSArchive *archive, char *name, u32 nameLength);
extern void Fs_Archive_SetExtraFileOperationHandler(FSArchive *archive,
                                                    void *readFn,
                                                    void *writeFn);
extern int Fs_Archive_LoadFromFatFnt(FSArchive *archive, u32 base, u32 fat,
                                    u32 fatSize, u32 fnt, u32 fntSize,
                                    void *readFn, void *writeFn);

extern int Fs_RomArchive_ExtraFileOperationHandler_AllDisable(void *archive,
                                                              int operation);
extern int Fs_RomArchive_ReadFn_RomDisable(void *archive, void *destination,
                                           u32 source, u32 length);
extern int Fs_RomArchive_WriteFn_RomDisable(void *archive,
                                            const void *source,
                                            u32 destination, u32 length);
extern int Fs_RomArchive_ExtraFileOperationHandler_Default(void *archive,
                                                           int operation);
extern int Fs_RomArchive_ReadFn_Default(void *archive, void *destination,
                                        u32 source, u32 length);

void Fs_InitializeMountRom(u32 defaultDma)
{
    data_0216f358 = defaultDma;
    data_0216f354 = Os_AllocateLockId();
    data_0216f35c.offset = 0;
    data_0216f35c.length = 0;
    data_0216f364.offset = 0;
    data_0216f364.length = 0;

    Card_Initialize();

    Fs_Archive_Initialize(&data_0216f36c);
    Fs_RegisterArchive(&data_0216f36c, data_02161764, 3);

    if (*(volatile u16 *)0x027ffc40 == 2) {
        data_0216f35c.offset = ~0u;
        data_0216f35c.length = 0;
        data_0216f364.offset = ~0u;
        data_0216f364.length = 0;

        Fs_Archive_SetExtraFileOperationHandler(
            &data_0216f36c,
            (void *)Fs_RomArchive_ExtraFileOperationHandler_AllDisable,
            (void *)~0u);
        Fs_Archive_LoadFromFatFnt(
            &data_0216f36c, 0, 0, 0, 0, 0,
            (void *)Fs_RomArchive_ReadFn_RomDisable,
            (void *)Fs_RomArchive_WriteFn_RomDisable);
    } else {
        const CardRomRegion *const fnt =
            (const CardRomRegion *)0x027ffe40;
        const CardRomRegion *const fat =
            (const CardRomRegion *)0x027ffe48;

        Fs_Archive_SetExtraFileOperationHandler(
            &data_0216f36c,
            (void *)Fs_RomArchive_ExtraFileOperationHandler_Default,
            (void *)0x602);

        if ((fnt->offset == ~0u) || (fnt->offset == 0) ||
            (fat->offset == ~0u) || (fat->offset == 0)) {
            /* The copied ROM header does not contain file-system tables. */
        } else {
            Fs_Archive_LoadFromFatFnt(
                &data_0216f36c, 0, fat->offset, fat->length,
                fnt->offset, fnt->length,
                (void *)Fs_RomArchive_ReadFn_Default,
                (void *)Fs_RomArchive_WriteFn_RomDisable);
        }
    }
}
