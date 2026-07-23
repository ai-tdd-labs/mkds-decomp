// PURPOSE: Sets up the texture data for a menu resource.
// The argument is probably an NSBTX resource file.
// Its TEX0 block is saved in the shared menu state before the resource setup runs.

typedef struct StructCE {
    char pad[0x1d4];
    void *tex0Block;
} StructCE;

extern void *Nsbtx_GetTEX0Block(void *resource);
extern void NNS_G3dResDefaultSetup(void *resource);
extern StructCE *data_0217ad08;

void func_02078f78(void *resource)
{
    void *tex0Block = Nsbtx_GetTEX0Block(resource);

    data_0217ad08->tex0Block = tex0Block;
    NNS_G3dResDefaultSetup(resource);
}
