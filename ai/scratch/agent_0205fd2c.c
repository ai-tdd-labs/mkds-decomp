// PURPOSE: Returns whether the selected kart entry is unlocked.
extern unsigned int CheckExtraKartUnlockFlags_from_thumb(void);

int func_0205fd2c(unsigned char **table, int offset, int index)
{
    unsigned int required;
    unsigned int unlocked;

    unlocked = CheckExtraKartUnlockFlags_from_thumb();
    required = (*table)[index * 13 + offset + 6];
    if (required != 0 && required <= unlocked) {
        return 1;
    }
    return 0;
}
