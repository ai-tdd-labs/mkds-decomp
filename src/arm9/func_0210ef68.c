/*
PURPOSE: Resets the dynamic offset for every sound file in a list.
The argument points to up to 16 sound-file handles followed by a signed count.
Each listed file has its dynamic FAT offset set to zero.
*/

typedef struct SoundFileList {
    void *files[16];
    int count;
} SoundFileList;

extern void Sound_SetFileFatDynamicOffsetField(void *file, int offset);

void func_0210ef68(SoundFileList *list)
{
    int index;

    for (index = 0; index < list->count; index++) {
        Sound_SetFileFatDynamicOffsetField(list->files[index], 0);
    }
}
