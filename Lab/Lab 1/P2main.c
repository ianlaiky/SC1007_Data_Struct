#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode{
    int item;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
    ListNode *head;
    int size;
} LinkedList;

void moveEvenItemsToBack(LinkedList *ll);

void printList2(LinkedList ll);
ListNode* findNode2(LinkedList ll, int index);
int insertNode2(LinkedList *ll, int index, int item);
void deleteList2(LinkedList *ptrHead);

int main()
{
    LinkedList ll;
    ll.head =NULL;
    ll.size = 0;
    int item;


    printf("Enter a list of numbers, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
    {
        if(!insertNode2(&ll,ll.size, item)) break;
    }

    scanf("%*s");

    printList2(ll);

    moveEvenItemsToBack(&ll);

    printList2(ll);
    deleteList2(&ll);
    return 0;
}

void printList2(LinkedList ll){
        ListNode *cur = ll.head;
        printf("Current List has %d elements: ",ll.size);

        while (cur != NULL){
            printf("%d ", cur->item);
            cur = cur->next;
        }
        printf("\n");
}

ListNode* findNode2(LinkedList ll, int index)
{
        ListNode *cur = ll.head;
        if (cur==NULL || index<0 || index >ll.size)
           return NULL;

        while(index>0){
            cur=cur->next;
            if (cur==NULL)
                return NULL;
            index--;
        }
        return cur;
}

int insertNode2(LinkedList *ll, int index, int item){
    ListNode  *pre, *newNode;
    // If empty list or inserting first node, update head pointer
    if (index == 0){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = ll->head;

        ll->head = newNode;
        ll->size++;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((pre = findNode2(*ll, index-1)) != NULL){
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = pre->next;
        pre->next = newNode;
        ll->size++;
        return 1;
    }
    return 0;
}

void deleteList2(LinkedList *ll){
    ListNode *cur = ll->head;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	ll->head = NULL;
	ll->size = 0;
}

void moveEvenItemsToBack(LinkedList *ll){


    ListNode *odd=NULL;
    ListNode *oddhead=NULL;
    ListNode *even=NULL;
    ListNode *evenhead=NULL;

    ListNode *cur = ll->head;

    while(cur!=NULL){

        printf("123: %d\n",cur->item);

        if(cur->item%2!=0){
           if(oddhead==NULL){
            oddhead = (ListNode*)malloc(sizeof(ListNode));
            oddhead->item = cur->item;
            oddhead->next=NULL;
            odd=oddhead;

            }else{

            odd->next = (ListNode*)malloc(sizeof(ListNode));
            odd = odd->next;
            odd->item = cur->item;
            odd->next=NULL;


            }

        }else{
            if(evenhead==NULL){
            evenhead = (ListNode*)malloc(sizeof(ListNode));
            evenhead->item = cur->item;
            evenhead->next=NULL;
            even=evenhead;

            }else{

            even->next = (ListNode*)malloc(sizeof(ListNode));
            even = even->next;
            even->item = cur->item;
            even->next=NULL;


            }


        }



        cur=cur->next;



    }

    odd->next = evenhead;

ll->head=oddhead;




}
