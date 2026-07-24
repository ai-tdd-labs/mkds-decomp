// PURPOSE: Builds a view matrix for the camera.
// The first three arguments provide the camera position, up direction, and target.
// When load is nonzero, the matrix is also sent to the geometry engine.
// When mtx is non-null, the same matrix is written to memory.

typedef signed int fx32;
typedef signed int BOOL;
typedef volatile unsigned int vu32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct Matrix4x3 {
    fx32 values[12];
} Matrix4x3;

extern void VecFx32_Normalize(const VecFx32 *a, VecFx32 *dst);
extern void VecFx32_CrossProduct(const VecFx32 *a, const VecFx32 *b,
                                 VecFx32 *dst);
extern fx32 Vector3_DotProduct(const VecFx32 *a, const VecFx32 *b);

void G3i_LookAt_(const VecFx32 *a, const VecFx32 *b, const VecFx32 *c,
                  BOOL load, Matrix4x3 *mtx)
{
    VecFx32 temp, temp1, temp2;
    fx32 c1, c2, c3;
    vu32 *reg_ptr;

    temp.x = a->x - c->x;
    temp.y = a->y - c->y;
    temp.z = a->z - c->z;
    VecFx32_Normalize(&temp, &temp);
    VecFx32_CrossProduct(b, &temp, &temp1);
    VecFx32_Normalize(&temp1, &temp1);
    VecFx32_CrossProduct(&temp, &temp1, &temp2);

    if (load) {
        *(vu32 *)0x04000440 = 0x2;
        reg_ptr = (vu32 *)0x0400045c;
        *reg_ptr = (vu32)temp1.x;
        *reg_ptr = (vu32)temp2.x;
        *reg_ptr = (vu32)temp.x;
        *reg_ptr = (vu32)temp1.y;
        *reg_ptr = (vu32)temp2.y;
        *reg_ptr = (vu32)temp.y;
        *reg_ptr = (vu32)temp1.z;
        *reg_ptr = (vu32)temp2.z;
        *reg_ptr = (vu32)temp.z;
    }

    c1 = -Vector3_DotProduct(a, &temp1);
    c2 = -Vector3_DotProduct(a, &temp2);
    c3 = -Vector3_DotProduct(a, &temp);

    if (load) {
        *reg_ptr = (vu32)c1;
        *reg_ptr = (vu32)c2;
        *reg_ptr = (vu32)c3;
    }

    if (mtx) {
        mtx->values[0] = temp1.x;
        mtx->values[1] = temp2.x;
        mtx->values[2] = temp.x;
        mtx->values[3] = temp1.y;
        mtx->values[4] = temp2.y;
        mtx->values[5] = temp.y;
        mtx->values[6] = temp1.z;
        mtx->values[7] = temp2.z;
        mtx->values[8] = temp.z;
        mtx->values[9] = c1;
        mtx->values[10] = c2;
        mtx->values[11] = c3;
    }
}
