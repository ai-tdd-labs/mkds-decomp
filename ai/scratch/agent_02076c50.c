// PURPOSE: Sets the camera frustum from the supplied view settings.
// The second argument probably selects an alternate far-plane value.
// It writes the projection matrix and clears pending graphics-state bits.

typedef int fx32;

typedef struct ViewFrustumSettings {
    unsigned char pad_00[0x70];
    fx32 near;
    fx32 far;
    fx32 top;
    fx32 bottom;
    fx32 left;
    fx32 right;
    unsigned char pad_88[4];
    fx32 alternate_far;
} ViewFrustumSettings;

typedef struct GraphicsState {
    unsigned char pad_00[0xfc];
    unsigned int flags_fc;
} GraphicsState;

extern void G3i_FrustumW_(fx32 top, fx32 bottom, fx32 left, fx32 right,
                          fx32 near, fx32 far, fx32 scale_w, int flag,
                          void *matrix);
extern char data_021702a4[];
extern GraphicsState data_0217029c;

void func_02076c50(ViewFrustumSettings *settings, int use_alternate_far)
{
    G3i_FrustumW_(settings->top, settings->bottom, settings->left,
                  settings->right, settings->near,
                  use_alternate_far ? settings->alternate_far : settings->far,
                  0x1000, 0, data_021702a4);
    data_0217029c.flags_fc &= ~0x50;
}
