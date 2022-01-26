#include <stdio.h>
#include <stdlib.h>

struct _listNode {
    int item;
    struct _listNode *next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);

void deleteList(ListNode **ptrHead);

void triPartition(ListNode **head, int pivot);

int main() {
    ListNode *head = NULL, *temp;
    int i = 0;
    int pivot = 0;

    scanf("%d", &pivot);

    while (scanf("%d", &i)) {
        if (head == NULL) {
            head = (ListNode *) malloc(sizeof(ListNode));
            temp = head;
        } else {
            temp->next = (ListNode *) malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = i;
    }
    temp->next = NULL;


    triPartition(&head, pivot);
    printList(head);
    deleteList(&head);

    return 0;
}

void printList(ListNode *head) {
    while (head != NULL) {
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead) {
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur != NULL) {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
    *ptrHead = NULL;
}

void triPartition(ListNode **head, int pivot) {

    ListNode *cur = *head;
    ListNode *prev = NULL;
    ListNode *temp;
    ListNode *smallerThanPivotHead = NULL;
    ListNode *smallerThanPivotTail = NULL;
    ListNode *largerThanPivotHead = NULL;
    ListNode *largerThanPivotTail = NULL;
    ListNode *equalToPivotHead = NULL;
    ListNode *equalToPivotTail = NULL;


    while (cur != NULL) {

        temp = cur->next;
        cur->next = NULL;

        if (cur->item < pivot) {
            if (smallerThanPivotHead == NULL) {
                smallerThanPivotHead = cur;
                smallerThanPivotTail = cur;
            } else {
                smallerThanPivotTail->next = cur;
                smallerThanPivotTail = cur;
            }
        } else if (cur->item > pivot) {
            if (largerThanPivotHead == NULL) {
                largerThanPivotHead = cur;
                largerThanPivotTail = cur;
            } else {
                largerThanPivotTail->next = cur;
                largerThanPivotTail = cur;
            }

        } else {
            if (equalToPivotHead == NULL) {
                equalToPivotHead = cur;
                equalToPivotTail = cur;
            } else {
                equalToPivotTail->next = cur;
                equalToPivotTail = cur;
            }
        }
        cur = temp;

    }


    if (smallerThanPivotTail != NULL) {
        smallerThanPivotTail->next = equalToPivotHead;
    } else {
        smallerThanPivotHead = equalToPivotHead;
    }

    if (equalToPivotTail != NULL) {
        equalToPivotTail->next = largerThanPivotHead;
    } else {
        smallerThanPivotTail->next = largerThanPivotHead;
    }

    if (largerThanPivotTail != NULL) {
        largerThanPivotTail->next = NULL;
    }

    *head = smallerThanPivotHead;


}







// Write your code here
