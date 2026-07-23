// PURPOSE: Generates a code for a valid time-trial record.
// The internal ID selects the saved record and out receives its code.
// A record is probably valid only when its byte at offset 0x18 is nonzero.

typedef unsigned char u8;

typedef struct TimeTrialRecord {
    u8 data[0x1c];
} TimeTrialRecord;

extern int TimeTrialRecord_CopyFrom_from_thumb(
    int internalId, int recordBank, TimeTrialRecord *destination);
extern int GenerateTimeTrialCodeImpl(char *out, TimeTrialRecord *rec,
                                     int internalId);

int GenerateTimeTrialCode(int internalId, char *out)
{
    TimeTrialRecord record;

    if (TimeTrialRecord_CopyFrom_from_thumb(internalId, 0, &record) != 0) {
        if (record.data[0x18] != 0) {
            return GenerateTimeTrialCodeImpl(out, &record, internalId);
        }
    }
    return 0;
}
