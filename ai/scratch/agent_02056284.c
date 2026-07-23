typedef struct StaffGhostReadWork {
    unsigned char padding_00[0x1c];
    void *buffer;
} StaffGhostReadWork;

extern StaffGhostReadWork *data_0217aa08;
extern int OpenReadEntireFileBuffer_from_thumb(char *path, void *dst,
                                                unsigned int size);

void *GetReadStaffGhost_from_thumb(char *path)
{
    // PURPOSE: Loads a staff ghost file into its read buffer.
    if (OpenReadEntireFileBuffer_from_thumb(path, data_0217aa08->buffer,
                                             0x1000) != 0) {
        return data_0217aa08->buffer;
    }
    return 0;
}
