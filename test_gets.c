#include <stdio.h>
#include <string.h>

int main()
{
    char tmp[10];
    
    printf("strlen of tmp : %d\n", (int)strlen(tmp));

    //test size 12 over than sizeof(tmp)
    //fgets(tmp, 12, stdin); 
    fgets(tmp, sizeof(tmp), stdin); 

    printf("tmp : %s\n", tmp);
    printf("tmp size of %ld, strlen of tmp : %ld\n", sizeof(tmp), strlen(tmp));
    printf("(%%c) tmp+8 : %c, tmp+9 : %c, tmp+10 : %c\n", *(tmp+8), *(tmp+9), *(tmp+10));
    printf("(%%X) tmp+8 : %X, tmp+9 : %X, tmp+10 : %X\n", *(tmp+8), *(tmp+9), *(tmp+10));


    return 0;
}
