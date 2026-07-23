// PURPOSE: Copies the next available data chunk into a request buffer.

typedef unsigned int u32;

typedef struct GlobalSZRequest {
    char _00[8];
    u32 position;
    char _0c[0x14];
    char buffer[1];
} GlobalSZRequest;

typedef struct GlobalSZState {
    char _00[0x1c];
    u32 position;
    char *source;
    u32 remaining;
} GlobalSZState;

extern GlobalSZState data_0217fa40;
extern void Mem_CpuCopy8(void *dst, const void *src, u32 size);

int GlobalSZ_SomeFn(GlobalSZRequest *request)
{
    GlobalSZState *state = &data_0217fa40;
    u32 base = state->position & (u32)-0x200;

    if (base == request->position) {
        u32 offset = state->position - base;
        u32 size = 0x200 - offset;

        if (size > state->remaining) {
            size = state->remaining;
        }

        Mem_CpuCopy8(request->buffer + offset, state->source, size);
        state->position += size;
        state->source += size;
        state->remaining -= size;
    }

    return state->remaining != 0;
}
