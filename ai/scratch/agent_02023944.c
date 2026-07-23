// PURPOSE: Clears every pixel in a sprite to one color.
// The sprite provides its pixel buffer, tile dimensions, and bit depth.
// The color is repeated into a 32-bit fill word for 4bpp or 8bpp pixels.
// The complete buffer is then filled with that word.
typedef unsigned char u8;
typedef unsigned int u32;

typedef struct G2dSprite {
    void *pixels;
    u32 tile_width;
    u32 tile_height;
    u8 bits_per_pixel;
} G2dSprite;

extern void Mem_CpuFastMemorySet(u32 value, void *dst, u32 size);

void G2d_Sprite_Clear(G2dSprite *sprite, u32 color)
{
    volatile u32 fill;
    u8 bits_per_pixel = sprite->bits_per_pixel;

    if (bits_per_pixel == 4) {
        fill = color | (color << 4);
        fill |= fill << 8;
    } else {
        fill = color | (color << 8);
    }
    fill |= fill << 16;

    Mem_CpuFastMemorySet(fill, sprite->pixels,
        sprite->tile_width * sprite->tile_height * ((bits_per_pixel << 6) / 8));
}
