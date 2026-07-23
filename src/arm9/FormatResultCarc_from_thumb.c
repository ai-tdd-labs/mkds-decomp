/* Builds the .carc scene path for the results screen (without language code):
 * "/data/Scene/%s%s%s" -> name + (variant depending on mode field f78)
 * + ".carc" into dst (max 0x80). */
extern void Util_SNPrintF(char *dst, unsigned int size, const char *fmt, ...);

struct S0217b488 { char pad[0x78]; int f78; };
extern struct S0217b488 *data_0217b488;

struct S021541a8 { char pad[0x50]; char *f50; };
extern struct S021541a8 data_021541a8;

extern char data_02165108[];
extern char data_0216510c[];
extern char data_02165110[]; /* "/data/Scene/%s%s%s" */
extern char data_02165124[]; /* ".carc" */

void FormatResultCarc_from_thumb(char *dst)
{
    Util_SNPrintF(dst, 0x80, data_02165110, data_021541a8.f50,
                  data_0217b488->f78 == 1 ? data_02165108 : data_0216510c,
                  data_02165124);
}
