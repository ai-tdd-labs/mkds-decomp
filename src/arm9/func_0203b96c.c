// PURPOSE: Checks whether a selected group has an unlocked secret flag.

extern int CheckSavedSecretFlag_from_thumb(int secretFlag);

int func_0203b96c(int group)
{
    if (group == 9) {
        return 0;
    }
    switch (group) {
    case 0:
    case 1:
    case 4:
    case 5:
        return 1;

    case 2:
        if (CheckSavedSecretFlag_from_thumb(0) ||
            CheckSavedSecretFlag_from_thumb(1) ||
            CheckSavedSecretFlag_from_thumb(2) ||
            CheckSavedSecretFlag_from_thumb(3)) {
            return 1;
        }
        goto not_found;

    case 3:
        if (CheckSavedSecretFlag_from_thumb(4) ||
            CheckSavedSecretFlag_from_thumb(5) ||
            CheckSavedSecretFlag_from_thumb(6) ||
            CheckSavedSecretFlag_from_thumb(7)) {
            return 1;
        }
        goto not_found;

    case 6:
        if (CheckSavedSecretFlag_from_thumb(8) ||
            CheckSavedSecretFlag_from_thumb(9) ||
            CheckSavedSecretFlag_from_thumb(10) ||
            CheckSavedSecretFlag_from_thumb(11)) {
            return 1;
        }
        goto not_found;

    case 7:
        if (CheckSavedSecretFlag_from_thumb(12) ||
            CheckSavedSecretFlag_from_thumb(13) ||
            CheckSavedSecretFlag_from_thumb(14) ||
            CheckSavedSecretFlag_from_thumb(15)) {
            return 1;
        }
        goto not_found;
    }

not_found:
    return 0;
}
