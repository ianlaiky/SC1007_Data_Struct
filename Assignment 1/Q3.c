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

void push(ListNode **head, int data);

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

    ListNode *cur = *head;
    ListNode *temp = NULL;
    int tempK = K;

    while (cur != NULL) {


        push(&temp, cur->item);
        cur = cur->next;
        tempK--;

    }
    *head = temp;

    printf("\n");
}

void push(ListNode **head, int data) {
    ListNode *new_node = (ListNode *) malloc(sizeof(ListNode));
    new_node->item = data;
    new_node->next = *head;
    *head = new_node;
}




