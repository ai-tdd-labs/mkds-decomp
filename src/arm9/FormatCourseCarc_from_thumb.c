/* PURPOSE: Builds the archive path for a course.
 * Writes a course archive path into output, using the selected course entry.
 * The third argument selects the texture archive suffix.
 * A shared mode and per-course flag probably select an additional suffix.
 */

typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    char *name;
    u8 padding[4];
} CourseNameEntry;

typedef struct {
    u8 usesModeSuffix;
    u8 padding[7];
} CourseLanguageEntry;

extern char *Util_SNPrintF(char *output, int outputSize, const char *format, ...);
extern CourseNameEntry data_02154228[];
extern CourseLanguageEntry data_0215422c[];
extern char data_02165164[];
extern char data_02165168[];
extern char data_0216516c[];
extern char data_02165170[];
extern char data_02165174[];

char *FormatCourseCarc_from_thumb(char *output, int courseId, int loadTextureCarc)
{
    int useModeSuffix = 0;
    const char *archiveSuffix;
    const char *modeSuffix;

    if (*(volatile u16 *)0x027ffc40 == 2 &&
        data_0215422c[courseId].usesModeSuffix == 1) {
        useModeSuffix = 1;
    }

    if (loadTextureCarc != 0) {
        archiveSuffix = data_02165164;
    } else {
        archiveSuffix = data_02165168;
    }

    if (useModeSuffix != 0) {
        modeSuffix = data_0216516c;
    } else {
        modeSuffix = data_02165170;
    }

    return Util_SNPrintF(output, 0x80, data_02165174,
                         data_02154228[courseId].name,
                         modeSuffix, archiveSuffix);
}
