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

int precedence(char x){

if(x == '/' || x == '*'){
    return 2;
}else{
    return 1;

}


}


void in2Post(char* infix, char* postfix)
{
 //Write your code here
    int po = 0;
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->size=0;
    s->head=NULL;

    while(*infix!='\0'){
//        printf("123 %c:\n",*infix);
        if(*infix == '(' || *infix == ')' || *infix == '+' || *infix == '-'|| *infix == '*'|| *infix == '/'){
            if(*infix == ')'){
                while(peek(*s)!='('){
                    printf("%c ",peek(*s));
                    *postfix=peek(*s);
                    *postfix++;
                    pop(s);
                }
                pop(s);
            }else if(*infix=='('){
             push(s,*infix);

             }else{
                while(!isEmptyStack(*s) && peek(*s)!='(' && precedence(peek(*s))>= precedence(*infix)){
                        printf("%c ",peek(*s));
                         *postfix=peek(*s);
                         *postfix++;
                          pop(s);
                      }
                       push(s,*infix);
             }



        }else{
            printf("%c ",*infix);
             *postfix=*infix;
              *postfix++;
        }


        infix++;
    }

    while(!isEmptyStack(*s)){
          printf("%c ",peek(*s));
             *postfix=peek(*s);
              *postfix++;

            pop(s);
    }






}
