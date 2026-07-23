/*
 * PURPOSE: Update a linked sub-object's low-nibble flags and, if the owner is active, forward the active state and flag bits to a global follow-up handler.
 */

typedef struct StructML_Sub {
    char pad_0x00[0x14];
    volatile unsigned int flags; /* 0x14 */
} StructML_Sub;

typedef struct StructML_Owner {
    char pad_0x00[0xc];
    StructML_Sub *sub;  /* 0xc */
    int active;         /* 0x10 */
} StructML_Owner;

extern void StructML_SomeFn_8(int active, unsigned int flagBits);

void func_0209ba08(StructML_Owner *owner, unsigned int flagBits) {
    StructML_Sub *sub = owner->sub;
    int active;

    if (sub != 0) {
        sub->flags = sub->flags & ~0xf;
        sub->flags = sub->flags | flagBits;
    }

    active = owner->active;
    if (active != 0) {
        StructML_SomeFn_8(active, flagBits);
    }
}
