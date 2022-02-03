#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode {
    int item;
    struct _dbllistnode *next;
    struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist {
    int size;
    CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);

void deleteList(CDblLinkedList *ptrCDLL);

void printList(CDblLinkedList CDLL);

int numMountainPairs(CDblLinkedList CDLL);

int main() {
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;

    int item;
    int i, cases;
    int numP;
    scanf("%d", &cases);
    for (i = 0; i < cases; i++) {
        while (scanf("%d", &item))
            insertNode_AtFront(&himalayas, item);
        scanf("%*s");

        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n", numP);

        deleteList(&himalayas);
    }
    return 0;
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value) {
    //create a new node
    CDblListNode *newNode;
    newNode = (CDblListNode *) malloc(sizeof(CDblListNode));
    newNode->item = value;

    if (ptrCDLL->size == 0) //first node
    {
        newNode->next = newNode;
        newNode->pre = newNode;
        ptrCDLL->head = newNode;
    } else {
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;

        newNode->pre->next = newNode; //update last node next link;
        ptrCDLL->head->pre = newNode;

        ptrCDLL->head = newNode;
    }
    ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL) {

    if (CDLL.head == NULL) return;

    CDblListNode *temp = CDLL.head;
    printf("Current List: ");

    while (temp->next != CDLL.head) {
        printf("%d ", temp->item);
        temp = temp->next;

    }
    printf("%d\n", temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL) {
    if (ptrCDLL->head == NULL) return;
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;

    while (cur->next != ptrCDLL->head) {
        temp = cur->next;
        free(cur);
        cur = temp;
    }

    free(cur);
    ptrCDLL->head = NULL;
    ptrCDLL->size = 0;

}

typedef struct _dbllistnode2 {
    CDblListNode *item;
    CDblListNode *item2;
    struct _dbllistnode2 *next;

} CDblListNode2;

int numMountainPairs(CDblLinkedList CDLL) {
    int numP = 0;
    CDblListNode *temp = CDLL.head;
    CDblListNode *temp2 = temp;
    CDblListNode *temp3;

    CDblListNode2 *pairs = NULL;


    for (int i = 0; i < CDLL.size; ++i) {

        temp2 = temp->next->next;
        int tempItem = temp->next->item;
//        printf("%s %d \n", "new Loop -----------------",tempItem);
        for (int j = 0; j < CDLL.size - 3; ++j) {
//            printf("Checking:%d %d\n", temp->item, temp2->item);

            // Check if pairs exists
            int exists = 0;
            CDblListNode2 *tempPair_1 = pairs;
            while (tempPair_1 != NULL) {
                if ((tempPair_1->item == temp && tempPair_1->item2 == temp2) ||
                    (tempPair_1->item == temp2 && tempPair_1->item2 == temp)) {
//                    printf("Pair exists: %d %d\n", temp->item, temp2->item);
                    exists = 1;

                }
                tempPair_1 = tempPair_1->next;
            }
//            if (exists == 0) {

            if (temp2->item >= tempItem && temp->item >= tempItem) {

//                    printf("%d %d Temp: %d\n", temp->item, temp2->item,tempItem);
                tempItem = temp2->item;
                if (exists == 0) { numP++; }

                if (pairs == NULL) {
                    pairs = (CDblListNode2 *) malloc(sizeof(CDblListNode2));
                    pairs->item = temp;
                    pairs->item2 = temp2;
                    pairs->next = NULL;
                } else {
                    CDblListNode2 *tempPairs = pairs;
                    while (tempPairs->next != NULL) {
                        tempPairs = tempPairs->next;
                    }
                    tempPairs->next = (CDblListNode2 *) malloc(sizeof(CDblListNode2));
                    tempPairs->next->item = temp;
                    tempPairs->next->item2 = temp2;
                    tempPairs->next->next = NULL;
                }
            }
//            }


            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    return numP + CDLL.size;

}




