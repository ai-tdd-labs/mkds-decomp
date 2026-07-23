// PURPOSE: Loads the selected kart's menu models and emblem files.
// This worker rebuilds the current resource slot on a fresh expansion heap.
// It loads the selected character's emblem and the selected kart's model files.
// The final halfword in each resource slot probably tracks loading progress.

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct KartSelection {
    int character;
    int kart;
} KartSelection;

typedef struct KartNameRecord {
    u8 data[0xe0];
} KartNameRecord;

typedef struct CEElem {
    void *memory;
    void *heap;
    void *emblemModel;
    void *emblemTexture;
    void *customEmblemTexture;
    void *emblemAnimation;
    void *kartModel;
    void *kartTexture;
    void *tireModel;
    void *tireTexture;
    void *shadowModel;
    void *field_2c;
    u16 loadState;
} CEElem;

typedef struct StructCE {
    u8 pad_000[0x20];
    KartSelection *selection;
    u8 pad_024[0x1a4];
    KartNameRecord *kartNames;
    u8 pad_1cc[0x28];
    CEElem elems[2];
    u8 pad_25c[0xa];
    s16 currentElem;
    int field_268;
} StructCE;

extern StructCE *data_0217ad08;

extern void Mem_Exp_Finalize(void *heap);
extern void *Mem_Exp_Create(void *memory, u32 size, int option);
extern void MaybeDisposeCommonHeaderFileData(void *resource);
extern void ReadFileFromMountManagerHandle_from_thumb(char *path, void *heap,
                                                       void *destination);

extern char *FormatCharacterEmblemNsbmdPath(int character, int alt);
extern char *FormatCharacterEmblemNsbtxPath(int character, int flag);
extern char *FormatCharacterEmblemNsbcaPath(int character, int animation);
extern char *FormatEmblemNsbtx(int character);
extern char *FormatCharacterKartNsbmdPath(int character);
extern char *FormatCharacterKartNsbtxPath(int character);
extern char *FormatKartShadowNsbmdPath(int kart);
extern char *FormatKartTireNsbmdPath(int kart, char *tireName);
extern char *FormatKartTireNsbtxPath(int kart, char *tireName);

void func_02077d68(void)
{
    StructCE *work;
    CEElem *elems;
    int elemIndex;
    int character;
    CEElem *elem;
    int kart;
    KartNameRecord *kartName;

    work = data_0217ad08;
    elems = work->elems;
    elemIndex = work->currentElem;
    elem = &elems[elemIndex];
    character = work->selection->character;
    kart = work->selection->kart;

    elem->loadState = 0;
    Mem_Exp_Finalize(elem->heap);
    elem->heap = Mem_Exp_Create(
        *(void **)((int)elems + elemIndex * 0x34), 0xf000, 0);

    if (character != -1 && elem->emblemModel != 0) {
        MaybeDisposeCommonHeaderFileData(elem->emblemModel);
        MaybeDisposeCommonHeaderFileData(elem->emblemTexture);
        MaybeDisposeCommonHeaderFileData(elem->customEmblemTexture);
        MaybeDisposeCommonHeaderFileData(elem->kartModel);
        MaybeDisposeCommonHeaderFileData(elem->kartTexture);
        MaybeDisposeCommonHeaderFileData(elem->tireModel);
        MaybeDisposeCommonHeaderFileData(elem->tireTexture);
        MaybeDisposeCommonHeaderFileData(elem->shadowModel);
    }

    kartName = &data_0217ad08->kartNames[kart];

    ReadFileFromMountManagerHandle_from_thumb(
        FormatCharacterEmblemNsbmdPath((u16)character, 1),
        elem->heap, &elem->emblemModel);
    ReadFileFromMountManagerHandle_from_thumb(
        FormatCharacterEmblemNsbtxPath((u16)character, 1),
        elem->heap, &elem->emblemTexture);
    ReadFileFromMountManagerHandle_from_thumb(
        FormatCharacterEmblemNsbcaPath((u16)character, 2),
        elem->heap, &elem->emblemAnimation);
    ReadFileFromMountManagerHandle_from_thumb(
        FormatEmblemNsbtx((u16)character),
        elem->heap, &elem->customEmblemTexture);
    ReadFileFromMountManagerHandle_from_thumb(
        FormatCharacterKartNsbmdPath((u16)kart),
        elem->heap, &elem->kartModel);
    ReadFileFromMountManagerHandle_from_thumb(
        FormatCharacterKartNsbtxPath((u16)kart),
        elem->heap, &elem->kartTexture);
    ReadFileFromMountManagerHandle_from_thumb(
        FormatKartShadowNsbmdPath((u16)kart),
        elem->heap, &elem->shadowModel);
    ReadFileFromMountManagerHandle_from_thumb(
        FormatKartTireNsbmdPath((u16)kart, (char *)kartName),
        elem->heap, &elem->tireModel);
    ReadFileFromMountManagerHandle_from_thumb(
        FormatKartTireNsbtxPath((u16)kart, (char *)kartName),
        elem->heap, &elem->tireTexture);
}
