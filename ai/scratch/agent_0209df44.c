/*
PURPOSE: Registers two handler callbacks under ID 0x18d.
Thin wrapper: calls func_0209bf70 with two function pointers
(func_0209ea10 and func_0209e988), zeroed middle arguments, and the
constant 0x18d (probably a message/event ID or size). No return value.
*/

typedef void (*Callback)(void);

extern void func_0209bf70(Callback cb1, int a1, Callback cb2, int a2, int a3, int id);
extern void func_0209ea10(void);
extern void func_0209e988(void);

void func_0209df44(void)
{
    func_0209bf70((Callback)func_0209ea10, 0, (Callback)func_0209e988, 0, 0, 0x18d);
}
