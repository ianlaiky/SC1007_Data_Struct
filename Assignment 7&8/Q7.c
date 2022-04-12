#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int *M;


int bottom_up_dp(int n, int *s, int *v, int C)
{
    //write your code here

    int i;

//    M[0] = 0;
//    M[1] = 1;

    for (i=0;i<=n;i++)
        M[i] = M[i-1] + M[i-2];

    return M[n];


}


int main ()
{
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    for (i=0; i<=n; i++)
        M[i] = -1;
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));

    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);

    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);

    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));

}