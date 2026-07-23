/* PURPOSE: Shuts down the current menu state and releases its heap.
 * The function probably restores display settings when the state is active.
 * It chooses the normal or download-play cleanup path from shared boot state,
 * destroys the owned heap, and clears the shared state pointer.
 */

typedef struct MenuShutdownState {
    unsigned char padding_00[0x30];
    void *heap;
    unsigned char padding_34[0x0c];
    int displayReady;
    unsigned char padding_44[0x28];
    int active;
} MenuShutdownState;

extern MenuShutdownState *data_0217d364;

extern int func_0211e130(void);
extern void func_0211de34(void);
extern void func_0211df38(void);
extern void func_0211f498(void);
extern void Mem_DestroyHeap(void *heap);

void func_021196f4(void)
{
    if (data_0217d364->active == 1) {
        if (data_0217d364->displayReady == 0) {
            if (func_0211e130() != 0) {
                *(volatile unsigned int *)0x04000000 =
                    (*(volatile unsigned int *)0x04000000 & 0xffffe0ff) |
                    0x1800;
            }
        } else {
            /* Keep this write separate to preserve the original branch shape. */
            *(volatile unsigned int *)0x04000000 =
                (*(volatile unsigned int *)0x04000000 & 0xffffe0ff) | 0x1800;
        }
    }

    if (*(volatile unsigned short *)0x027ffc40 != 2) {
        func_0211de34();
        func_0211df38();
    } else {
        func_0211f498();
    }

    Mem_DestroyHeap(data_0217d364->heap);
    data_0217d364 = 0;
}
