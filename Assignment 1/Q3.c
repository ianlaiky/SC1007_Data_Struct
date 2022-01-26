#include <stdio.h>
#include <stdlib.h>

struct _listNode {
    int item;
    struct _listNode *next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);

void deleteList(ListNode **ptrHead);

void reverseKNodes(ListNode **head, int K);

ListNode *reverse(ListNode *head, int K);

int main() {
    ListNode *head = NULL, *temp;
    int i = 0;
    int K = 0;

    scanf("%d", &K);

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


    reverseKNodes(&head, K);
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

void reverseKNodes(ListNode **head, int K) {

    if (K == 0) {
        *head = *head;
    } else {
        *head = reverse(*head, K);
    }


}


ListNode *reverse(ListNode *head, int K) {
    if (head == NULL) {
        return NULL;
    }

    ListNode *cur = head;
    ListNode *next = NULL;
    ListNode *prev = NULL;
    ListNode *lessThanK = head;
    int tempK = K;
    int cnt = 0;

    while (lessThanK != NULL) {

        cnt++;
        lessThanK = lessThanK->next;
    }
    if (cnt < K) {
        return head;
    }

    while (cur != NULL && tempK > 0) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        tempK--;
        cnt++;
    }


    if (next != NULL) {
        head->next = reverse(next, K);
    }
    return prev;
}




