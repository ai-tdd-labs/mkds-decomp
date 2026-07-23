/* PURPOSE: Applies the player's custom emblem textures to the kart-select model.
 *
 * StructCESub_SomeFn_from_thumb(sub): if the global StructCE's +0x1e0 field is
 * set and this sub-object's +0xb4 emblem data pointer is set, it patches the
 * "emblem" and "emblem_pl" texture/palette slots of the nsbtx resource held at
 * sub->f14->f4 with that emblem data. Probably called when entering kart select.
 */

typedef unsigned char u8;

typedef struct StructCE {
    u8 pad_00[0x1e0];
    void *f1e0; /* 0x1e0: guard field, probably a loaded-resource pointer */
} StructCE;

typedef struct ResourceHolder {
    u8 pad_00[4];
    void *f4; /* 0x4: nsbtx file */
} ResourceHolder;

typedef struct StructCESub {
    u8 pad_00[0x14];
    ResourceHolder *f14; /* 0x14: resource holder */
    u8 pad_18[0xb4 - 0x18];
    void *fb4; /* 0xb4: emblem image data */
} StructCESub;

extern StructCE *data_0217ad08;
extern char data_02155048[];  /* "emblem" */
extern char data_021550a8[];  /* "emblem_pl" */

extern void func_02010458(void *nsbtx, char *name);
extern void func_020101e8(void *nsbtx, char *name);
extern void func_0201050c(void *nsbtx, void *data, char *name);
extern void func_02010294(void *nsbtx, void *data, char *name);

void StructCESub_SomeFn_from_thumb(StructCESub *sub)
{
    if (data_0217ad08->f1e0 != 0) {
        if (sub->fb4 != 0) {
            func_02010458(sub->f14->f4, data_02155048);
            func_020101e8(sub->f14->f4, data_021550a8);
            func_0201050c(sub->f14->f4, sub->fb4, data_02155048);
            func_02010294(sub->f14->f4, sub->fb4, data_021550a8);
        }
    }
}
