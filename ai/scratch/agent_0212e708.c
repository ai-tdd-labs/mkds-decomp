// PURPOSE: Loads sequence data and its required sound bank.
// The sequence ID selects an archive entry, while flags and context control loading.
// It probably stores the sequence data through the optional output pointer.

typedef unsigned int u32;

typedef struct SeqInfo {
    u32 file_id;
    unsigned short bank_id;
} SeqInfo;

extern SeqInfo *NNS_SndArcGetSeqInfo(unsigned int sseq_id);
extern int Sound_GetSbnkPointer(unsigned int sbnk_id, char flags, void *ctx,
                                int use_active_sdat, void **out_ptr);
extern void *Sound_PrepareSseqData(unsigned int file_id, void *ctx,
                                   int use_active_sdat);
extern void *Sound_MaybeGetRawFilePointer(unsigned int file_id);

int NNSi_SndArcLoadSeq(unsigned int sseq_id, char flags, void *ctx,
                       int use_active_sdat, void **out_ptr)
{
    SeqInfo *info;
    void *data;
    int result;

    info = NNS_SndArcGetSeqInfo(sseq_id);
    if (info == 0) {
        return 2;
    }

    result = Sound_GetSbnkPointer(info->bank_id, flags, ctx, use_active_sdat, 0);
    if (result != 0) {
        return result;
    }

    if (flags & 1) {
        data = Sound_PrepareSseqData(info->file_id, ctx, use_active_sdat);
        if (data == 0) {
            return 6;
        }
    } else {
        data = Sound_MaybeGetRawFilePointer(info->file_id);
    }

    if (out_ptr != 0) {
        *out_ptr = data;
    }
    return 0;
}
