#pragma optimize_for_size on
extern int Maybe_helper_0b2aec(void *a0);
extern int Maybe_check_0b2ac8(void *a0);

int Maybe_helper_0b2a94(void *a0) {
    int r = 0;
    if (Maybe_helper_0b2aec(a0) == 0 && Maybe_check_0b2ac8(a0) != 0)
        r = 1;
    return r;
}
