typedef unsigned int u32;

typedef struct StructDWValue {
    u32 words[2];
} StructDWValue;

typedef struct StructDWGenerated {
    StructDWValue first;
    StructDWValue second;
    u32 trailing;
} StructDWGenerated;

typedef struct StructDWOutput {
    StructDWValue first;
    StructDWValue second;
    u32 hasFirst;
} StructDWOutput;

extern void StructDW_MaybeCreate_from_thumb(StructDWGenerated *generated);

void StructDW_SomeFn_GetSomething_from_thumb(StructDWOutput *output)
{
    // PURPOSE: Copies the generated record and reports whether its first value exists.
    StructDWGenerated generated;
    u32 zero = 0;

    StructDW_MaybeCreate_from_thumb(&generated);
    output->first = generated.first;
    output->second = generated.second;

    if ((generated.first.words[1] ^ zero) |
        (generated.first.words[0] ^ zero)) {
        output->hasFirst = 1;
    } else {
        output->hasFirst = 0;
    }
}
