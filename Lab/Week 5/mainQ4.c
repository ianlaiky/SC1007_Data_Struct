#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The limit of expression length

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

void in2Post(char*, char*);

int main()
{
    char infix[SIZE];
    char postfix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    in2Post(infix,postfix);
    printf("The postfix expression is \n");
    printf("%s\n",postfix);
    return 0;
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = (StackNode *) malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
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
     if(s.size == 0) return 1;
     else return 0;
}

void in2Post(char* infix, char* postfix)
{
    // Convert the infix expression to postfix expression
    Stack s;
    s.size = 0;
    s.head = NULL;

    int i = 0;


    while(infix[i] != '\0'){
        if(infix[i] == '('){
            push(&s, infix[i]);
        }
        else if(infix[i] == ')'){
            while(peek(s) != '('){
                postfix[i] = pop(&s);
                i++;
            }
            pop(&s);
        }
        else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/'){
            while(!isEmptyStack(s) && peek(s) != '(' && (peek(s) == '+' || peek(s) == '-' || peek(s) == '*' || peek(s) == '/')){
                postfix[i] = pop(&s);
                i++;
            }
            push(&s, infix[i]);
        }
        else{
            postfix[i] = infix[i];
            i++;
        }
        i++;
    }

    while(!isEmptyStack(s)){
        postfix[i] = pop(&s);
        i++;
    }
    postfix[i] = '\0';

 
 
 
 
 
}