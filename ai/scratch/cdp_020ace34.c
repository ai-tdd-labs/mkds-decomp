#pragma optimize_for_size on
extern int Maybe_helper_0ace8c(void *a0);
extern int Maybe_check_0ace68(void *a0);

int Maybe_helper_0ace34(void *a0) {
    int r = 0;
    if (Maybe_helper_0ace8c(a0) == 0 && Maybe_check_0ace68(a0) != 0)
        r = 1;
    return r;
}
