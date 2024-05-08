#include <stdio.h>

int main()
{
    int num = 8;
    int sum = 0;
    while (num > 0)
    {
        sum += num--;
    }
//
//    if ( sum & 1 == 1 )
//        goto end;
//
    printf("hi1\n");

end:
    printf("SUM : %d\n", sum);

    return 0;
}
    
