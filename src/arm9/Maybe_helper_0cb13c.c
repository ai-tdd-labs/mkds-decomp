#pragma optimize_for_size on
extern int Maybe_helper_0cb194(void *a0);
extern int Maybe_check_0cb170(void *a0);

int Maybe_helper_0cb13c(void *a0) {
    int r = 0;
    if (Maybe_helper_0cb194(a0) == 0 && Maybe_check_0cb170(a0) != 0)
        r = 1;
    return r;
}
