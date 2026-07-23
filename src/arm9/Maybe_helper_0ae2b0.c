#pragma optimize_for_size on
extern int Maybe_helper_0ae308(void *a0);
extern int Maybe_check_0ae2e4(void *a0);

int Maybe_helper_0ae2b0(void *a0) {
    int r = 0;
    if (Maybe_helper_0ae308(a0) == 0 && Maybe_check_0ae2e4(a0) != 0)
        r = 1;
    return r;
}
