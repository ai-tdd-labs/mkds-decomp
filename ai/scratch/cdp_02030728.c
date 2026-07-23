#pragma optimize_for_size on
extern int Maybe_helper_030780(void *a0);
extern int Maybe_check_03075c(void *a0);

int Maybe_helper_030728(void *a0) {
    int r = 0;
    if (Maybe_helper_030780(a0) == 0 && Maybe_check_03075c(a0) != 0)
        r = 1;
    return r;
}
