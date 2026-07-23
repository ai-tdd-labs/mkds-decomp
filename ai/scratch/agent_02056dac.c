/* PURPOSE: Reports how many kart choices are unlocked.
 * The save-data context is checked for three extra-kart secret flags.
 * The highest available unlock level wins; one kart choice is always available.
 */
extern int CheckSecretFlagWith_from_thumb(int secretFlag, void *saveData);

int CheckExtraKartUnlockFlagsWith_from_thumb(void *saveData) {
    int kartChoiceCount = 1;

    if (CheckSecretFlagWith_from_thumb(0x13, saveData)) {
        kartChoiceCount = 4;
    } else if (CheckSecretFlagWith_from_thumb(0x12, saveData)) {
        kartChoiceCount = 3;
    } else if (CheckSecretFlagWith_from_thumb(0x11, saveData)) {
        kartChoiceCount = 2;
    }

    return kartChoiceCount;
}
