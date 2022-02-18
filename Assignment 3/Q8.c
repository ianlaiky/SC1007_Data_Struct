#include <stdio.h>
#include <stdlib.h>


#define MAX_N 120

typedef struct _btnode {
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void buildTree(BTNode **node, char *preO, char *postO);

void inOrder(BTNode *cur);

void preOrder(BTNode *cur);

void postOrder(BTNode *cur);

int main() {
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s", preO);
    scanf("%s", postO);

    BTNode *root = NULL;
    buildTree(&root, preO, postO);
    if (root == NULL) printf("error\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");

    inOrder(root);
    printf("\n");

    return 0;
}

void inOrder(BTNode *cur) {
    if (cur == NULL)
        return;

    inOrder(cur->left);
    printf("%c", cur->id);
    inOrder(cur->right);
}

void preOrder(BTNode *cur) {
    if (cur == NULL)
        return;

    printf("%c", cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}

void postOrder(BTNode *cur) {
    if (cur == NULL)
        return;

    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c", cur->id);
}

#include <string.h>

void buildTree(BTNode **node, char *preO, char *postO) {
    // generate binary tree from preorder and postorder

    printf("ROOT: %c\n", preO[0]);

    char *templeftpreO = malloc(sizeof(char) * MAX_N);
    int templeftindex = 0;

    char *temprightpostO = malloc(sizeof(char) * MAX_N);
    int temprightindex = 0;

    while (preO[templeftindex] != postO[strlen(postO) - 2]) {
        templeftpreO[templeftindex] = preO[templeftindex+1];
        templeftindex++;
    }

    templeftpreO[templeftindex-1] = '\0';
    printf("%d\n", templeftindex);

    while (preO[templeftindex] != preO[strlen(preO)-1]) {
        printf("%c ", preO[templeftindex]);
        printf("%c", preO[strlen(preO)-1]);
        printf("\n");
        temprightpostO[temprightindex] = preO[templeftindex];
        templeftindex++;
        temprightindex++;
    }


    temprightpostO[temprightindex] = '\0';

    printf("LEFT: %s\n", templeftpreO);
    printf("RIGHT: %s\n", temprightpostO);

}













