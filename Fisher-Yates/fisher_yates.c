#include <stdio.h>
#include <math.h>
#include <time.h>

int main()
{
    int A[10];
    int i, length = 10;
    int rnd, tmp;

    for (i = 0; i < length; ++i) {
        A[i] = i + 1;
    }
    printf("Before fisher-yates shuffle sort: \n");
    for (i = 0; i < length; ++i) {
        printf("%d ", A[i]);
    }
    printf("\n");


    for (i = 0; i < 10; ++i) {
        srand((unsigned int)time(0));
        rnd = (int)(rand() % length);
        --length;

        tmp = A[length];
        A[length] = A[rnd];
        A[rnd] = tmp;
    }
    
    printf("After fisher-yates shuffle sort: \n");
    for (i = 0; i < 10; ++i) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    return 0;
}
