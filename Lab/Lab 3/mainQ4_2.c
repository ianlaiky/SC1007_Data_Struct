#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

BTNode* insertBTNode(BTNode* cur, int item);
void printBTNode(BTNode *root, int space,int left);
void deleteTree(BTNode **root);

int smallestValue(BTNode *node);

int main()
{
    BTNode* root=NULL;
    int item;

    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        root = insertBTNode(root, item);
    scanf("%*s");

    printf("The Binary Tree:\n");
    printBTNode(root,0,0);

    if(root){
        printf("The smallest number in the tree is %d.\n",smallestValue(root));
        deleteTree(&root);
        root=NULL;
    }

    return 0;
}

BTNode* insertBTNode(BTNode* cur, int item){
    if (cur == NULL){
	BTNode* node = (BTNode*) malloc(sizeof(BTNode));
	node->item = item;
	node->left = node->right = NULL;
	return node;
	}
    if (rand()%2)
        cur->left  = insertBTNode (cur->left, item);
    else
        cur->right = insertBTNode (cur->right, item);

    return cur;
}

void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->item);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

void deleteTree(BTNode **root){
    if (*root != NULL)
	{
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}

int smallestValue(BTNode *node){
//Write your code here
    int fin=node->item;
    int fin2=node->item;

    if(node->left==NULL && node->right==NULL){
        return node->item;
    }

    if(node->left!=NULL){
        int data = smallestValue(node->left);
        if(node->item<data){
            fin = node->item;
        }else{
           fin = data;
        }
    }

      if(node->right!=NULL){
        int data = smallestValue(node->right);
        if(node->item<data){
            fin2 = node->item;
        }else{
           fin2 = data;
        }
    }
    if(fin<fin2){
        return fin;
    }else{
    return fin2;}





}
