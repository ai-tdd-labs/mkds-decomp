// PURPOSE: Queues a sound effect when sound playback is enabled.
// The context and three event values are passed to the racer sound handler.
// The global flag probably disables queued playback when its low bit is clear.

extern int data_0217c780;

extern int StructMQRacerEntry_SomeFn_6(void *context, int mode, int event,
                                       int sound_id, int parameter);

int DriverContext_MaybeQueuePlaySfx(void *context, int event, int sound_id,
                                    int parameter)
{
    if ((data_0217c780 & 1) == 0) {
        return 0;
    }

    return StructMQRacerEntry_SomeFn_6(context, 0, event, sound_id, parameter);
}
