/* PURPOSE: Builds the ghost replay file path for a ghost number.
 * Arguments: ghost number, output buffer, and output-buffer length.
 * It probably prepares the filename for loading or saving a ghost replay.
 */
extern char data_02164770[];
extern int Util_SNPrintF(char *buf, unsigned int len, const char *fmt, ...);

int FormatGhostBinPath(int ghostId, char *buf, unsigned int len) {
    Util_SNPrintF(buf, len, data_02164770, ghostId);
    return 1;
}
