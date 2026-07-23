/*
 * PURPOSE: Turns a race feature (a callback-driven mini-system) on or off
 * depending on which race mode is currently selected.
 *
 * Reads the current race mode from the config (gRaceConfig). Only acts for
 * two modes: 0x25 (probably "enter"/start of the mode) creates the helper
 * objects and wires up their update callback at +0x90; 0x10 (probably
 * "exit"/teardown) swaps one callback and tears the other object down.
 * Any other mode returns immediately. Two global handles (data_0217ae78 and
 * data_0217ae88) hold the created objects. func_0208b7bc is an allocator/
 * constructor (size, params) and func_0208b710 is probably a cleanup call.
 */
typedef unsigned int u32;

typedef struct Obj {
    char pad[0x90];
    void *cb;           /* update/step callback at +0x90 */
} Obj;

extern Obj *gRaceConfig;    /* pointer to config; field0 = mode */
extern Obj *data_0217ae78;
extern Obj *data_0217ae88;
extern char data_02155a14[];    /* params passed to the constructor */

extern void func_0208b710(void);
extern Obj *func_0208b7bc(int size, void *params);
extern void func_020824d0(void);
extern void func_0208266c(void);
extern void func_02082034(void);

void func_02081f30(void)
{
    int mode = *(int *)gRaceConfig;

    if (mode != 0x10) {
        if (mode != 0x25)
            return;
        /* 0x25 = enter: build both helper objects */
        if (data_0217ae78 != 0) {
            func_0208b710();
            data_0217ae78 = func_0208b7bc(0x3c, data_02155a14);
            data_0217ae78->cb = (void *)func_020824d0;
        }
        if (data_0217ae88 == 0)
            return;
        func_0208b710();
        data_0217ae88 = func_0208b7bc(0x3f, data_02155a14);
        data_0217ae88->cb = (void *)func_0208266c;
        return;
    } else {
        /* 0x10 = exit: swap one callback, tear the other down */
        if (data_0217ae78 != 0)
            data_0217ae78->cb = (void *)func_02082034;
        if (data_0217ae88 == 0)
            return;
        func_0208b710();
        data_0217ae88 = 0;
    }
}
