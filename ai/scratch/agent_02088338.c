/* PURPOSE: Builds the file path of a team's emblem texture (Team*_emblem.nsbtx).
 * Behaviour: picks one of two team emblem name strings (index 1 when team==0,
 * index 0 otherwise) and formats "<base>emblem/Team<name>_emblem.nsbtx" into
 * the shared 0x100-byte path buffer, then returns it. */
extern char *data_02165e4c[];   /* two team emblem name strings */
extern char *data_0217af24;     /* base path prefix */
extern char gSharedPathBuffer[];    /* shared 0x100 path buffer */
extern char data_02165eb4[];    /* "%semblem/Team%s_emblem.nsbtx" */

extern int _snprintf(char *buf, unsigned int len, const char *fmt, ...);

char *FormatTeamEmblemNsbtx(int team) {
    _snprintf(gSharedPathBuffer, 0x100, data_02165eb4, data_0217af24,
              data_02165e4c[team == 0 ? 1 : 0]);
    return gSharedPathBuffer;
}
