// PURPOSE: Completes a queued file operation and publishes its result to each owner.
// The first argument holds owner result slots and the operation queues.
// The second argument is the completed operation and its owner bit mask.
// Small results are probably registered directly from the operation buffer.

#pragma optimize_for_size on

typedef unsigned short u16;
typedef unsigned int u32;

typedef struct ListNode ListNode;

struct ListNode {
    ListNode *next;
};

typedef struct StructGO {
    void *value0;
    void *value4;
    unsigned char payload[0x20];
    struct StructGO *next;
    void *value2C;
    u16 value30;
    u16 isDefault;
} StructGO;

typedef struct PendingOperation {
    ListNode node;
    StructGO object;
    unsigned char padding_38[0x24];
    u32 start_5c;
    u32 end_60;
    unsigned char padding_64[0x1c];
    int state_80;
    int ownerCount_84;
    int ownerMask_88;
    void *result_8c;
    unsigned char padding_90[0x30];
    unsigned char smallResult_c0;
} PendingOperation;

typedef struct OwnerEntry {
    unsigned char padding_00[4];
    void *result_04;
    unsigned char padding_08[4];
} OwnerEntry;

typedef struct OperationOwner {
    unsigned char padding_0000[0x46c4];
    ListNode *completed_46c4;
    ListNode *active_46c8;
    int ownerMask_46cc;
} OperationOwner;

typedef struct ExtraFileOperationState {
    unsigned char padding_00[0x0c];
    int state_0c;
} ExtraFileOperationState;

extern ExtraFileOperationState data_02175ec0;
extern unsigned char data_0215470c[];

extern u32 Os_DisableIrq(void);
extern void Os_RestoreIrq(u32 state);
extern int StructGO_SomeFn_from_thumb(StructGO *object, void *value0,
                                      const void *payload, void *value2C,
                                      void *value4, u16 value30);
extern void func_0204d110(ListNode **source, ListNode **destination,
                          ListNode *node);

void func_0204d18c(OperationOwner *owner, PendingOperation *operation)
{
    u32 irqState;
    int ownerMask;
    int ownerIndex;
    OwnerEntry *ownerEntry;

    irqState = Os_DisableIrq();
    if (data_02175ec0.state_0c != 0) {
        ownerMask = operation->ownerMask_88;
        operation->ownerMask_88 = 0;
        owner->ownerMask_46cc |= ownerMask;

        if (operation->ownerCount_84 <= 0) {
            u32 resultSize = operation->end_60 - operation->start_5c;

            StructGO_SomeFn_from_thumb(
                &operation->object, operation->result_8c, data_0215470c,
                resultSize <= 0x400 ? &operation->smallResult_c0 : 0,
                (void *)resultSize, 0);
            func_0204d110(&owner->active_46c8, &owner->completed_46c4,
                          &operation->node);
            operation->state_80 = 2;
        }

        ownerEntry = (OwnerEntry *)owner;
        for (ownerIndex = 0; (1 << ownerIndex) <= ownerMask;
             ownerIndex++, ownerEntry++) {
            if (((1 << ownerIndex) & ownerMask) != 0) {
                operation->ownerCount_84++;
                ownerEntry->result_04 = operation->result_8c;
            }
        }
    }
    Os_RestoreIrq(irqState);
}
