/*
 * PURPOSE: Loads the AD00 "killer item" 3D model (mesh, texture, shadow
 * variant, and animation) and wires it into the shared racer-manager slot.
 *
 * Arguments:
 *   heapId - heap id, forwarded to Model_CreateFromNsbmdNsbtxMetaCopy and
 *            (probably reused, not as a heap id) to Animation_CreateFrom /
 *            Animation_RegisterAll.
 *
 * Loads four file buffers (killer-item nsbmd/nsbtx, a "_s" nsbmd variant,
 * and a nsbca animation file) via the KME/KM1/KM2/KSB file-buffer finders,
 * builds a ModelBlock in-place at RacerManager->model, renders it once
 * (probably to force material setup), builds an Animation in-place at
 * RacerManager->anim from the nsbca buffer and registers/activates it, sets
 * up RacerManager->sh from the "_s" nsbmd buffer, and finally applies
 * default fields to the model.
 */

typedef struct RacerManager RacerManager;
typedef struct ModelBlock ModelBlock;
typedef struct Animation Animation;
typedef struct StructAD00Sh StructAD00Sh;

/* RacerManager (via RacerManagerPtr) @ 0x0217ad00: 0x2c:ModelBlock model;
 * 0x98:StructAD00Sh sh; 0x10c:Animation anim  [ai/structs.jsonl] */
#define RM_MODEL(rm) ((ModelBlock *)((char *)(rm) + 0x2c))
#define RM_SH(rm)    ((StructAD00Sh *)((char *)(rm) + 0x98))
#define RM_ANIM(rm)  ((Animation *)((char *)(rm) + 0x10c))

extern RacerManager *data_0217ad00; /* pointer to RacerManager (dereferenced) */

extern void *FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(char *path);
extern void *FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(char *path);
extern ModelBlock *Model_CreateFromNsbmdNsbtxMetaCopy(int heapId, void *modelMem, void *nsbmd, void *nsbtx);
extern void ModelBlock_SomeMatFn(ModelBlock *model, int arg1);
extern void Model_Render(ModelBlock *model, int arg1);
extern void Animation_CreateFrom(int arg0, Animation *anim, ModelBlock *model, int arg3, int heapId, void *nsbmd);
extern void Animation_RegisterAll(Animation *anim, void *nsbca, int heapId);
extern void Animation_SetAt(Animation *anim, int index);
extern void StructAD00Sh_SomeFn_2(StructAD00Sh *sh, void *nsbmd, int arg2);
extern void StructML_SetSomeDefaultFields(ModelBlock *model);

extern char data_021657b0[]; /* "character/common/KillerItem.nsbmd" */
extern char data_021657d4[]; /* "character/common/KillerItem.nsbtx" */
extern char data_021657f8[]; /* "character/common/KillerItem_s.nsbmd" */
extern char data_0216581c[]; /* "character/common/KillerItem.nsbca" */

void LoadAD00KillerItemModel_from_thumb(int heapId)
{
    void *nsbmd;
    void *nsbtx;
    void *nsbmdS;
    void *nsbca;

    nsbmd = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(data_021657b0);
    nsbtx = FindFileBuffer_KME_KM1_KM2_KSB_from_thumb(data_021657d4);
    nsbmdS = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(data_021657f8);

    ModelBlock_SomeMatFn(
        Model_CreateFromNsbmdNsbtxMetaCopy(heapId, RM_MODEL(data_0217ad00), nsbmd, nsbtx),
        0);

    Model_Render(RM_MODEL(data_0217ad00), 3);

    nsbca = FindFileBufferGeneric_KME_KM1_KM2_KSB_from_thumb(data_0216581c);

    Animation_CreateFrom(0, RM_ANIM(data_0217ad00), RM_MODEL(data_0217ad00), 1, heapId, nsbmd);
    Animation_RegisterAll(RM_ANIM(data_0217ad00), nsbca, heapId);
    Animation_SetAt(RM_ANIM(data_0217ad00), 0);

    StructAD00Sh_SomeFn_2(RM_SH(data_0217ad00), nsbmdS, 3);

    StructML_SetSomeDefaultFields(RM_MODEL(data_0217ad00));
}
