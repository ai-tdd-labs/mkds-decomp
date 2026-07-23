// PURPOSE: Records reliable network timing samples for each peer.
// The first argument contains four timestamps used to remove remote processing time.
// The second argument selects a peer record in the shared network work area.
// Too many rejected samples probably mark that peer as unreliable.

typedef unsigned char u8;
typedef unsigned long long u64;

typedef struct TimingSample {
    u64 outer_start;
    u64 inner_start;
    u64 inner_end;
    u64 outer_end;
} TimingSample;

typedef struct ByteStride38 {
    u8 value;
    u8 padding[0x37];
} ByteStride38;

extern u8 *data_0217aa14;

void func_0205b824(TimingSample *sample, int peer)
{
    u8 count;
    u8 *work;
    int peer_offset;
    u64 interval;
    int accepted;

    peer_offset = peer * 0x38;
    work = data_0217aa14;
    count = *(work + peer_offset + 0x48);

    if (count >= 12) {
        return;
    }

    if (count != 0) {
        interval = (sample->outer_end - sample->outer_start) -
                   (sample->inner_end - sample->inner_start);

        if ((interval << 6) / 0x82ea < 1000) {
            *(u64 *)((work + 0x3c) + peer_offset) += interval;
            accepted = 1;
        } else {
            accepted = 0;
            ((ByteStride38 *)(work + 0x49))[peer].value++;
            if ((data_0217aa14 + peer_offset)[0x49] > 0x40) {
                data_0217aa14[0x748] |= 1 << peer;
            }
        }
    } else {
        accepted = 1;
    }

    if (accepted != 0) {
        count++;
    }
    (data_0217aa14 + peer_offset)[0x48] = count;
}
