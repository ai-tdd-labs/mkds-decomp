// PURPOSE: Queues a sound effect unless the event is the default type.
/*
 * The first argument is forwarded as the driver context.
 * The second argument probably selects an event type.
 */

extern void DriverContext_MaybeQueuePlaySfx(void *context, int event, int sound_id,
                                            int parameter);

void func_020f7c60(void *context, int event)
{
    if (event == 1) {
        return;
    }

    DriverContext_MaybeQueuePlaySfx(context, event, 0x7f, 0);
}
