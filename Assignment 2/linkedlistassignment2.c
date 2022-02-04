#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    float item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *reverseSegment(ListNode* head, int start, int end);

int main()
{
    ListNode *head = NULL, *temp;
    float f = 0.0;
    int S, E;

    scanf("%d %d",&S, &E);

    while (scanf("%f", &f)){
        if (head == NULL){
            head = (ListNode*) malloc(sizeof(ListNode));
            temp = head;
        }
        else{
            temp->next = (ListNode*) malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = f;
    }
    temp->next = NULL;

    head = reverseSegment(head,S,E);
    printList(head);
    deleteList(&head);
    return 0;

}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%.2f ",head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
        temp=cur->next;
        free(cur);
        cur=temp;
    }
    *ptrHead=NULL;
}

ListNode *reverseSegment(ListNode* head, int start, int end)
{
// Write your code here
    ListNode *current, *prev, *next, *prev2, *next2, *mid, *mid2, *temp;
    int count = 0;
    current = head;

    while(current != NULL) {
        if (count == (start-1)) {
            prev = current;
        }
        if (count == (start+1)){
            next = current;
        }
        if (count == (end-1)){
            prev2 = current;
        }
        if (count == (end+1)){
            next2 = current;
        }
        if(count == start){
            mid = current;
        }
        if (count == end){
            mid2 = current;
        }
        count++;
        current = current->next;
    }

    current = head;
    count = 0;

    mid2->next = next;
    prev2->next = mid;
    mid->next = next2;
    prev->next = mid2;
    current->next = prev;

}