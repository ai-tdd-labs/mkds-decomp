typedef struct FSFile {
    int field_00;  /* 0x00 */
    int field_04;  /* 0x04 */
    int field_08;  /* 0x08 */
    int field_0c;  /* 0x0c */
    int field_10;  /* 0x10 */
    int pad_14;    /* 0x14 */
    int field_18;  /* 0x18 */
    int field_1c;  /* 0x1c */
} FSFile;
void Fs_File_Initialize(FSFile *f) {
    f->field_00 = 0;
    f->field_04 = f->field_00;
    f->field_1c = 0;
    f->field_18 = f->field_1c;
    f->field_08 = 0;
    f->field_10 = 0xe;
    f->field_0c = 0;
}
