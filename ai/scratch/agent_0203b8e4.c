/*
 * PURPOSE: Counts matching entries and uses that count to limit a second scan.
 * The argument points to six 32-bit words used as two 64-bit values and an accumulator.
 * The helper tests eight small indices; the first scan counts successful tests.
 * The function probably updates the first 64-bit value before returning the second scan index.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct MatchState {
    unsigned int value_lo;
    unsigned int value_hi;
    unsigned int factor_lo;
    unsigned int factor_hi;
    unsigned int add_lo;
    unsigned int add_hi;
} MatchState;

extern int func_0203b96c(int index);
extern unsigned long long Multiply64(unsigned int left_lo, unsigned int left_hi,
                                     unsigned int right_lo, unsigned int right_hi);

// PURPOSE: Counts matching entries and uses that count to limit a second scan.
int func_0203b8e4(MatchState *state)
{
    u8 matches = 0;
    u8 index = 0;
    u16 limit;
    u8 accepted = 0;

    do {
        if (func_0203b96c(index) != 0)
            matches++;
        index++;
    } while (index < 8);

    if (matches != 0) {
        unsigned long long product;

        product = Multiply64(state->factor_lo, state->factor_hi,
                             state->value_lo, state->value_hi);
        product += ((unsigned long long)state->add_hi << 32) | state->add_lo;
        state->value_lo = (unsigned int)product;
        state->value_hi = (unsigned int)(product >> 32);

    }

    if (matches == 0)
        limit = (u16)state->value_hi;
    else {
        unsigned long long product;

        product = Multiply64(state->value_hi, 0, matches, 0);
        limit = (u16)(product >> 32);
    }

    index = 0;
    do {
        if (func_0203b96c(index) != 0) {
            accepted++;
            if (accepted > limit)
                break;
        }
        index++;
    } while (index < 8);

    return index;
}
