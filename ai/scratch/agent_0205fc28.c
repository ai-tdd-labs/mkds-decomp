// PURPOSE: Checks whether a secret flag is enabled for the active save data.
// The argument identifies the secret flag to test.
// During a probably active non-results scene, the check uses save data at offset 0x30.
// Otherwise, it uses the standard saved-secret-flag check.

typedef struct SecretFlagContext {
    int state;
    int mode;
} SecretFlagContext;

extern SecretFlagContext *data_0217aa00;
extern unsigned char *data_0217aa08;

extern int CheckSavedSecretFlag_from_thumb(int secretFlag);
extern int CheckSecretFlagWith_from_thumb(int secretFlag, void *saveData);

int func_0205fc28(int secretFlag) {
    int useActiveSaveData = 0;
    SecretFlagContext *context = data_0217aa00;

    /* A null or idle context falls back to the normal save-data check. */
    if ((context == 0 ? 0 : context->state) != 0 && context->mode != 13) {
        useActiveSaveData = 1;
    }

    if (useActiveSaveData == 0) {
        return CheckSavedSecretFlag_from_thumb(secretFlag);
    }

    return CheckSecretFlagWith_from_thumb(secretFlag, data_0217aa08 + 0x30);
}
