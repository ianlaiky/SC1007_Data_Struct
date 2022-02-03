#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The size of the array

enum ExpType {
    OPT, OPERAND
};

typedef struct _stackNode {
    char item;
    struct _stackNode *next;
} StackNode;

typedef struct _stack {
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, char item);

int pop(Stack *sPtr);

char peek(Stack s);

int isEmptyStack(Stack s);

typedef struct _listnode {
    int item;
    enum ExpType type;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist {
    int size;
    ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item, enum ExpType type);

int deleteNode(LinkedList *llPtr);

void removeAllNodes(LinkedList *llPtr);

int isEmptyLinkedList(LinkedList ll);


void in2PreLL(char *infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main() {
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c", infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL) {
    ListNode *temp = NULL;
    temp = inExpLL.head;
    while (temp != NULL) {
        if (temp->type == OPERAND)
            printf(" %d ", temp->item);
        else
            printf(" %c ", (char) (temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if (newNode == NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head = newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if (LLPtr == NULL || LLPtr->size == 0) {
        return 0;
    } else {
        ListNode *temp = LLPtr->head;
        LLPtr->head = LLPtr->head->next;

        free(temp);
        LLPtr->size--;
        return 1;
    }
}

int isEmptyLinkedList(LinkedList ll) {
    if (ll.size == 0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr) {
    while (deleteNode(LLPtr));
}

void push(Stack *sPtr, char item) {
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
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

char peek(Stack s) {
    return s.head->item;
}

int isEmptyStack(Stack s) {
    if (s.size == 0) return 1;
    else return 0;
}

int getPriority(char C) {
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;

    return 0;
}

void in2PreLL(char *infix, LinkedList *inExpLL) {

    // calculate size of string
    int size = 0;
    while (infix[size] != '\0')
        size++;

    // Reverse the infix expression
    char *infixReverse = malloc(sizeof(char) * size);
    int i = size - 1;
    int j = 0;
    while (i >= 0) {
        infixReverse[j] = infix[i];
        i--;
        j++;
    }
    infixReverse[j] = '\0';

//    printf("%s\n", infixReverse);

    // Replace ( with ) and vice versa

    char *infixReverse2 = malloc(sizeof(char) * size);
    i = 0;
    j = 0;
    while (infixReverse[i] != '\0') {
        if (infixReverse[i] == '(') {
            infixReverse2[j] = ')';
            j++;
        } else if (infixReverse[i] == ')') {
            infixReverse2[j] = '(';
            j++;
        } else {
            infixReverse2[j] = infixReverse[i];
            j++;
        }
        i++;
    }
    infixReverse2[j] = '\0';

//    printf("%s\n", infixReverse2);

    // Add ( to start and ) to end of string
    char *infixReverse3 = malloc(sizeof(char) * size + 2);
    infixReverse3[0] = '(';
    i = 0;
    j = 1;
    while (infixReverse2[i] != '\0') {
        infixReverse3[j] = infixReverse2[i];
        i++;
        j++;
    }
    infixReverse3[j] = ')';
    infixReverse3[j + 1] = '\0';


//    printf("%s\n", infixReverse3);

    // Infix to postfix
    Stack s;
    s.head = NULL;
    s.size = 0;

    int ia = 0;

    while (infixReverse3[ia] != '\0') {
        if (infixReverse3[ia] == '(') {
            push(&s, infixReverse3[ia]);
        } else if (infixReverse3[ia] == ')') {
            while (peek(s) != '(') {
                insertNode(inExpLL, peek(s), OPT);
                pop(&s);
            }
            pop(&s);
        } else if (infixReverse3[ia] == '+' || infixReverse3[ia] == '-' || infixReverse3[ia] == '*' ||
                   infixReverse3[ia] == '/') {
            while (!isEmptyStack(s) && getPriority(peek(s)) > getPriority(infixReverse3[ia])) {
                insertNode(inExpLL, peek(s), OPT);
                pop(&s);
            }
            push(&s, infixReverse3[ia]);
        } else {
            Stack tempStack;
            tempStack.head = NULL;
            tempStack.size = 0;


            while (infixReverse3[ia] >= '0' && infixReverse3[ia] <= '9') {
                push(&tempStack, infixReverse3[ia]);
                ia++;
            }
            ia--;
            int num = 0;
            //reverse number
            int numReverse = 0;
            while(tempStack.head != NULL) {
                numReverse = numReverse * 10 + (peek(tempStack)-'0');
                pop(&tempStack);
            }

            insertNode(inExpLL, numReverse, OPERAND);


        }
        ia++;
    }

    while (!isEmptyStack(s)) {
        insertNode(inExpLL, peek(s), OPT);
        pop(&s);
    }

    free(infixReverse);
    free(infixReverse2);
    free(infixReverse3);


}


