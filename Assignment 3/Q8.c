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
//    preOrder(root);
//    printf("\n");
//    postOrder(root);
//    printf("\n");
//
//    inOrder(root);
//    printf("\n");

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

    if (preO[0] == '\0' || postO[0] == '\0') {
        printf("TRUE");
//        *node = NULL;
        return;
    }

    if(strlen(preO) == 1 && strlen(postO) == 1) {
//        *node = (BTNode *) malloc(sizeof(BTNode));
//        (*node)->id = preO[0];
//        (*node)->left = NULL;
//        (*node)->right = NULL;
//printf("NODE%c\n", preO[0]);
        return;
    }


    printf("ROOT: %c\n", preO[0]);

    char *templeftpreO = malloc(sizeof(char) * MAX_N);
    int templeftindex = 0;
    char *templeftpostO = malloc(sizeof(char) * MAX_N);
    int templeftpostoindex = 0;
    char *temprightpreO = malloc(sizeof(char) * MAX_N);
    int temprightindex = 0;
    char *temprightpostO = malloc(sizeof(char) * MAX_N);
    int temprightpostoindex = 0;

    while (preO[templeftindex] != postO[strlen(postO) - 2]) {
        templeftpreO[templeftindex] = preO[templeftindex + 1];
        templeftindex++;
    }
    templeftpreO[templeftindex - 1] = '\0';
    printf("LEFTpreO: %s\n", templeftpreO);

    while (postO[templeftpostoindex] != preO[1]) {
        templeftpostO[templeftpostoindex] = postO[templeftpostoindex];
        templeftpostoindex++;
    }

    templeftpostO[templeftpostoindex] = preO[1];
    templeftpostO[templeftpostoindex + 1] = '\0';
    printf("LEFTposto: %s\n", templeftpostO);


    while (preO[templeftindex] != preO[strlen(preO) - 1]) {

        temprightpreO[temprightindex] = preO[templeftindex];
        templeftindex++;
        temprightindex++;
    }


    temprightpreO[temprightindex] = preO[strlen(preO) - 1];
    temprightpreO[temprightindex + 1] = '\0';
    printf("RIGHTpreo: %s\n", temprightpreO);

    templeftpostoindex++;
    while (postO[templeftpostoindex] != postO[strlen(postO) - 1]) {
        temprightpostO[temprightpostoindex] = postO[templeftpostoindex];
        temprightpostoindex++;
        templeftpostoindex++;
    }


    temprightpostO[temprightpostoindex] = '\0';

    printf("RIGHTposto: %s\n", temprightpostO);

    buildTree(NULL, templeftpreO, templeftpostO);
    buildTree(NULL, temprightpreO, temprightpostO);


}









