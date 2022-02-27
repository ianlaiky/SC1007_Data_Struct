#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The limit of expression length

typedef struct _stackNode {
    double item;
    struct _stackNode *next;
} StackNode;

typedef struct _stack {
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, double item);

int pop(Stack *sPtr);

double peek(Stack s);

int isEmptyStack(Stack s);

double exePostfix(char *);

int main() {
    char postfix[SIZE];

    printf("Enter a postfix expression:\n");
    scanf("%[^\n]%*c", postfix);

    printf("The answer is %.2lf.\n", exePostfix(postfix));

    return 0;
}

void push(Stack *sPtr, double item) {
    StackNode *newNode;
    newNode = (StackNode *) malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr) {
    if (sPtr == NULL || sPtr->head == NULL) {
        return 0;
    } else {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

double peek(Stack s) {
    return s.head->item;
}

int isEmptyStack(Stack s) {
    if (s.size == 0) return 1;
    else return 0;
}

double exePostfix(char *postfix) {
    // Evaluate the single digit postfix expression
    Stack s;
    s.size = 0;
    s.head = NULL;

    int i = 0;

    while (postfix[i] != '\0') {
        if (postfix[i] >= '0' && postfix[i] <= '9') {
            push(&s, postfix[i] - '0');
        } else {
            double op1 = peek(s);
            pop(&s);
            double op2 = peek(s);
            pop(&s);
            switch (postfix[i]) {
                case '+':
                    push(&s, op2 + op1);
                    break;
                case '-':
                    push(&s, op2 - op1);
                    break;
                case '*':
                    push(&s, op2 * op1);
                    break;
                case '/':
                    push(&s, op2 / op1);
                    break;
                default:
                    break;
            }
        }
        i++;
    }

    return peek(s);


}