// PURPOSE: Draws racer names and updates the race transfer state.
// Passes the two supplied racer-related pointers to the renderer first.
// It then probably transfers the corresponding race state between them.

extern void DrawRacerNames(void *arg0, void *arg1);
extern void Maybe_race_transfer_s_o(void *arg0, void *arg1);

void func_020b6d98(void *arg0, void *arg1)
{
    DrawRacerNames(arg0, arg1);
    Maybe_race_transfer_s_o(arg0, arg1);
}
