// PURPOSE: Checks whether the current player's course vector is in bounds.
// It returns allowed by default for most courses.
// On the two special courses, it probably checks the player's current position.

typedef signed int s32;
typedef unsigned char u8;

typedef struct VecFx32 {
    s32 x;
    s32 y;
    s32 z;
} VecFx32;

extern int GetCurrentInternalCourseId_0(void);
extern int GetCurrentPlayerRacerId(void);
extern void GetDriverVec354(VecFx32 *vector, u8 racerId);
extern int CheckVectorBounds_Clock_Airship(VecFx32 *vector);

int CheckCourseSomeVectorBounds(void)
{
    int result = 1;
    int course;

    course = GetCurrentInternalCourseId_0();
    if (course != 0x11) {
        if (course != 0x13) {
            goto done;
        }
    }

    {
        VecFx32 vector;

        GetDriverVec354(&vector, (u8)GetCurrentPlayerRacerId());
        result = CheckVectorBounds_Clock_Airship(&vector);
    }

done:
    return result;
}
