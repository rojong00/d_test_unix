#include "inline.h"
//extern inline int* max(int* a, int* b);

int main(int argc, char* argv[])
{
    int a = 5;
    int b = 4;
    
    printf("a = %d, b = %d\nBigger one is %d\n", a, b, *(max(&a, &b)));
    

    int i = 1, j = 2, k = 3;
    int total = get_sum_of_array(3, (int[]){2 * i, i + j, j * k});

    printf("total for compounnd literal ; %d\n", total);

    return 0;
}
