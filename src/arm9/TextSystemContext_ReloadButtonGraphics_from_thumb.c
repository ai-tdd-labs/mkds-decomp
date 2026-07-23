// PURPOSE: Reloads the text system button graphics.
//
// This function reserves the normal button graphic entries when the global
// text context has button sets. It probably reserves a second pair only for
// the two-set text context.

typedef struct TextSystemContext {
    char _00[0x28];
    int button_graphics_count;
    int button_graphics_index;
} TextSystemContext;

extern TextSystemContext *data_0217d3f0;
extern void AllocateReserveTEQSub(int, int, void *, int);

void TextSystemContext_ReloadButtonGraphics_from_thumb(void)
{
    if (data_0217d3f0->button_graphics_count > 0) {
        AllocateReserveTEQSub(0x1F,
            (0xEE - data_0217d3f0->button_graphics_index) << 1,
            (char *)data_0217d3f0 + 0x2246, 2);
        AllocateReserveTEQSub(0x1F,
            (0xFE - data_0217d3f0->button_graphics_index) << 1,
            (char *)data_0217d3f0 + 0x2246, 2);

        if (data_0217d3f0->button_graphics_count == 2) {
            AllocateReserveTEQSub(0x1F,
                (data_0217d3f0->button_graphics_index + 0xED) << 1,
                (char *)data_0217d3f0 + 0x2244, 2);
            AllocateReserveTEQSub(0x1F,
                (data_0217d3f0->button_graphics_index + 0xFD) << 1,
                (char *)data_0217d3f0 + 0x2244, 2);
        }
    }
}
