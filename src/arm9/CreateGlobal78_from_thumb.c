/* PURPOSE: Creates the workspace used by the on-screen keyboard.
 * The arguments give the workspace width, height, and UTF-16 text capacity.
 * It allocates the drawing buffers, loads keyboard graphics and layout maps,
 * and installs the callbacks and constants used by the keyboard renderer.
 */

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Global78 {
    void *characterBuffer;
    void *drawingBuffer;
    u32 characterBufferSize;
    u32 drawingBufferSize;
    void *graphics10Key;
    void *graphicsJapanese;
    void *graphicsAscii;
    void *graphicsEuropean;
    void *graphicsPictograph;
    void *graphicsPictographAlt;
    void *layout10Key;
    void *layoutJapanese;
    void *layoutAscii;
    void *layoutEuropean;
    void *layoutPictograph;
    void *layoutPictographAlt;
    u16 *text;
    u16 textCapacity;
    u16 cursorStart;
    u16 cursorEnd;
    u16 textLengthLimit;
    u32 unused4C;
    u32 keyValue0;
    u32 keyValue1;
    u32 keyValue2;
    u32 keyValue3;
    u32 keyValue4;
    u32 keyValue5;
    u32 keyValue6;
    u32 keyValue7;
    u32 keyValue8;
    u32 keyValue9;
} Global78;

extern Global78 *data_0217b334;

extern void *data_0217b300;
extern void *data_0217b304;
extern void *data_0217b308;
extern void *data_0217b30c;
extern void *data_0217b310;
extern void *data_0217b314;
extern void *data_0217b318;
extern void *data_0217b31c;
extern void *data_0217b320;
extern void *data_0217b324;
extern void *data_0217b328;
extern void *data_0217b32c;
extern void *data_0217b330;
extern void *data_0217b338;

extern char data_02167bf4[];
extern char data_02167c0c[];
extern char data_02167c24[];
extern char data_02167c3c[];
extern char data_02167c54[];
extern char data_02167c6c[];
extern char data_02167c84[];
extern char data_02167c90[];
extern char data_02167c9c[];
extern char data_02167ca4[];
extern char data_02167cb0[];
extern char data_02167cbc[];
extern char data_02167cc8[];
extern char data_02167cd8[];
extern char data_02167cec[];
extern char data_02167d00[];
extern char data_02167d10[];
extern char data_02167d28[];
extern char data_02167d40[];
extern char data_02167d58[];
extern char data_02167d68[];
extern char data_02167d80[];
extern char data_02167d98[];
extern char data_02167db0[];
extern char data_02167dc0[];
extern char data_02167dd0[];

extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void *Mem_AllocateHeapAligned(void *heap, int size, int alignment);
extern void *GetLoadedFont_from_thumb(int fontType);
extern void *find_buf_fn_from_thumb(char *name);
extern void Gfx_ReadCharGraphics(void **output, void *fileBuffer);
extern void Gfx_ReadCharGraphicsRelative(void **output, void *fileBuffer);

extern void func_020abff4(void);
extern void func_020ac0b4(void);
extern int func_020ab064(void (*callback)(void));
extern int func_020ab058(void (*callback)(void));
extern int func_020ab07c(int value);
extern int func_020ab070(int value);
extern void func_020ab088(void *font, void *characterBuffer,
                          void *drawingBuffer, int width, int height,
                          int initialValue);
extern void func_020ab1a8(short first, short second, short size);

void CreateGlobal78_from_thumb(int width, int height, int textCapacity)
{
    data_0217b334 = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x78);

    data_0217b334->textCapacity = (u16)textCapacity;
    data_0217b334->textLengthLimit = (u16)textCapacity;
    data_0217b334->cursorStart = 0;
    data_0217b334->cursorEnd = 0;

    data_0217b334->text = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
        (textCapacity + 1) * 2);

    data_0217b334->drawingBufferSize = width * 2 * height;
    data_0217b334->drawingBuffer = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
        data_0217b334->drawingBufferSize);

    data_0217b334->characterBufferSize = 0x4020;
    data_0217b334->characterBuffer = Mem_AllocateHeapAligned(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()),
        data_0217b334->characterBufferSize, 0x20);

    func_020ab088(GetLoadedFont_from_thumb(0),
                  data_0217b334->characterBuffer,
                  data_0217b334->drawingBuffer,
                  width, height, 0);

    func_020ab064(func_020abff4);
    func_020ab058(func_020ac0b4);
    func_020ab07c(0);
    func_020ab070(1);

    data_0217b334->keyValue0 = 0;
    data_0217b334->keyValue1 = 0;
    data_0217b334->keyValue2 = 0x23;
    data_0217b334->keyValue3 = 0x7a;
    data_0217b334->keyValue4 = 0x7d;
    data_0217b334->keyValue5 = 0x8e;
    data_0217b334->keyValue6 = 0x83;
    data_0217b334->keyValue7 = 0x7a;
    data_0217b334->keyValue8 = 0xdd;
    data_0217b334->keyValue9 = 0x8e;

    Gfx_ReadCharGraphics(&data_0217b334->graphics10Key,
                         find_buf_fn_from_thumb(data_02167bf4));
    Gfx_ReadCharGraphics(&data_0217b334->graphicsAscii,
                         find_buf_fn_from_thumb(data_02167c0c));
    Gfx_ReadCharGraphics(&data_0217b334->graphicsJapanese,
                         find_buf_fn_from_thumb(data_02167c24));
    Gfx_ReadCharGraphics(&data_0217b334->graphicsEuropean,
                         find_buf_fn_from_thumb(data_02167c3c));
    Gfx_ReadCharGraphics(&data_0217b334->graphicsPictograph,
                         find_buf_fn_from_thumb(data_02167c54));
    Gfx_ReadCharGraphicsRelative(&data_0217b334->graphicsPictographAlt,
                                 find_buf_fn_from_thumb(data_02167c6c));

    data_0217b334->layout10Key = find_buf_fn_from_thumb(data_02167c84);
    data_0217b334->layoutAscii = find_buf_fn_from_thumb(data_02167c90);
    data_0217b334->layoutJapanese = find_buf_fn_from_thumb(data_02167c9c);
    data_0217b334->layoutEuropean = find_buf_fn_from_thumb(data_02167ca4);
    data_0217b334->layoutPictograph = find_buf_fn_from_thumb(data_02167cb0);
    data_0217b334->layoutPictographAlt = find_buf_fn_from_thumb(data_02167cbc);

    data_0217b318 = find_buf_fn_from_thumb(data_02167cc8);
    data_0217b31c = find_buf_fn_from_thumb(data_02167cd8);
    data_0217b304 = find_buf_fn_from_thumb(data_02167cec);
    data_0217b338 = find_buf_fn_from_thumb(data_02167d00);
    data_0217b30c = find_buf_fn_from_thumb(data_02167d10);
    data_0217b310 = find_buf_fn_from_thumb(data_02167d28);
    data_0217b314 = find_buf_fn_from_thumb(data_02167d40);
    data_0217b300 = find_buf_fn_from_thumb(data_02167d58);
    data_0217b308 = find_buf_fn_from_thumb(data_02167d68);
    data_0217b320 = find_buf_fn_from_thumb(data_02167d80);
    data_0217b324 = find_buf_fn_from_thumb(data_02167d98);
    data_0217b328 = find_buf_fn_from_thumb(data_02167db0);
    data_0217b32c = find_buf_fn_from_thumb(data_02167dc0);
    data_0217b330 = find_buf_fn_from_thumb(data_02167dd0);

    func_020ab1a8(1, 2, 0x400);
}
