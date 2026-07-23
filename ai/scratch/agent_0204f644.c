// PURPOSE: Loads the next queued resource into its destination buffer.
// The queue holds up to twelve resource descriptions and their destination heaps.
// A shared-source entry is probably decompressed by a worker before loading continues.
// The return value reports whether no queued resource remains to be loaded.

typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct FSFile {
    u8 pad_00[0x0c];
    volatile u32 status;
    u8 pad_10[0x14];
    u32 start;
    u32 end;
    u8 pad_2c[0x1c];
} FSFile;

typedef struct ResourceSlotFlags {
    u32 options : 29;
    signed int usesSharedSource : 1;
    u32 pending : 1;
    u32 unknown : 1;
} ResourceSlotFlags;

typedef struct ResourceSlot {
    u8 pad_00[0x34];
    u8 descriptor[0x40];
    void *source;
    void *buffer;
    void **output;
    void *heap;
    ResourceSlotFlags flags;
} ResourceSlot;

typedef struct UnkStruct_0217aa00 {
    u8 pad_0000[0x16a0];
    ResourceSlot slots[12];
    u8 pad_1d00[8];
    u16 loadIndex;
    u16 pad_1d0a;
    FSFile file;
} UnkStruct_0217aa00;

typedef struct WorkerState {
    u8 pad_00[0xf8];
    u32 taskPending;
} WorkerState;

extern UnkStruct_0217aa00 *data_0217aa00;
extern WorkerState *data_0217aa0c;

extern void Fs_File_Close(FSFile *file);
extern void Fs_File_Initialize(FSFile *file);
extern int Fs_File_Open(FSFile *file, const char *path);
extern u32 Fs_File_ReadAsync(FSFile *file, void *buffer, u32 size);
extern void *Mem_AllocateHeapAligned(void *heap, u32 size, u32 alignment);
extern void WorkerInsertTask(void (*task)(void));
extern void func_0204f770(void);

int func_0204f644(void)
{
    UnkStruct_0217aa00 *state = data_0217aa00;
    u16 index = state->loadIndex;
    int previous = (s16)(index - 1);
    FSFile *file = &state->file;
    int busy = !!(file->status & 1);

    if (busy != 0) {
        return 0;
    }

    if (previous >= 0) {
        if (state->slots[previous].flags.usesSharedSource != 0) {
            if (data_0217aa0c->taskPending != 0) {
                return 0;
            }

            WorkerInsertTask(func_0204f770);
            data_0217aa0c->taskPending = 1;
            return 0;
        }
    }

    if (index >= 12 || state->slots[index].descriptor[0] == 0) {
        return 1;
    }

    {
        int open = !!(file->status & 0x10);

        if (open != 0) {
            Fs_File_Close(file);
        }
    }

    Fs_File_Initialize(file);
    if (Fs_File_Open(file, (const char *)state->slots[index].descriptor) != 0) {
        UnkStruct_0217aa00 *reload =
            *(UnkStruct_0217aa00 * volatile *)&data_0217aa00;
        u32 size = file->end - file->start;
        void *source = reload->slots[index].source;

        if (source == 0) {
            source = Mem_AllocateHeapAligned(
                data_0217aa00->slots[index].heap, size, 0x20);
            *data_0217aa00->slots[index].output = source;
        }

        Fs_File_ReadAsync(file, source, size);
        data_0217aa00->loadIndex++;
    }

    return 0;
}
