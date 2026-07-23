// PURPOSE: Queues a sound effect while advancing the driver's event counter.
// The supplied driver context is forwarded to the sound queue.
// The counter probably identifies the next queued sound event.
extern int data_0217d1f0;
extern void DriverContext_MaybeQueuePlaySfx(void *ctx, int sound, int volume, int flags);

void func_0210f9f0(void *ctx) {
    int event = data_0217d1f0;

    data_0217d1f0 = event + 1;
    DriverContext_MaybeQueuePlaySfx(ctx, event + 0xea, 0x7f, 0);
}
