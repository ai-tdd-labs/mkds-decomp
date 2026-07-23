/* PURPOSE: Prepares the item-box models and animation lookup tables.
 *
 * Loads the box and question-mark billboard models, configures their render
 * attributes, and allocates sine/cosine tables used by item-box animation.
 * A special race configuration also clears one flag on both models.
 */

typedef int fx32;
typedef short fx16;
typedef long long fx64;

typedef struct BillboardModel {
    int field_00;
    int field_04;
    int field_08;
    int field_0c;
    unsigned int renderAttributes;
    unsigned int flags;
} BillboardModel;

typedef struct ItemBoxTrigEntry {
    fx32 cosine;
    fx32 sine;
    fx32 cosineSquared;
    fx32 sineSquared;
    fx32 sineCosine;
} ItemBoxTrigEntry;

typedef struct ItemBoxSinCosEntry {
    fx32 cosine;
    fx32 sine;
} ItemBoxSinCosEntry;

extern int data_0216bfa4;
extern int data_0216bfb0;
extern BillboardModel *data_0217b71c;
extern BillboardModel *data_0217b710;
extern ItemBoxTrigEntry *data_0217b704;
extern ItemBoxSinCosEntry *data_0217b708;
extern fx16 data_0215d4b4[];
extern int *gRaceConfig;

extern void *FormatFindMapObjFileBuffer_0_from_thumb(void *name);
extern void BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
    void *destination, void *modelBuffer, void *textureBuffer, void *parameters);
extern void BillboardModel_SomeFn(void *model);
extern void *GetActiveExecutionContext(void);
extern void *ExecutionContext_GetHeapHandle(void *context);
extern void *Mem_AllocateHeap(void *heap, unsigned int size);
extern int MaybeBoundsCheck(int value, int limit);
extern fx64 Multiply64(fx64 left, fx64 right);

void func_020de84c(void)
{
    BillboardModel *model;
    int i;
    fx32 cosine;
    fx32 sine;
    int tableIndex;
    int j;

    BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
        &data_0217b71c,
        FormatFindMapObjFileBuffer_0_from_thumb(&data_0216bfa4), 0, 0);
    BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(
        &data_0217b710,
        FormatFindMapObjFileBuffer_0_from_thumb(&data_0216bfb0), 0, 0);
    BillboardModel_SomeFn(data_0217b71c);
    BillboardModel_SomeFn(data_0217b710);

    model = data_0217b71c;
    model->renderAttributes &= 0x8000ffff;
    model->renderAttributes |= 0x52940000;
    model = data_0217b710;
    model->renderAttributes &= 0x8000ffff;
    model->renderAttributes |= 0x52940000;

    data_0217b704 = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x1770);
    for (i = 0; i < 300; i++) {
        /* Convert this entry number to an index into the packed FX trig table. */
        tableIndex =
            ((unsigned short)MaybeBoundsCheck(
                 (int)((unsigned int)i << 16), 300) >>
             4) <<
            1;
        cosine = data_0215d4b4[tableIndex + 1];
        sine = data_0215d4b4[tableIndex];
        data_0217b704[i].cosine = cosine;
        data_0217b704[i].sine = sine;
        data_0217b704[i].cosineSquared =
            (fx32)(Multiply64((fx64)cosine, (fx64)cosine) >> 12);
        data_0217b704[i].sineSquared =
            (fx32)(Multiply64((fx64)sine, (fx64)sine) >> 12);
        data_0217b704[i].sineCosine =
            (fx32)(Multiply64((fx64)cosine, (fx64)sine) >> 12);
    }

    data_0217b708 = Mem_AllocateHeap(
        ExecutionContext_GetHeapHandle(GetActiveExecutionContext()), 0x410);
    for (j = 0; j < 130; j++) {
        tableIndex =
            ((unsigned short)MaybeBoundsCheck(
                 (int)((unsigned int)j << 16), 130) >>
             4) <<
            1;
        data_0217b708[j].cosine = data_0215d4b4[tableIndex + 1];
        data_0217b708[j].sine = data_0215d4b4[tableIndex];
    }

    if (*gRaceConfig == 0x1d) {
        data_0217b71c->flags &= 0xffff7fff;
        data_0217b710->flags &= 0xffff7fff;
    }
}
