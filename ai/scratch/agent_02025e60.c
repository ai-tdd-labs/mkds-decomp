// PURPOSE: Returns a table value for the current game mode.
// The input selects an entry in one of two mode-dependent tables.
// Mode four and unsupported modes probably have no value.

typedef struct GlobalCA {
    char _00[0xc8];
    unsigned int mode;
} GlobalCA;

extern GlobalCA *GetGlobalCA_from_thumb(void);
extern int data_02153274[];
extern int data_02153240[];

int func_02025e60(int index)
{
    int result = -1;

    switch (GetGlobalCA_from_thumb()->mode) {
    case 0:
    case 1:
    case 3:
    case 5:
        result = data_02153274[index];
        break;
    case 2:
        result = data_02153240[index];
        break;
    }
    return result;
}
