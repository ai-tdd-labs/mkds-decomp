// PURPOSE: Updates an object's short value from a three-point curve.

typedef signed short s16;

typedef struct Curve {
    s16 low;
    s16 middle;
    s16 high;
    unsigned char low_end;
    unsigned char high_start;
} Curve;

typedef struct CurveRef {
    char pad_00[4];
    Curve *curve;
} CurveRef;

typedef struct Object {
    char pad_00[0x34];
    s16 value;
} Object;

extern int _s32_div_f(int numerator, int denominator);

void func_0201df30(Object *object, CurveRef *reference, int value)
{
    unsigned char low_end = reference->curve->low_end;
    unsigned char high_start = reference->curve->high_start;

    if (value < low_end) {
        s16 low = reference->curve->low;

        object->value = low +
            _s32_div_f(value *
                           (reference->curve->middle - low),
                       low_end);
        return;
    }

    if (value < high_start) {
        object->value = reference->curve->middle;
        return;
    }

    {
        s16 high = reference->curve->high;

        object->value = high +
        _s32_div_f((value - 0xff) *
                       (high - reference->curve->middle),
                   0xff - high_start);
    }
}
