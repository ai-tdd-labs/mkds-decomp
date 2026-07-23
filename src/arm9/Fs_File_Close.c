// PURPOSE: Closes a file operation and marks the file as closed.
/* The argument is a file state pointer.
 * It first asks the file system to perform close operation 8.
 * On success, it clears the pending state and updates probably internal flags.
 */

extern int Fs_File_SendOperation(void *file, int operation);

int Fs_File_Close(void *file)
{
    if (Fs_File_SendOperation(file, 8) == 0) {
        return 0;
    }

    *(int *)((char *)file + 8) = 0;
    *(int *)((char *)file + 0x10) = 0xe;
    *(int *)((char *)file + 0xc) &= ~0x30; /* Clear close-related flags. */
    return 1;
}
