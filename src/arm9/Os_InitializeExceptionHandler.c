// PURPOSE: Sets up the system exception handler.
// Reads the saved exception location and keeps it only when it is in main RAM.
// If system flags permit it, the handler is probably installed in both exception vectors.
// Clears the initialization state when setup is complete.

extern int data_021701c4;
extern int data_021701bc;

extern int Os_GetSystemFlags(void);
extern void Os_ExceptionHandler(void);

void Os_InitializeExceptionHandler(void)
{
    unsigned int exceptionLocation;

    exceptionLocation = *(volatile unsigned int *)0x027ffd9c;
    if (exceptionLocation < 0x02600000) {
        goto clearLocation;
    }
    if (exceptionLocation >= 0x02800000) {
        goto clearLocation;
    }
    data_021701c4 = exceptionLocation;
    goto locationChecked;

clearLocation:
    data_021701c4 = 0;

locationChecked:

    if ((data_021701c4 == 0) || ((Os_GetSystemFlags() & 0x40000000) == 0)) {
        volatile unsigned int *vectorBase;

        vectorBase = (volatile unsigned int *)0x027e3000;
        *(volatile unsigned int *)0x027ffd9c =
            (unsigned int)(void *)Os_ExceptionHandler;
        vectorBase[0x3f7] = (unsigned int)(void *)Os_ExceptionHandler;
    }

    data_021701bc = 0;
}
