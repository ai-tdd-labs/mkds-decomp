// PURPOSE: Queues a sound effect and advances its event counter.
// The context and sound identifier are passed to the driver's sound queue.
// The counter probably selects a sound variation and determines its volume.

extern int data_0217ccac;
extern void DriverContext_MaybeQueuePlaySfx(void *ctx, int sound, int volume, int flags);

void func_0210ba78(void *ctx, int sound)
{
    int event = data_0217ccac;

    DriverContext_MaybeQueuePlaySfx(ctx, sound + event,
        (unsigned char)(0x7f - (event >> 1)), 0);
    data_0217ccac += 10;
}
