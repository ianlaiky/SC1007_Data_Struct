#include <stdio.h>
#include <stdlib.h>

struct _listNode {
    float item;
    struct _listNode *next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);

void deleteList(ListNode **ptrHead);

ListNode *reverse(ListNode *head);

ListNode *reverseSegment(ListNode *head, int start, int end);

int main() {
    ListNode *head = NULL, *temp;
    float f = 0.0;
    int S, E;

    scanf("%d %d", &S, &E);

    while (scanf("%f", &f)) {
        if (head == NULL) {
            head = (ListNode *) malloc(sizeof(ListNode));
            temp = head;
        } else {
            temp->next = (ListNode *) malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = f;
    }
    temp->next = NULL;

    head = reverseSegment(head, S, E);
    printList(head);
    deleteList(&head);
    return 0;

}

void printList(ListNode *head) {
    while (head != NULL) {
        printf("%.2f ", head->item);
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

ListNode *reverseSegment(ListNode *head, int start, int end) {

    ListNode *tempbefore = NULL;
    ListNode *tempbeforehead = NULL;
    ListNode *tempafterhead = NULL;
    ListNode *tempafter = NULL;
    ListNode *temphead = NULL;
    ListNode *temp = NULL;
    ListNode *cur = head;
    int index = 0;
    if (start == 0 && end == 0) {
        return head;
    }
    while (cur != NULL) {
        if (index >= start && index <= end) {
            if (temp == NULL) {
                ListNode *single = malloc(sizeof(ListNode));
                single->item = cur->item;
                single->next = NULL;
                temp = single;
                temphead = temp;
            } else {
                ListNode *single = malloc(sizeof(ListNode));
                single->item = cur->item;
                single->next = NULL;
                temp->next = single;
                temp = temp->next;
            }
        } else if (index < start) {
            if (tempbefore == NULL) {
                ListNode *single = malloc(sizeof(ListNode));
                single->item = cur->item;
                single->next = NULL;
                tempbefore = single;
                tempbeforehead = tempbefore;
            } else {
                ListNode *single = malloc(sizeof(ListNode));
                single->item = cur->item;
                single->next = NULL;
                tempbefore->next = single;
                tempbefore = tempbefore->next;

            }

        } else {
            if (tempafter == NULL) {
                tempafter = cur;
                tempafterhead = tempafter;
            } else {
                tempafter->next = cur;
                tempafter = tempafter->next;
            }

        }
        index++;
        cur = cur->next;
    }
    if (index < end) {
        return head;
    }

    ListNode *reversed = reverse(temphead);
    if (tempbefore != NULL) {
        tempbefore->next = reversed;
        while (tempbefore->next != NULL) {

            tempbefore = tempbefore->next;
        }
        tempbefore->next = tempafterhead;
    } else {
        tempbeforehead = reversed;
        while (reversed->next != NULL) {

            reversed = reversed->next;
        }
        reversed->next = tempafterhead;
    }


    return tempbeforehead;
}

ListNode *reverse(ListNode *head) {
    ListNode *cur = head, *prev = NULL, *next;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}




