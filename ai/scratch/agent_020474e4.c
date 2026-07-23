/* PURPOSE: Configures four standard mount entries for the full game.
 *
 * This function has no arguments and returns no value. It reads the mount
 * table through the global object's field at offset 0xa0, then assigns four
 * slot/value pairs with both option bits disabled.
 */

extern void *data_0217aa10;

extern void SetMountData_from_thumb(void *mountTable, int slot, int value,
                                    int option29, int option30);

void func_020474e4(void)
{
    SetMountData_from_thumb(*(void **)((char *)data_0217aa10 + 0xa0),
                            0xb, 0xaa, 0, 0);
    SetMountData_from_thumb(*(void **)((char *)data_0217aa10 + 0xa0),
                            0xc, 0x6e, 0, 0);
    SetMountData_from_thumb(*(void **)((char *)data_0217aa10 + 0xa0),
                            9, 0x1e, 0, 0);
    SetMountData_from_thumb(*(void **)((char *)data_0217aa10 + 0xa0),
                            0xa, 0x1e, 0, 0);
}
