// PURPOSE: Calculates the size of the ROM binary data area.
// It reads a small header from the supplied file when one is available.
// The header is probably used to locate ROM data; a shared fallback is used otherwise.

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct RomFile {
    u8 unknown_00[0x24];
    u32 start;
    u8 unknown_28[4];
    u32 end;
    u8 unknown_30[0xc];
    u32 binary_size;
} RomFile;

extern int Fs_File_Read(RomFile *file, void *destination, u32 size);
extern void Fs_File_Seek(RomFile *file, u32 offset, u32 origin);

u32 ComputeRomBinarySize_from_thumb(RomFile *file)
{
    u8 header[0x60];
    void *rom_header = 0;
    u32 size = 0;
    u32 offset;

    if (file != 0) {
        offset = file->end - file->start;
        if (Fs_File_Read(file, header, 0x60) >= 0x60) {
            rom_header = header;
        }
        Fs_File_Seek(file, offset, 0);
    } else {
        rom_header = (void *)0x027ffe00;
    }

    if (rom_header != 0) {
        RomFile *header_file = (RomFile *)rom_header;
        size = header_file->end + 0x268 + header_file->binary_size;
        if (size < 0x10000) {
            size = 0x10000;
        }
    }

    return size;
}
