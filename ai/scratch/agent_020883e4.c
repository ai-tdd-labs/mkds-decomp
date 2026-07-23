/* Builds the path to the face animations: "%s%scommon/P_faceanim.nsbtp"
 * in the shared path buffer (0x100) and returns it. */
extern char *data_02165ac4;
extern char *data_0217af24;
extern char gSharedPathBuffer[];
extern char data_02165ef0[];

extern int _snprintf(char *buf, unsigned int len, const char *fmt, ...);

char *FormatCharacterFaceAnimationNsbtpPath(void) {
    _snprintf(gSharedPathBuffer, 0x100, data_02165ef0, data_0217af24, data_02165ac4);
    return gSharedPathBuffer;
}
