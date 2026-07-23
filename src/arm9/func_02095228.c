// PURPOSE: Rolls a fresh random number for every child in a node's list, so each one gets its own luck value each frame.
// Takes a node (r0) that owns a pointer-array of child nodes plus a count. For
// each child it advances a shared 64-bit linear-congruential RNG (state =
// state*mult + inc, stored in the global system struct at *data_0217561c+0x498)
// and writes a reduced random value in [0,15) into the child's field at +0xa0.
// The scan stops at the first NULL child (or when count is reached).
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct Node Node;
struct Node {
    Node **list;      // 0x0: array of child pointers
    u16 count;        // 0x4: number of slots
    u8 pad[0xa0 - 6];
    u32 rnd;          // 0xa0: latest random roll (0..14)
};

typedef struct {
    u64 state;        // 0x0
    u64 mult;         // 0x8
    u64 inc;          // 0x10
} Rng;

typedef struct {
    u8 pad0[0x498];
    Rng rng;          // 0x498
} Sys;

extern Sys *data_0217561c;   // global pointer to the system struct

void func_02095228(Node *node)
{
    int i;
    Node *child;

    if (node == 0) {
        return;
    }
    // stop at the count limit or the first NULL child, whichever comes first
    for (i = 0; i < node->count && (child = node->list[i]) != 0; i++) {
        Rng *rng;
        u32 hi;
        // advance the shared 64-bit LCG
        rng = &data_0217561c->rng;
        rng->state = rng->mult * rng->state + rng->inc;
        // reduce the high word to [0,15) via the multiply-high trick
        hi = (u32)(rng->state >> 32);
        child->rnd = (u16)(((u64)hi * 15) >> 32);
    }
}
