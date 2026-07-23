// PURPOSE: Applies texture and palette updates to every model material.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int ModelBlock_SomeTexPltFn_10(void *material, int arg);
extern int ModelBlock_SomeTexPltFn_11(void *material, int arg);

int func_02010168(void *model, int arg)
{
    unsigned int i;
    int result;

    result = 1;
    i = 0;

    if (i >= *((u8 *)model + 9))
        goto done;

    {
        u8 *base = (u8 *)model + 8;

        do {
            u16 stride = *(u16 *)(base + *(u16 *)((u8 *)model + 0xE));
            void *material = (u8 *)model + *(u32 *)(base + *(u16 *)((u8 *)model + 0xE) + stride * i + 4);

            result &= ModelBlock_SomeTexPltFn_10(material, arg);
            result &= ModelBlock_SomeTexPltFn_11(material, arg);
            i++;
        } while (i < *((u8 *)model + 9));
    }

done:
    return result;
}
