typedef struct {
    unsigned char pad_000[0x120];
    unsigned int countdown;
} Object0212EF00;

extern void func_0212c9a4(Object0212EF00 *object);

void func_0212ef00(Object0212EF00 *object)
{
    if (object->countdown == 0) {
        return;
    }

    object->countdown--;
    if (object->countdown == 0) {
        func_0212c9a4(object);
    }
}
