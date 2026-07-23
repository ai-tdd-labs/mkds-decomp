// PURPOSE: Moves a node from one linked list to the front of another list.
// The first two arguments are list heads and the third is the node to move.
// The operation is protected while interrupts are disabled.

typedef struct ListNode ListNode;

struct ListNode {
    ListNode *next;
};

extern unsigned int Os_DisableIrq(void);
extern void Os_RestoreIrq(unsigned int state);

void func_0204d110(ListNode **source, ListNode **destination, ListNode *node)
{
    // PURPOSE: Moves a node between linked lists with interrupts disabled.
    unsigned int irqState;
    ListNode *current;

    irqState = Os_DisableIrq();
    current = *source;
    if (current == node) {
        *source = node->next;
        node->next = *destination;
        *destination = node;
    } else if (current != 0) {
        do {
            if (current->next == node) {
                current->next = node->next;
                node->next = *destination;
                *destination = node;
                break;
            }
            current = current->next;
        } while (current != 0);
    }
    Os_RestoreIrq(irqState);
}
