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

int hasGreatGrandchild(BTNode *node);

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

    printf("The node(s) with great grandchild:\n");
    hasGreatGrandchild(root);
    printf("\n");

    deleteTree(&root);
    root=NULL;
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


int hasGreatGrandchild(BTNode *node){
//Write your code here
int con = 0;
    if(node==NULL){
        return 0;
    }
    if(node->right==NULL && node->left==NULL){
        return 0;
    }
//printf("%d ",node->item);

hasGreatGrandchild(node->left);
    if(node->left!=NULL){
        if(node->left->left!=NULL){
                if((node->left->left->left!=NULL || node->left->left->right!=NULL)&& con==0){
            printf("%d ",node->item); con = 1;}

//            return 1;
        } if(node->left->right!=NULL&& con==0){
            if((node->left->right->left!=NULL ||  node->left->right->right!=NULL)&& con==0){
         printf("%d ",node->item);
           con = 1;
        }}


    }
    if(node->right!=NULL && con==0){

         if(node->right->left!=NULL){
                if((node->right->left->left!=NULL || node->right->left->right!=NULL)&& con==0){

            printf("%d ",node->item);   con = 1;}

//            return 1;
        } if(node->right->right!=NULL&& con==0){
            if((node->right->right->left!=NULL ||  node->right->right->right!=NULL)&& con==0){printf("%d ",node->item);

         con = 1;}

        }
    }


hasGreatGrandchild(node->right);

return 0;



}
