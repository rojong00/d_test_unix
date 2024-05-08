#include <stdio.h>

int main()
{
    int a = 5;
    int b = 1;
    int c = 0;
    int d = -1;

    printf("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
    puts("TOGGLE");
    printf("a = %d, b = %d, c = %d, d = %d\n", !a, !b, !c, !d);

    return 0;
}
