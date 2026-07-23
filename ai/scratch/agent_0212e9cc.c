// PURPOSE: Checks whether a sequence can be loaded.
// Takes a sequence identifier and probably an associated sound-bank identifier.
// Requests the sequence with the standard load settings.
// Returns one when the loader reports success.

extern int NNSi_SndArcLoadSeq(int sequence_id, int bank_id, int archive_id,
                              int load_flag, int reserved);

int CheckMaybeLoadSseqOk(int sequence_id, int archive_id) {
    return NNSi_SndArcLoadSeq(sequence_id, 0xff, archive_id, 1, 0) == 0;
}
