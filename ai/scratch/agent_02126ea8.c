// PURPOSE: Reloads the button graphics for the text system.
//
// The global context probably holds the number of button graphic sets at
// offset 0x28.  For each of its first two sets, this reserves the two related
// texture entries from the shared graphics data at offset 0x44.

typedef struct TextSystemContext {
    char _00[0x28];
    int button_graphics_count;
} TextSystemContext;

extern TextSystemContext *data_0217d3f0;
extern void AllocateReserveTEQSub(int, int, void *, int);

void TextSystemContext_ReloadButtonGraphics2_from_thumb(void)
{
    int i;

    if (data_0217d3f0->button_graphics_count > 0) {
        for (i = 0; i < 2; i++) {
            AllocateReserveTEQSub(0x1F, (i + 0xED) << 1,
                (char *)data_0217d3f0 + 0x2244, 2);
            AllocateReserveTEQSub(0x1F, (i + 0xFD) << 1,
                (char *)data_0217d3f0 + 0x2244, 2);
        }
    }
}
