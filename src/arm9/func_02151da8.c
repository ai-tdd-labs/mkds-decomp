/* PURPOSE: Checks whether the generated data is empty.
 * The helper probably writes two double-word values into a local record.
 * Returns one only when both values are zero.
 */
typedef unsigned int u32;

typedef struct {
    unsigned long long first;
    unsigned long long second;
    u32 trailing;
} StructDWGenerated;

extern void StructDW_MaybeCreate_from_thumb(StructDWGenerated *generated);

int func_02151da8(void)
{
    // PURPOSE: Checks whether the generated data is empty.
    StructDWGenerated generated;

    StructDW_MaybeCreate_from_thumb(&generated);
    if (generated.second == 0 && generated.first == 0) {
        return 1;
    }
    return 0;
}
