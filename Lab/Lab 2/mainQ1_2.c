#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _listnode{
    char item;
    struct _listnode *next;
} ListNode;
typedef ListNode StackNode;
typedef ListNode QueueNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} Stack;

typedef struct _queue{
   int size;
   ListNode *head;
   ListNode *tail;
} Queue;

//Prototypes of Interface functions for Stack structure
void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);
void deleteStack(Stack *sPtr);

//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, char item);
int dequeue(Queue *qPtr);
char getFront(Queue q);
int isEmptyQueue(Queue q);
void deleteQueue(Queue *qPtr);

int palindrome(Queue* wordPtr);

int main()
{
    char item;
    Queue word;
    word.head=NULL;
    word.tail=NULL;
    word.size=0;

    printf("Enter a string of characters, terminated by a newline:\n");
    while(1){
        scanf("%c",&item);
        if(item=='\n') break;
        enqueue(&word,item);
    }

    printf("The string is ");
    printf("%s",palindrome(&word)? "":"not ");
    printf("a palindrome.\n");

    return 0;
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size==0) return 1;
     else return 0;
}

void deleteStack(Stack *sPtr){
     while(pop(sPtr));
}

void enqueue(Queue *qPtr, char item){
    QueueNode *newNode;
    newNode = (QueueNode *) malloc(sizeof(QueueNode));
    newNode->item = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr){
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

char getFront(Queue q){
    return q.head->item;
}

int isEmptyQueue(Queue q){
    if(q.size==0) return 1;
    else return 0;
}
void deleteQueue(Queue *qPtr)
{
    while(dequeue(qPtr));
}

int palindrome(Queue* wordPtr){
//Write your code here

    Queue *newqueue = (Queue*)malloc(sizeof(Queue));
    newqueue->size=0;
    newqueue->head=NULL;
    newqueue->tail=NULL;

    Stack *newstack = (Stack*)malloc(sizeof(Stack));
    newstack->head=NULL;
    newstack->size=0;



    ListNode *temp = wordPtr->head;
//    printf("\n");
    while(temp!=NULL){



        if(temp->item!=' '){

              if(temp->item<='Z'){
//                 printf("123: %c\n",temp->item+32);
                  push(newstack,temp->item+32);
                  enqueue(newqueue,temp->item+32);
//                printf("ququ %c: \n",peek(*newstack));
              }else{
//                printf("123: %c\n",temp->item);}
                push(newstack,temp->item);
                enqueue(newqueue,temp->item);
//              printf("ququ %c: \n",peek(*newstack));
        }



    } temp = temp->next;
}

    while(!isEmptyStack(*newstack)){
            char s = peek(*newstack);
            pop(newstack);
            char ss = getFront(*newqueue);
           dequeue(newqueue);

            if(s!=ss){
                return 0;
            }


    }

    return 1;



}
