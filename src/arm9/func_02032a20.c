// PURPOSE: Updates the global menu state and starts its sound.

typedef struct GlobalCA {
    unsigned char pad0[0xc8];
    int fC8;
    unsigned char pad1[0x18];
    int fE4;
} GlobalCA;

typedef struct MenuWork {
    unsigned char pad0[0x44];
    int f44;
    unsigned char pad1[0xc];
    int f54;
    unsigned char pad2[0xc];
    int f64;
    int f68;
} MenuWork;

extern MenuWork *data_02174e5c;
extern unsigned char data_0217d068[];
extern GlobalCA *GetGlobalCA_from_thumb(void);
extern void NNSi_MaybeSndPlayerStartSeq(void *player, int playerNo, int sequenceId);

#pragma optimize_for_size on

void func_02032a20(void)
{
    int flag;

    if (data_02174e5c->f68 == 0) {
        GetGlobalCA_from_thumb()->fC8 = 2;
        switch (data_02174e5c->f44) {
        case 0:
            flag = 0;
            break;
        default:
            flag = 1;
            break;
        }
        GetGlobalCA_from_thumb()->fE4 = flag;
    } else {
        if (data_02174e5c->f44 == 0) {
            GetGlobalCA_from_thumb()->fC8 = 3;
        } else {
            GetGlobalCA_from_thumb()->fC8 = 2;
            switch (data_02174e5c->f44) {
            case 1:
                flag = 0;
                break;
            default:
                flag = 1;
                break;
            }
            GetGlobalCA_from_thumb()->fE4 = flag;
        }
    }

    data_02174e5c->f64 = 1;
    data_02174e5c->f54 = 5;
    NNSi_MaybeSndPlayerStartSeq(data_0217d068, 0, 5);
}
