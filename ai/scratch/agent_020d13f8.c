// PURPOSE: Advances the ending credits frame counter.
// The shared credits object probably stores its current frame at offset zero.
// When the frame reaches 780, the staff-roll action is triggered.
// It returns the current display scanline counter.

typedef struct {
    int frame_count;
} EndingStaffRollObjectData;

extern EndingStaffRollObjectData *data_0217b4ac;
extern void RunWhenStaffRollCount(void);

unsigned short IncrementStaffRollFrameCount(void)
{
    if (data_0217b4ac->frame_count < 0x7fffffff)
        data_0217b4ac->frame_count++;

    if (data_0217b4ac->frame_count == 0x30c)
        RunWhenStaffRollCount();

    return *(volatile unsigned short *)0x04000304;
}
