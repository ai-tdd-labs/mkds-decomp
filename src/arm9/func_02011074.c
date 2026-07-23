// PURPOSE: Initializes the shared 3D rendering state.
// This installs the default geometry commands, lighting, materials, and viewport.
// It also resets the projection, camera, base transform, and view vectors.

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

typedef struct GraphicsState {
    u32 command0;                 /* 0x000 */
    u32 projection_mode;          /* 0x004 */
    u8 projection_matrix[0x40];   /* 0x008 */
    u32 position_mode;            /* 0x048 */
    u8 camera_matrix[0x30];       /* 0x04c */
    u32 command1;                 /* 0x07c */
    u32 light_vector[4];          /* 0x080 */
    u32 command2;                 /* 0x090 */
    u32 material_color0;          /* 0x094 */
    u32 material_color1;          /* 0x098 */
    u32 polygon_attr;             /* 0x09c */
    u32 viewport;                 /* 0x0a0 */
    u32 command3;                 /* 0x0a4 */
    u32 light_color[4];           /* 0x0a8 */
    u32 command4;                 /* 0x0b8 */
    u8 base_rotation[0x24];       /* 0x0bc */
    s32 base_translation[3];      /* 0x0e0 */
    s32 base_scale[3];            /* 0x0ec */
    u32 texture_image_param;      /* 0x0f8 */
    u32 flags;                    /* 0x0fc */
    u8 derived_matrices[0x140];   /* 0x100 */
    s32 camera_position[3];       /* 0x240 */
    s32 camera_up[3];             /* 0x24c */
    s32 camera_target[3];         /* 0x258 */
} GraphicsState;

extern GraphicsState data_0217029c;
extern u32 data_021702a4;
extern u32 data_021702e8;
extern u32 data_02170358;

extern void Matrix4x3_Identity(void *matrix);
extern void func_02147954(void *matrix);
extern void MTX_Identity33_(void *matrix);

void func_02011074(void)
{
    data_0217029c.command0 = 0x17101610;
    data_0217029c.projection_mode = 0;
    data_0217029c.position_mode = 2;
    data_0217029c.command1 = 0x32323232;
    data_0217029c.command2 = 0x60293130;
    data_0217029c.command3 = 0x33333333;
    data_0217029c.command4 = 0x002a1b19;

    Matrix4x3_Identity(&data_021702e8);
    func_02147954(&data_021702a4);

    data_0217029c.light_vector[0] = 0x2d8b62d8;
    data_0217029c.light_vector[1] = 0x40000200;
    data_0217029c.light_vector[2] = 0x800001ff;
    data_0217029c.light_vector[3] = 0xc0080000;
    data_0217029c.material_color0 = 0x4210c210;
    data_0217029c.material_color1 = 0x4210c210;
    data_0217029c.polygon_attr = 0x001f008f;
    data_0217029c.viewport = 0xbfff0000;
    data_0217029c.light_color[0] = 0x00007fff;
    data_0217029c.light_color[1] = 0x4000001f;
    data_0217029c.light_color[2] = 0x800003e0;
    data_0217029c.light_color[3] = 0xc0007c00;
    data_0217029c.base_translation[0] = 0;
    data_0217029c.base_translation[1] = 0;
    data_0217029c.base_translation[2] = 0;

    MTX_Identity33_(&data_02170358);

    data_0217029c.base_scale[0] = 0x1000;
    data_0217029c.base_scale[1] = 0x1000;
    data_0217029c.base_scale[2] = 0x1000;
    data_0217029c.texture_image_param = 0;
    data_0217029c.flags = 0;
    data_0217029c.camera_position[2] = 0;
    data_0217029c.camera_position[1] = 0;
    data_0217029c.camera_position[0] = 0;
    data_0217029c.camera_up[2] = 0;
    data_0217029c.camera_up[0] = 0;
    data_0217029c.camera_up[1] = 0x1000;
    data_0217029c.camera_target[1] = 0;
    data_0217029c.camera_target[0] = 0;
    data_0217029c.camera_target[2] = -0x1000;
}
