#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *arg1 = "hi every body";
    char arg2[100];

    strncpy(arg2, arg1, strlen(arg1));
    printf("new str arg2 : %s\n", arg2);
    printf("arg1 size : %ld, arg2 size : %ld\n", strlen(arg1), strlen(arg2));

    
    return 0;
}
