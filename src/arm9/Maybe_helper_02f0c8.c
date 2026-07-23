#pragma optimize_for_size on
extern int Maybe_helper_02f028(void *a0);
extern int Maybe_check_02f0fc(void *a0);

int Maybe_helper_02f0c8(void *a0) {
    int r = 0;
    if (Maybe_helper_02f028(a0) == 0 && Maybe_check_02f0fc(a0) != 0)
        r = 1;
    return r;
}
