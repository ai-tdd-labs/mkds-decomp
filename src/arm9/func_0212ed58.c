// PURPOSE: Starts a sound sequence using its sequence information.
// The first argument is probably a sound player or handle.
// The second argument selects a sequence whose archive entry supplies its settings.
// Returns zero when that sequence has no archive information.

struct SeqInfo {
    unsigned char pad_0[4];
    unsigned short field_4;
    unsigned char pad_6[2];
    unsigned char field_8;
    unsigned char field_9;
};

extern struct SeqInfo *NNS_SndArcGetSeqInfo(int sequence);
extern int MaybeStartSeq(void *player, unsigned char field_9,
                         unsigned short field_4, unsigned char field_8,
                         struct SeqInfo *info, int sequence);

int func_0212ed58(void *player, int sequence)
{
    struct SeqInfo *info;

    info = NNS_SndArcGetSeqInfo(sequence);
    if (info == 0) {
        return 0;
    }

    return MaybeStartSeq(player, info->field_9, info->field_4, info->field_8,
                         info, sequence);
}
