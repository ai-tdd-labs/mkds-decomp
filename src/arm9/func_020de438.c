/* Loads the two warp pipe models (earthen_pipe1/2.nsbmd) as
 * billboard models and registers them. */
extern int data_0216bf7c;   /* "earthen_pipe1.nsbmd" */
extern int data_0216bf90;   /* "earthen_pipe2.nsbmd" */
extern void *data_0217b6f0;
extern void *data_0217b6f4;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(void *dst, void *buf, void *a2, void *a3);
extern void BillboardModel_SomeFn(void *model);

void func_020de438(void) {
    BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(&data_0217b6f0, FormatFindMapObjFileBuffer_from_thumb(&data_0216bf7c), 0, 0);
    BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(&data_0217b6f4, FormatFindMapObjFileBuffer_from_thumb(&data_0216bf90), 0, 0);
    BillboardModel_SomeFn(data_0217b6f0);
    BillboardModel_SomeFn(data_0217b6f4);
}
