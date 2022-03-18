#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void insertBSTNode(BTNode** cur, int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

int main()
{
    BTNode* root = NULL;
    int item;

    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        insertBSTNode(&root, item);
    scanf("%*s");

    printf("The Binary Search Tree:\n");
    printBTNode(root,0,0);

    deleteTree(&root);
    root=NULL;
    return 0;
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

void insertBSTNode(BTNode** cur, int item){
    //Write Your Code Here
    BTNode *temp=*cur;
    if(temp==NULL){
        printf("123");
        temp=(BTNode*)malloc(sizeof(BTNode));
        temp->item=item;
        temp->left=NULL;
        temp->right=NULL;
        *cur=temp;
    }else{

        while(temp!=NULL){
            if((temp->item)>item){
                if(temp->left==NULL){

//                               printf(" 123ssssssssssdd ");
                    temp->left=(BTNode*)malloc(sizeof(BTNode));
                    temp->left->item=item;
                    temp->left->left=NULL;
                    temp->left->right=NULL;
                    break;
                }
                temp=temp->left;
            }else if((temp->item)<item){

                 if(temp->right==NULL){
//                            printf(" 123sdd ");
                    temp->right=(BTNode*)malloc(sizeof(BTNode));
                    temp->right->item=item;
                    temp->right->left=NULL;
                    temp->right->right=NULL;
                    break;
                }
                  temp=temp->right;
            }else{
                printf("Duplicate %d",temp->item);
                break;
            }

        }
    }











}
