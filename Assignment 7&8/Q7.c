#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int max(int i, int i1);

int bottom_up_dp(int n, int *s, int *v, int C) {
    //write your code here

    int **table = (int **) malloc(sizeof(int *) * n + 1);
    for (int i = 0; i <= n; i++) {
        table[i] = (int *) malloc(sizeof(int) * C + 1);
    }

    //set all values to 0
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= C; j++) {
            table[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= C; j++) {
            if (s[i] <= j) {
                table[i][j] = max(table[i - 1][j], table[i - 1][j - s[i]] + v[i]);
            } else {
                table[i][j] = table[i - 1][j];
            }
        }
    }

    return table[n][C];

}

int max(int i, int i1) {
    if (i > i1) {
        return i;
    } else {
        return i1;
    }

}


int main() {
    int n, C;
    int function;
    int *s;
    int *v;
    int i, j;
    printf("Enter the number of items n:\n");
    scanf("%d", &n);

    printf("Enter the capacity C:\n");
    scanf("%d", &C);
    s = (int *) malloc(sizeof(int) * (n + 1));
    v = (int *) malloc(sizeof(int) * (n + 1));

    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &s[i]);

    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &v[i]);

    printf("The maximum value is: %d \n", bottom_up_dp(n, s, v, C));

}