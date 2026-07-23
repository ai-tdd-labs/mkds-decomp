// PURPOSE: Selects a course outside the current cup.
// It advances the shared random generator to choose a starting position.
// It then scans cyclically until it finds a course absent from the cup.

#pragma optimize_for_size on

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long long u64;

typedef struct RandomGenerator {
    u64 state;
    u64 multiplier;
    u64 increment;
} RandomGenerator;

typedef struct RandomSystem {
    u8 padding_000[0x94];
    RandomGenerator random;
} RandomSystem;

typedef struct CupProgressState {
    u8 padding_000[0x5c];
    int courses[4];
} CupProgressState;

extern RandomSystem *data_02174e28;
extern CupProgressState *data_0217b488;
extern int data_02153a4c[];
extern u64 Multiply64(u64 left, u64 right);

int func_0202af60(void)
{
    RandomSystem *system;
    RandomGenerator *random;
    CupProgressState *cup;
    int course;
    int i;
    int available;

    system = data_02174e28;
    random = &system->random;
    system->random.state =
        Multiply64(random->multiplier, system->random.state) +
        random->increment;
    course = (u16)(random->state >> 52) % 20;
    cup = data_0217b488;

    do {
        available = 1;
        course = (course + 1) % 20;
        for (i = 0; i < 4; i++) {
            if (cup->courses[i] == data_02153a4c[course]) {
                available = 0;
                break;
            }
        }
    } while (available == 0);

    return course;
}
