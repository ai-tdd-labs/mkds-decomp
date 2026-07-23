/* PURPOSE: Writes a request record into an output buffer.
 * The request type selects one of several packed output formats.
 * Types 4 and 6 scan up to 16 active subrecords and stop on the first error.
 * Some field meanings are uncertain, but their widths and offsets follow the ROM.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef union RequestPayload {
    u32 value;
    u8 bytes[0x1e4];
} RequestPayload;

typedef struct RequestRecord {
    u32 type;
    u8 pad_004[4];
    u16 activeMask;
    u8 pad_00a[2];
    u8 channel;
    u8 pad_00d[7];
    RequestPayload payload;
} RequestRecord;

extern int func_020070d8(void);
extern int func_020070e4(void);
extern int func_02006858(void *output, u16 activeMask, u8 channel,
                         int firstValue, int secondValue);
extern int func_020062f4(void *subrecord);
extern int func_020065f8(void *output, u16 activeBit, u8 channel,
                         u32 payloadValue);
extern int func_02006794(void *output, u16 activeMask, u8 channel,
                         u32 payloadValue, int slotIndex);
extern int func_020066c0(void *output, u16 activeMask, u8 channel,
                         u32 payloadValue, int slotIndex);
extern int func_0200654c(void *output, u16 activeMask, u8 channel,
                         void *payload, int trailingByte);

int func_02005a30(RequestRecord *request, void *output)
{
    int result = 0;

    switch (request->type) {
    case 2: {
        int firstValue = func_020070d8();
        int secondValue = func_020070e4();

        return func_02006858(output, request->activeMask, request->channel,
                             firstValue, secondValue);
    }

    case 4:
    case 6: {
        int subrecordIndex = 0;
        u8 *subrecord = (u8 *)request + 0x1f8;

        for (; subrecordIndex < 16; subrecordIndex++, subrecord += 0x68) {
            u32 activeBit = 1;
            activeBit <<= subrecordIndex;

            if ((request->activeMask & (u16)activeBit) != 0) {
                int slotIndex = func_020062f4(subrecord);

                /* Continuing iterations prove that result is still zero. */
                if (slotIndex == ~result) {
                    result = func_020065f8(output, (u16)activeBit,
                                           request->channel,
                                           request->payload.value);
                } else if (request->type == 4) {
                    result = func_02006794(output, request->activeMask,
                                           request->channel,
                                           request->payload.value, slotIndex);
                } else {
                    result = func_020066c0(output, request->activeMask,
                                           request->channel,
                                           request->payload.value, slotIndex);
                }

                if (result != 0) {
                    return result;
                }
            }
        }

        return result;
    }

    case 10:
        result = func_0200654c(output, request->activeMask, request->channel,
                               request->payload.bytes,
                               request->payload.bytes[9]);
        break;
    }

    return result;
}
