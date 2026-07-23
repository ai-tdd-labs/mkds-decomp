// PURPOSE: Sets or clears a scene-dependent object flag.
// The argument selects whether the flag may be enabled in scene 2.
// The global object and the exact meaning of its flag field are probably unknown.

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 pad_00[4];
    u16 xflag2;
} Struct5624;

extern int GetCurrentSceneId(void);
extern Struct5624 *data_02175624;

void Struct5624_SetXflag2(void *enabled)
{
    if (GetCurrentSceneId() == 2 && enabled != 0) {
        data_02175624->xflag2 = data_02175624->xflag2 | 2;
    } else {
        data_02175624->xflag2 = data_02175624->xflag2 & ~2;
    }
}
