// PURPOSE: Copies data into the current position of a buffer.
// The buffer tracks its base pointer, capacity, and current position.
// The copy length is probably clipped so it does not pass the capacity.

typedef unsigned int u32;
typedef unsigned char u8;

typedef struct {
    u8 *data;
    u32 size;
    u32 position;
} Buffer;

extern u32 func_0213c9e8(u8 *destination, const void *source, u32 size);

u32 func_0213ca94(Buffer *buffer, const void *source, u32 size)
{
    // Keep the requested length unless the remaining buffer space is smaller.
    if (buffer->position + size > buffer->size) {
        size = buffer->size - buffer->position;
    }
    func_0213c9e8(buffer->data + (buffer->position << 1), source, size);
    buffer->position += size;
}
