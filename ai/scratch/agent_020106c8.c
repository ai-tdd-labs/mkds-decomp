// PURPOSE: Binds one texture resource to every material listed by a model texture binding.
// The binding supplies the material indices and is marked active afterward.
// Texture parameters, VRAM base, and dimension-dependent scales are written to each material.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int fx32;

extern void FX_Div(void *a0);

void func_020106c8(void *model, void *binding, void *texture, void *textureData)
{
    u32 i;
    u32 textureBase;
    u8 *materialIndices;

    materialIndices = (u8 *)model + *(u16 *)binding;

    if ((*(u32 *)textureData & 0x1c000000) != 0x14000000) {
        textureBase = *(u32 *)((u8 *)texture + 8) & 0xffff;
    } else {
        textureBase = *(u32 *)((u8 *)texture + 0x18) & 0xffff;
    }

    i = 0;
    if (i < *((u8 *)binding + 2)) {
        u32 height;
        u8 *material;
        u8 *dictionaryBase;
        fx32 one = 0x1000;

        do {
            dictionaryBase = (u8 *)model + 4;

            {
                u16 stride = *(u16 *)(dictionaryBase + *(u16 *)((u8 *)model + 0xa));
                u8 materialIndex = materialIndices[i];
                u32 dimensions;
                u32 width;
                u16 materialWidth;
                u16 materialHeight;

                material = (u8 *)model +
                    *(u32 *)(dictionaryBase + *(u16 *)((u8 *)model + 0xa) +
                             stride * materialIndex + 4);

                *(u32 *)(material + 0x14) |= *(u32 *)textureData + textureBase;

                dimensions = *(u32 *)((u8 *)textureData + 4);
                width = dimensions & 0x7ff;
                height = (dimensions >> 11) & 0x7ff;

                materialWidth = *(u16 *)(material + 0x20);
                *(fx32 *)(material + 0x24) =
                    width == materialWidth
                        ? one
                        : ((fx32 (*)(fx32, fx32))FX_Div)(width << 12,
                                                         (u32)materialWidth << 12);

                materialHeight = *(u16 *)(material + 0x22);
                *(fx32 *)(material + 0x28) =
                    height == materialHeight
                        ? one
                        : ((fx32 (*)(fx32, fx32))FX_Div)(height << 12,
                                                         (u32)materialHeight << 12);
            }

            i++;
        } while (i < *((u8 *)binding + 2));
    }

    *((u8 *)binding + 3) |= 1;
}
