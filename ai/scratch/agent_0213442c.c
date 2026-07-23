/* Assert logger: formats condition/file/function/line into the
 * assert buffer and calls the assert-fail handler. (Parked: mwld
 * placement mystery, see PLAN.) */
extern char data_0216ec60[];

extern void SomeSprintf(const char *fmt, ...);
extern void OnAssertionFailed(void);

void LogThrowAssertion(const char *cond, const char *file, const char *func, int line)
{
    SomeSprintf(data_0216ec60, cond, file, func, line);
    OnAssertionFailed();
}
