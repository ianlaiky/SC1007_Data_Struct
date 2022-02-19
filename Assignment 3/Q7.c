#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode {
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode {
    BTNode *node;
    struct _queuenode *next;
} QueueNode;

typedef struct _queue {
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space, int left);

//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode *node);

int dequeue(Queue *qPtr);

BTNode *getFront(Queue q);

int isEmptyQueue(Queue q);

int twoNodesCost(BTNode *node, int nodeV1, int nodeV2);

int main() {
    BTNode *root = (BTNode *) malloc(sizeof(BTNode));

    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    BTNode *node;
    enqueue(&q, root);

    int nodeV;
    char opL, opR;

    while (!isEmptyQueue(q)) {
        scanf("%d %c %c", &nodeV, &opL, &opR);
        node = getFront(q);
        dequeue(&q);
        node->nodeV = nodeV;

        if (opL != '@') {
            node->left = (BTNode *) malloc(sizeof(BTNode));
            enqueue(&q, node->left);
        } else node->left = NULL;
        if (opR != '@') {
            node->right = (BTNode *) malloc(sizeof(BTNode));
            enqueue(&q, node->right);
        } else
            node->right = NULL;
    }

    int v1, v2;
    scanf("%d %d", &v1, &v2);
    int cost = twoNodesCost(root, v1, v2);

    printBTNode(root, 0, 0);

    printf("Distance is %d\n", cost);
    return 0;
}

void enqueue(Queue *qPtr, BTNode *node) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if (isEmptyQueue(*qPtr))
        qPtr->head = newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if (qPtr == NULL || qPtr->head == NULL) { //Queue is empty or NULL pointer
        return 0;
    } else {
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;
        if (qPtr->head == NULL) //Queue is emptied
            qPtr->tail = NULL;

        free(temp);
        qPtr->size--;
        return 1;
    }
}

BTNode *getFront(Queue q) {
    return q.head->node;
}

int isEmptyQueue(Queue q) {
    if (q.size == 0) return 1;
    else return 0;
}

void printBTNode(BTNode *root, int space, int left) {
    if (root != NULL) {

        int i;
        for (i = 0; i < space - 1; i++)
            printf("|\t");


        if (i < space) {
            if (left == 1)
                printf("|---");
            else
                printf("|___");
        }

        printf("%d\n", root->nodeV);

        space++;
        printBTNode(root->left, space, 1);
        printBTNode(root->right, space, 0);
    }
}

int checkIfNodeExists(BTNode *node, int nodeV) {
    if (node == NULL) return 0;
    if (node->nodeV == nodeV) return 1;
    int leftCost = checkIfNodeExists(node->left, nodeV);
    int rightCost = checkIfNodeExists(node->right, nodeV);

    if (leftCost == 1 || rightCost == 1) return 1;
    else return 0;
}

int height(BTNode *node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    if (leftHeight > rightHeight) return leftHeight + 1;
    else return rightHeight + 1;
}

Queue *printCurrentLevel(BTNode *node, int level, Queue *hqueue) {
    if (node == NULL) return hqueue;
    if (level == 1) {
//        printf("%d ", node->nodeV);
        // adding nodes to queue
        enqueue(hqueue, node);


    } else {
        printCurrentLevel(node->left, level - 1, hqueue);
        printCurrentLevel(node->right, level - 1, hqueue);
    }
}

int twoNodesCost(BTNode *node, int nodeV1, int nodeV2) {


    Queue *q = malloc(sizeof(Queue));
    q->head = malloc(sizeof(QueueNode));
    q->tail = NULL;
    q->size = 0;




    // Traverse by level
    int height4 = height(node);
    int i;

    for (i = 1; i <= height4; i++) {
        printCurrentLevel(node, i, q);
        printf("\n");
    }


    int arrSize = q->size;
    BTNode *templist[arrSize];
    int templistIndex = 0;
    while (!isEmptyQueue(*q)) {
        templist[templistIndex] = getFront(*q);
        dequeue(q);
        templistIndex++;
    }
    //reverse the list
    int j;
    BTNode *reversedList[arrSize];
    for (j = 0; j < arrSize; j++) {
        reversedList[j] = templist[arrSize - j - 1];
    }

    //print the list
    for (j = 0; j < arrSize; j++) {
//        printf("listt %d ", reversedList[j]->nodeV);
    }

    int sum = 0;
    for (int k = 0; k < arrSize; ++k) {
        if (checkIfNodeExists(reversedList[k], nodeV1) == 1 || checkIfNodeExists(reversedList[k], nodeV2) == 1) {
            sum += reversedList[k]->nodeV;
//            printf("sum%d \n", reversedList[k]->nodeV);

        }
        if (checkIfNodeExists(reversedList[k], nodeV1) == 1 && checkIfNodeExists(reversedList[k], nodeV2) == 1) {

            break;
        }

    }


    return sum;


}
