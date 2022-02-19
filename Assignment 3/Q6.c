#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode {
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node {
    BTNode *item;
    struct _node *next;
} StackNode;

typedef struct _stack {
    int size;
    StackNode *head;
} Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode **root, char *prefix);

void printTree(BTNode *node);

void printTreePostfix(BTNode *node);

double computeTree(BTNode *node);

void push(Stack *sPtr, BTNode *item);

int pop(Stack *sPtr);

BTNode *peek(Stack s);

int isEmptyStack(Stack s);

int main() {
    char prefix[SIZE];
    BTNode *root = NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void push(Stack *sPtr, BTNode *item) {
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

BTNode *peek(Stack s) {
    return s.head->item;
}

int isEmptyStack(Stack s) {
    if (s.size == 0) return 1;
    else return 0;
}

void deleteTree(BTNode **root) {
    BTNode *temp;
    if (*root != NULL) {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}


void createExpTree(BTNode **root, char *prefix) {

    Stack s;
    s.size = 0;
    s.head = NULL;
    if (strlen(prefix) == 0) return;
    if (strlen(prefix) == 1) {
        *root = malloc(sizeof(BTNode));
        (*root)->item = prefix[0] - '0' + 10000;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }


    while (*prefix != '\0') {
        if (*prefix != ' ') {
            if (!isEmptyStack(s)) {
//                printf("Current Node item: %c\n", peek(s)->item);
                // pop if left and right is not empty
                BTNode *checker = peek(s);
                while (checker->left != NULL && checker->right != NULL) {
//                    printf("popping\n");
                    pop(&s);
                    if(isEmptyStack(s)) return;
                    checker = peek(s);
                }


            }


            if (*prefix >= '0' && *prefix <= '9') {
                int num = 0;
                while (*prefix >= '0' && *prefix <= '9') {
                    num = num * 10 + *prefix - '0';
                    prefix++;
                }
                // to differentiate int and char
                // exceeding ascii 127 limit
                num = num + 10000;
                BTNode *newNode = peek(s);

                if (newNode->left == NULL) {
                    newNode->left = malloc(sizeof(BTNode));
                    newNode->left->item = num;
                    newNode->left->left = NULL;
                    newNode->left->right = NULL;
                } else if (newNode->right == NULL) {
                    newNode->right = malloc(sizeof(BTNode));
                    newNode->right->item = num;
                    newNode->right->left = NULL;
                    newNode->right->right = NULL;
                } else {


                    printf("Error: Too many numbers\n");
//                    exit(1);

                }


//                printf("LEAF: %d \n", num);

            } else {


                BTNode *newNode = malloc(sizeof(BTNode));
                newNode->item = *prefix;
                newNode->left = NULL;
                newNode->right = NULL;
                if (isEmptyStack(s)) {
                    *root = newNode;
                    push(&s, newNode);
                } else {

                    BTNode *temp = peek(s);
                    if (temp->left == NULL) {
                        temp->left = newNode;
                    } else if (temp->right == NULL) {
                        temp->right = newNode;
                    } else {

                        printf("Error: Too many operators\n");

                    }

                    push(&s, newNode);
                }

//                printf("ROOT: %c \n", *prefix);

            }


        }


        prefix++;
    }


}


void printTree(BTNode *node) {
    // Print in order traversal


    if (node != NULL) {
        printTree(node->left);
        // if item less than 127, it must be a char
        // e.g. '+' as 43 vs operand 43
        if (node->item < 10000) {
            printf("%c ", node->item);
            // else print as int

        } else {
            printf("%d ", node->item - 10000);

        }

        printTree(node->right);
    }

}

void printTreePostfix(BTNode *node) {
    //Write your code here
    if (node != NULL) {
        printTreePostfix(node->left);
        printTreePostfix(node->right);
        if (node->item < 10000) {
            printf("%c ", node->item);

        } else {
            printf("%d ", node->item - 10000);

        }

    }

}

double computeTree(BTNode *node) {
//Write your code here


    if (node != NULL) {
        if (node->item > 10000) {
            return node->item - 10000;
        } else {
            double left = computeTree(node->left);
            double right = computeTree(node->right);
            switch (node->item) {
                case '+':
                    return left + right;
                case '-':
                    return left - right;
                case '*':
                    return left * right;
                case '/':
                    return left / right;
                default:
                    return 0;
            }
        }
    } else {
        return 0;
    }

}



