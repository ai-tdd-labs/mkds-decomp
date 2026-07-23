typedef unsigned int u32;
typedef int BOOL;

typedef int (*FS_ARCHIVE_READ_FUNC)(void *p_arc, void *dst, u32 pos, u32 size);
typedef int (*FS_ARCHIVE_WRITE_FUNC)(void *p_arc, const void *src, u32 pos, u32 size);

typedef struct OSThreadQueue
{
    void *head;                        /* +0x0 */
    void *tail;                        /* +0x4 */
} OSThreadQueue;

typedef struct FSFileLink
{
    void *prev;                        /* +0x0 */
    void *next;                        /* +0x4 */
} FSFileLink;

typedef struct FSArchive
{
    union
    {
        char ptr[4];
        u32 pack;
    } name;                            /* 0x00 */
    struct FSArchive *next;            /* 0x04 */
    struct FSArchive *prev;            /* 0x08 */
    OSThreadQueue sync_q;              /* 0x0c */
    OSThreadQueue stat_q;              /* 0x14 */
    u32 flag;                          /* 0x1c */
    FSFileLink list;                   /* 0x20 */
    u32 base;                          /* 0x28 */
    u32 fat;                           /* 0x2c */
    u32 fat_size;                      /* 0x30 */
    u32 fnt;                           /* 0x34 */
    u32 fnt_size;                      /* 0x38 */
    u32 fat_bak;                       /* 0x3c */
    u32 fnt_bak;                       /* 0x40 */
    void *load_mem;                    /* 0x44 */
    FS_ARCHIVE_READ_FUNC read_func;    /* 0x48 */
    FS_ARCHIVE_WRITE_FUNC write_func;  /* 0x4c */
    FS_ARCHIVE_READ_FUNC table_func;   /* 0x50 */
} FSArchive;

extern int Fs_Archive_ReadFn_Default(void *p_arc, void *dst, u32 pos, u32 size);
extern int Fs_Archive_WriteFn_Default(void *p_arc, const void *src, u32 pos, u32 size);

#define FS_ARCHIVE_FLAG_LOADED 0x00000002

BOOL Fs_Archive_LoadFromFatFnt(FSArchive *p_arc, u32 base, u32 fat, u32 fat_size, u32 fnt, u32 fnt_size, FS_ARCHIVE_READ_FUNC read_func, FS_ARCHIVE_WRITE_FUNC write_func)
{
    p_arc->base = base;
    p_arc->fat_size = fat_size;
    p_arc->fat = p_arc->fat_bak = fat;
    p_arc->fnt_size = fnt_size;
    p_arc->fnt = p_arc->fnt_bak = fnt;
    p_arc->read_func = (read_func != 0) ? read_func : Fs_Archive_ReadFn_Default;
    p_arc->write_func = (write_func != 0) ? write_func : Fs_Archive_WriteFn_Default;
    p_arc->table_func = p_arc->read_func;
    p_arc->load_mem = 0;
    p_arc->flag |= FS_ARCHIVE_FLAG_LOADED;
    return 1;
}
