// PURPOSE: Copies the console owner's saved personal details.

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef struct OsPersonalData {
    u8 language;
    u8 color;
    u8 birth_month;
    u8 birth_day;
    u8 name[0x14];
    u16 name_length;
    u8 message[0x34];
    u16 message_length;
} OsPersonalData;

extern void CopyMemory16(const void *src, void *dest, u32 size);

void Os_GetPersonalData(OsPersonalData *personal_data)
{
    volatile u8 *personal = (volatile u8 *)0x027ffc80;

    personal_data->language = (u32)(*(volatile u16 *)(personal + 0x64) << 0x1d) >> 0x1d;
    personal_data->color = (u32)(personal[2] << 0x1c) >> 0x1c;
    personal_data->birth_month = personal[3];
    personal_data->birth_day = personal[4];
    personal_data->name_length = personal[0x1a];
    personal_data->message_length = personal[0x50];
    CopyMemory16((const void *)(personal + 6), personal_data->name, 0x14);
    CopyMemory16((const void *)(personal + 0x1c), personal_data->message, 0x34);
}
