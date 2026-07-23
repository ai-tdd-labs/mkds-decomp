// PURPOSE: Resets part of a structure and checks it against an input.
// The first argument is a four-word work structure.
// It probably preserves each pair of trailing words before replacing them with defaults.

typedef unsigned long long u64;

typedef struct StructDW {
    u64 head;
    u64 tail;
} StructDW;

extern void StructDW_MaybeCreate_from_thumb(StructDW *out);
extern int StructDW_SomeFn_0_from_thumb(StructDW *self, void *input);

int func_02151f48(StructDW *self, void *input)
{
    StructDW created;

    StructDW_MaybeCreate_from_thumb(&created);
    self->head = self->tail;
    self->tail = created.tail;

    if (StructDW_SomeFn_0_from_thumb(self, input)) {
        return 1;
    }
    return 0;
}
