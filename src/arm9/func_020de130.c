/* Loads the Chain Chomp (wanwan) map object: the chain model via the
 * MapObj file lookup, and then conditionally the stake model (wanwan_kui)
 * if that file exists in the CRS/CST archive. Both allocated and
 * registered as billboard models. */
extern int data_0216bf50;   /* "wanwan_chain.nsbmd" */
extern int data_0216bf64;   /* "MapObj/wanwan_kui.nsbmd" */
extern void *data_0217b6e8;
extern void *data_0217b6e4;

extern void *FormatFindMapObjFileBuffer_from_thumb(void *name);
extern void *FindFileBuffer_CRS_CST_from_thumb(void *name);
extern void BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(void *dst, void *buf, void *a2, void *a3);
extern void BillboardModel_SomeFn(void *model);

void func_020de130(void) {
    void *buf;
    BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(&data_0217b6e8, FormatFindMapObjFileBuffer_from_thumb(&data_0216bf50), 0, 0);
    BillboardModel_SomeFn(data_0217b6e8);
    buf = FindFileBuffer_CRS_CST_from_thumb(&data_0216bf64);
    if (buf != 0) {
        BillboardModel_AllocateFromNsbmdNsbtp_from_thumb(&data_0217b6e4, buf, 0, 0);
        BillboardModel_SomeFn(data_0217b6e4);
    }
}
