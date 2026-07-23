/* PURPOSE: Shows a progress message while an operation is running.
 * The message pointer supplies the text displayed in the dialog.
 * The five remaining arguments configure persistent dialog fields whose
 * exact meanings are uncertain.
 */

typedef struct TextSystemCommand TextSystemCommand;

typedef void (*TextSystemCommandFn)(TextSystemCommand *command, int commandId);

struct TextSystemCommand {
    unsigned char padding_00[0x18];
    TextSystemCommandFn execute;
};

typedef struct TextSystemContext {
    unsigned char padding_0000[0x20];
    int state20;
    int completionOption;
    int state28;
    int padding_2c;
    int state30;
    unsigned char padding_0034[8];
    int dialogOption3;
    int dialogOption4;
    unsigned char padding_0044[0x2030];
    int dialogOption1;
    int dialogOption2;
    unsigned char padding_207c[0x5c];
    TextSystemCommand command;
    unsigned char padding_20f4[0xa4];
    unsigned char progressText[0x74];
    int dialogActive;
} TextSystemContext;

typedef struct TextLayout {
    unsigned char padding_00[4];
    unsigned char widthTiles;
    unsigned char heightTiles;
} TextLayout;

extern TextSystemContext *data_0217d3f0;
extern TextLayout data_0215d044;

extern void G2d_Text_SomeFn_from_thumb(
    void *text,
    int arg1,
    int arg2,
    int width,
    int height,
    int arg5,
    int bufferSize,
    int arg7,
    void *message);
extern void TextSystemContext_DisableAllSprites_from_thumb(void);
extern void TextSystemContext_StartDialog_from_thumb(void);

void TextSystem_DisplayProgressDialog_from_thumb(
    void *message,
    int dialogOption1,
    int dialogOption2,
    int dialogOption3,
    int dialogOption4,
    int completionOption)
{
    data_0217d3f0->command.execute(&data_0217d3f0->command, 0xf);

    G2d_Text_SomeFn_from_thumb(
        data_0217d3f0->progressText,
        0,
        0,
        data_0215d044.widthTiles << 3,
        data_0215d044.heightTiles << 3,
        1,
        0x480,
        1,
        message);

    TextSystemContext_DisableAllSprites_from_thumb();
    data_0217d3f0->dialogActive = 1;
    TextSystemContext_StartDialog_from_thumb();

    /* Reload the shared context for each store because it may alias its data. */
    data_0217d3f0->state28 = 0;
    data_0217d3f0->state30 = 0;
    data_0217d3f0->state20 = 0;
    data_0217d3f0->completionOption = completionOption;
    data_0217d3f0->dialogOption1 = dialogOption1;
    data_0217d3f0->dialogOption2 = dialogOption2;
    data_0217d3f0->dialogOption3 = dialogOption3;
    data_0217d3f0->dialogOption4 = dialogOption4;
}
