// PURPOSE: Queues the selected cup picture files for loading.
// The argument selects a cup entry in the picture table.
// It probably avoids reloading work that is already selected.
// The three queued tasks load the palette, graphics, and related picture data.

typedef struct CupPictureWork {
    int unk_00;
    char char_gfx[8];
    int cup_index;
} CupPictureWork;

typedef struct CupPictureTableEntry {
    int value;
    int padding;
} CupPictureTableEntry;

extern CupPictureTableEntry data_0216aeac[];
extern CupPictureWork *gCupSelectWork;

extern int func_020d0ec4(void);
extern void WorkerInsertTask(void (*task)(void));
extern void WorkerNotifyTaskPending(void);
extern void Maybe_m_b_2(void);
extern void Maybe_m_b(void);
extern void Maybe_m_picture(void);

int func_020d0efc(int cupIndex)
{
    int result = 1;

    if (data_0216aeac[cupIndex].value == 0) {
        result = 0;
    } else {
        if (func_020d0ec4() != 0) {
            if (gCupSelectWork->cup_index != cupIndex) {
                gCupSelectWork->cup_index = cupIndex;
                WorkerInsertTask(Maybe_m_b_2);
                WorkerInsertTask(Maybe_m_b);
                WorkerInsertTask(Maybe_m_picture);
                WorkerNotifyTaskPending();
            }
        } else {
            result = 0;
        }
    }

    return result;
}
