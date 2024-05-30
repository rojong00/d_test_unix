#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char buf[100];
    memset(buf, 1, 100);
    puts("test argv");
    puts(argv[0]);
    printf("argv strlen : %ld\n", strlen(argv[0]));
    printf("argv sizeof : %ld\n", sizeof(argv[0]));

    strncpy(buf, argv[0], strlen(argv[0])+1);
    printf("buf : %s\n", buf);
    printf("buf strlen : %ld\n", strlen(buf));
    printf("buf sizeof : %ld\n", sizeof(buf));
    return 0;
}
