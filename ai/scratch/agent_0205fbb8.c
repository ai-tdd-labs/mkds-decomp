/* PURPOSE: Checks whether a secret flag is set.
 * The argument identifies the secret flag to test.
 * A probably active non-results context checks its live save block instead.
 * Otherwise, the normal saved-secret-flag check is used.
 */
typedef struct UnkStruct_0217aa00 {
    int state;
    int mode;
} UnkStruct_0217aa00;

extern UnkStruct_0217aa00 *data_0217aa00;
extern unsigned char *data_0217aa08;

extern int CheckSavedSecretFlag_from_thumb(int secretFlag);
extern int CheckSecretFlagWith_from_thumb(int secretFlag, void *saveData);

int CheckSecretFlag(int secretFlag) {
    UnkStruct_0217aa00 *context = data_0217aa00;
    int useLiveSave = 0;

    if (((context == 0) ? 0 : context->state) != 0 && context->mode != 13) {
        useLiveSave = 1;
    }

    if (useLiveSave == 0) {
        return CheckSavedSecretFlag_from_thumb(secretFlag);
    }

    return CheckSecretFlagWith_from_thumb(secretFlag, data_0217aa08 + 0x34);
}
