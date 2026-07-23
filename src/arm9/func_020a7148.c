/*
 * PURPOSE: Sets up a race-related object once per race, or destroys itself
 * if that object already exists.
 *
 * arg0 (r0/r4): pointer to the calling object.
 * First asks a slot manager whether id 0x6a is already in use. If it is
 * (func_020d3bf8 returned nonzero), the object is redundant and destroys
 * itself via func_020d2398. Otherwise it registers itself under id 0x6a
 * and under id 0x70 (using a per-course flag byte from *gRaceConfig at
 * offset 0x3d0 as the size/param), then registers three callback function
 * pointers (func_020a72c8, func_020a7270, func_020a71c8) with three
 * separate registration helpers.
 */

extern int func_020d3bf8(int id);
extern void func_020ac588(int id, int size, void *obj);
extern void func_020a233c(void *fn);
extern void func_020a2328(void *fn);
extern void func_020a2314(void *fn);
extern void func_020d2398(void *obj);
extern void func_020a72c8(void);
extern void func_020a7270(void);
extern void func_020a71c8(void);

typedef struct RaceConfig {
    char pad[0x3d0];
    unsigned char field_0x3d0;
} RaceConfig;

extern RaceConfig *gRaceConfig;

void func_020a7148(void *self)
{
    if (func_020d3bf8(0x6a) != 0) {
        goto already_exists;
    }

    func_020ac588(0x6a, 0x14, self);
    func_020ac588(0x70, gRaceConfig->field_0x3d0, self);

    func_020a233c(func_020a72c8);
    func_020a2328(func_020a7270);
    func_020a2314(func_020a71c8);
    return;

already_exists:
    func_020d2398(self);
}
