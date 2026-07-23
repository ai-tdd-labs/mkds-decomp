// PURPOSE: Configures a racer with default settings.
// The caller supplies the racer object in the first argument.
// This probably selects the default setup using fixed sentinel values.

extern void StructCO_ConfigureRacerDefault(void *racer, int a1, int a2,
                                           int a3, int a4, int a5);

void func_020ccb48(void *racer)
{
    StructCO_ConfigureRacerDefault(racer, -1, -1, 4, -1, 3);
}
