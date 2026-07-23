// PURPOSE: Loads the course collision file so the game knows where walls and floors are.
// Looks up the "course_collision.kcl" file buffer inside the loaded course
// archive, then copies/parses its KCL header into the global collision work
// area at data_0217b614. No arguments, no return value.

extern char data_0216b914[]; // "course_collision.kcl"
extern char data_0217b614[]; // global KCL work area

extern void *FindFileBuffer_CRS_CST_from_thumb(char *name);
extern void CopyKclHeaderAbsolute_from_thumb(void *dst, void *src);

void LoadCourseKcl_from_thumb(void) {
    // nested call: inner result flows straight into r1 (adds r1,r0,#0)
    CopyKclHeaderAbsolute_from_thumb(data_0217b614, FindFileBuffer_CRS_CST_from_thumb(data_0216b914));
}
