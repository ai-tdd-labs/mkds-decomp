/* PURPOSE: Plays a racer effect with a level based on the supplied value.
 * The first argument is probably a racer entry, and the second identifies
 * the effect. In mode 2, the third argument is scaled into an 8-bit level
 * and clamped to 50--127; all other modes use the maximum level.
 */

typedef unsigned char u8;

extern void StructMQRacerEntry_SomeFn_6(
    void *racer, int unused, int effectId, int level, int trailingArg);

void func_02024a28(void *racer, int effectId, int value, int mode)
{
    u8 level;

    if (mode == 2)
    {
        /* Preserve both byte truncations around the bias addition. */
        level = (u8)((u8)((value << 7) >> 12) + 20);

        if (level > 127)
        {
            level = 127;
        }
        else if (level < 50)
        {
            level = 50;
        }
    }
    else
    {
        level = 127;
    }

    StructMQRacerEntry_SomeFn_6(racer, 0, effectId, level, 0);
}
