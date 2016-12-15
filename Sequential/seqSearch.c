#include <stdio.h>

int main(void)
{
    int i, a[] = {10, 1, 3, 3, 5, 7, 8, -9, 0, -3, 2, 5};
    int N = sizeof(a)/sizeof(int);
    int V;
    printf("Enter number to find: ");
    scanf("%d", &V);
    for (i = 0; i < N; i++)
        if (a[i] == V) 
        {
            printf("Found!\n"); 
            break;
        }
    return 0;
}
