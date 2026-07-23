// PURPOSE: Checks whether the current race settings allow this selection.
// The global state provides the selection type and active race options.
// It returns zero for blocked combinations and one when selection is allowed.

typedef struct SelectionState {
    unsigned char padding_00[0x2c];
    int selectionType_2c;
    unsigned char padding_30[0x30];
    int mode_60;
    int field_64;
    int submode_68;
    int option_6c;
    int field_70;
    int option_74;
    int option_78;
} SelectionState;

extern SelectionState *data_0217d368;
extern int CheckSecretFlag(int secretFlag);

int func_0211cea8(void)
{
    if (data_0217d368->mode_60 == 0 &&
        data_0217d368->submode_68 == 3 &&
        CheckSecretFlag(0x10) == 0) {
        return 0;
    }

    switch (data_0217d368->selectionType_2c) {
    case 0:
        if (data_0217d368->mode_60 == 1 &&
            data_0217d368->option_6c == 0) {
            return 0;
        }
        if (data_0217d368->mode_60 == 4 &&
            data_0217d368->option_78 == 2) {
            return 0;
        }
        break;

    case 1:
        if (data_0217d368->mode_60 == 1 &&
            data_0217d368->option_6c == 0) {
            return 0;
        }
        if (data_0217d368->mode_60 == 3 &&
            data_0217d368->option_74 == 1) {
            return 0;
        }
        if (data_0217d368->mode_60 == 4 &&
            data_0217d368->option_78 == 2) {
            return 0;
        }
        break;

    case 2:
        if (data_0217d368->mode_60 == 4 &&
            data_0217d368->option_78 == 1) {
            return 0;
        }
        break;

    case 3:
        if (data_0217d368->mode_60 == 3 &&
            data_0217d368->option_74 == 1) {
            return 0;
        }
        if (data_0217d368->mode_60 == 4 &&
            data_0217d368->option_78 == 1) {
            return 0;
        }
        break;

    case 4:
        if (data_0217d368->mode_60 == 4 &&
            data_0217d368->option_78 == 1) {
            return 0;
        }
        break;

    case 5:
        if (data_0217d368->mode_60 == 3 &&
            data_0217d368->option_74 == 1) {
            return 0;
        }
        if (data_0217d368->mode_60 == 4 &&
            data_0217d368->option_78 == 1) {
            return 0;
        }
        break;
    }

    return 1;
}
