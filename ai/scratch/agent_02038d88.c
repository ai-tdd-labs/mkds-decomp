// PURPOSE: Creates a display configuration from a template.
// Arguments: heap supplies allocation memory and template_data supplies its initial settings.
// The configuration probably allocates an extra small block for one display mode.

typedef struct {
    char padding_00[0xa];
    unsigned short mode;
    char padding_0c[0x60];
    void *mode_data;
} DisplayConfig;

extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern void DisplayConfig_SomeFn(DisplayConfig *config, char *template_data);

DisplayConfig *CreateDisplayConfig(void *heap, char *template_data)
{
    DisplayConfig *config;
    unsigned char *mode_data;

    config = Mem_AllocateHeap(heap, 0xdc);
    DisplayConfig_SomeFn(config, template_data);
    if (config->mode == 1) {
        mode_data = Mem_AllocateHeap(heap, 8);
        *(unsigned short *)mode_data = 0x5000;
        mode_data[2] = 1;
        mode_data[3] = 1;
        config->mode_data = mode_data;
    }
    return config;
}
