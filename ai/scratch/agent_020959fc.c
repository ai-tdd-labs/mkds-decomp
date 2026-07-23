/*
PURPOSE: Register a handler by passing its callback and id 0x125 to the setup function.

Calls func_0209bf70 with the func_02095efc callback, literal args (0,0,2,1)
and the id constant 0x125 (pooled: not ARM-immediate-encodable).
*/

extern void func_0209bf70(void *arg0, int arg1, int arg2, int arg3, int arg4, void *arg5);
extern void func_02095efc(void);

void func_020959fc(void) {
    func_0209bf70(
        (void *)func_02095efc,  /* r0 - callback */
        0,                      /* r1 */
        0,                      /* r2 */
        2,                      /* r3 */
        1,                      /* [sp+0] */
        (void *)0x125           /* [sp+4] - handler id (pool constant) */
    );
}
