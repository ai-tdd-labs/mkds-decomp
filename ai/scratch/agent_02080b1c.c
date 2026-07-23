/*
 * PURPOSE: Moves a chase/camera target one step further along a branching
 * path of waypoints and computes the direction it is now heading.
 *
 * Arg: obj = a path-follower state block.
 * If the driver entry for obj->entry has a certain flag set, or the current
 * waypoint has <=1 outgoing links, nothing is advanced. Otherwise a 64-bit
 * random number generator is advanced and used to pick one of the outgoing
 * links (index = random_high * link_count >> 32). The old waypoint is saved
 * as prev, obj->cur becomes the chosen next waypoint, and obj->dir is set to
 * the normalized vector from the previous waypoint's position to the new one.
 */

typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef int fx32;

typedef struct { fx32 x, y, z; } VecFx32;

typedef struct Node {
    struct Node *link[6];   /* 0x00: outgoing waypoint links, indexed by idx */
    VecFx32 *pos;           /* 0x18: pointer to world position */
    u32 pad1c[2];
    u16 count;              /* 0x24: number of outgoing links */
} Node;

typedef struct {
    u64 state;              /* 0x00: 64-bit LCG state */
    u64 mult;               /* 0x08: multiplier */
    u64 inc;                /* 0x10: increment */
} Rng;

typedef struct {
    Node *cur;              /* 0x00: current waypoint */
    Node *prev;             /* 0x04: previous waypoint */
    VecFx32 dir;            /* 0x08: heading direction */
    u16 pad14[4];
    u16 entry;              /* 0x1c: driver entry id */
} Follower;

extern u32 *func_0207a974(u16 entry);        /* returns driver-entry record */
extern Rng *func_0208537c(Node *node);       /* returns the RNG state block */
extern void func_021484d0(const VecFx32 *a, const VecFx32 *b, VecFx32 *c); /* c = a - b */
extern void func_02039860(VecFx32 *dst, const VecFx32 *src); /* normalize */

void func_02080b1c(Follower *obj)
{
    u32 idx = 0;
    u32 raw;

    if ((func_0207a974(obj->entry)[0x4c / 4] & 0x10000000) == 0) {
        Node *node = obj->cur;
        u32 n = node->count;
        if (n > 1) {
            Rng *r = func_0208537c(node);
            if (n == 0) {
                raw = 0;
            } else {
                r->state = r->mult * r->state + r->inc;
                if (n == 0)
                    raw = (u32)(r->state >> 32);
                else
                    raw = (u32)(((r->state >> 32) * n) >> 32);
            }
            idx = (u16)raw;
        }
    }

    obj->prev = obj->cur;
    obj->cur = obj->cur->link[idx];
    func_021484d0(obj->cur->pos, obj->prev->pos, &obj->dir);
    func_02039860(&obj->dir, &obj->dir);
}
