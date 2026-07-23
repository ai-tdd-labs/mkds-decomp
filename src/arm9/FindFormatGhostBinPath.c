/* Looks up the course id for an internal id and then formats the ghost
 * file path "/data/ghost/ghost_%03d.bin" into buf. Returns 0 if the
 * course id does not exist (-1), otherwise 1. */
extern char data_02164754[];

extern int GetCourseIdFromInternalId(int internalId);
extern int Util_SNPrintF(char *buf, unsigned int len, const char *fmt, ...);

int FindFormatGhostBinPath(int internalId, char *buf, unsigned int len) {
    int courseId = GetCourseIdFromInternalId(internalId);
    if (courseId == -1) {
        return 0;
    }
    Util_SNPrintF(buf, len, data_02164754, (unsigned char)courseId);
    return 1;
}
