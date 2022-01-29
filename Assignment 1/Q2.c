#include <stdio.h>
#include <stdlib.h>

struct _listNode {
    int item;
    struct _listNode *next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList {
    ListNode *head;
    int size;
} LinkedList;

void printList(LinkedList ll);

void deleteList(LinkedList *llptr);

LinkedList split_and_rearrange(LinkedList ll, int arrange_type);

LinkedList rearrange(LinkedList ll);

int main() {
    LinkedList ll;

    ll.head = NULL;
    ll.size = 0;
    ListNode *temp;

    int i = 0;

    while (scanf("%d", &i)) {
        if (ll.head == NULL) {
            ll.head = (ListNode *) malloc(sizeof(ListNode));
            temp = ll.head;
        } else {
            temp->next = (ListNode *) malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = i;
        ll.size++;
    }
    temp->next = NULL;

    ll = rearrange(ll);

    printList(ll);
    deleteList(&ll);
    return 0;
}

void printList(LinkedList ll) {
    ListNode *temp = ll.head;

    while (temp != NULL) {
        printf("%d ", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

void deleteList(LinkedList *llptr) {
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur != NULL) {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
    llptr->head = NULL;
    llptr->size = 0;
}

LinkedList rearrange(LinkedList ll) {

    LinkedList first = split_and_rearrange(ll, 1);
    LinkedList second = split_and_rearrange(first, 0);


    return second;


}

LinkedList split_and_rearrange(LinkedList ll, int arrange_type) {

    int size = ll.size;
    ListNode *node1Head = NULL;
    ListNode *node2Head = NULL;
    ListNode *node1Tail = NULL;
    ListNode *node2Tail = NULL;
    ListNode *cur = ll.head;
    int currentIndex = 0;


    while (cur != NULL) {
        if (currentIndex < (size / 2)) {
            if (node1Head == NULL) {
                node1Head = cur;
                node1Tail = cur;
            } else {
                node1Tail->next = cur;
                node1Tail = cur;
            }
        } else {
            node1Tail->next = NULL;
            if (node2Head == NULL) {
                node2Head = cur;
                node2Tail = cur;
            } else {
                node2Tail->next = cur;
                node2Tail = cur;
            }
        }
        cur = cur->next;
        currentIndex++;
    }


    int alternate = arrange_type;
    ListNode *temp = NULL;
    ListNode *tempHead = NULL;


    int index = 0;

    while (index < size) {
        if (alternate == 0) {

            if (temp == NULL) {

                ListNode *single = malloc(sizeof(ListNode));
                single->item = node1Head->item;
                single->next = NULL;
                temp = single;
                tempHead = temp;

            } else {
                ListNode *single = malloc(sizeof(ListNode));
                single->item = node1Head->item;
                temp->next = single;
                temp = temp->next;
                temp->next = NULL;


            }

            node1Head = node1Head->next;
            alternate = 1;

        } else {
            if (temp == NULL) {


                ListNode *single = malloc(sizeof(ListNode));
                single->item = node2Head->item;
                single->next = NULL;
                temp = single;
                tempHead = temp;
            } else {
                ListNode *single = malloc(sizeof(ListNode));
                single->item = node2Head->item;
                temp->next = single;
                temp = temp->next;
                temp->next = NULL;
            }

            node2Head = node2Head->next;

            alternate = 0;
        }

        index++;
    }

    LinkedList *test = malloc(sizeof(LinkedList));
    test->head = tempHead;
    test->size = size;

    return *test;


}




