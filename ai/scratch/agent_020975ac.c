/*
PURPOSE: Registers two handler callbacks under ID 0x1d0.
Thin wrapper: calls func_0209bf70 with two function pointers
(func_020980ec and func_02097ed0), zeroed middle arguments, a constant
1 (probably a flag/priority), and the constant 0x1d0 (probably a
message/event ID or size). No return value.
*/

typedef void (*Callback)(void);

extern void func_0209bf70(Callback cb1, int a1, Callback cb2, int a2, int a3, int id);
extern void func_020980ec(void);
extern void func_02097ed0(void);

void func_020975ac(void)
{
    func_0209bf70((Callback)func_020980ec, 0, (Callback)func_02097ed0, 0, 1, 0x1d0);
}
