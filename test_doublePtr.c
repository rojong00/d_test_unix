#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void double_ptr_test(char** arg1)
{
    char *tmp = (char*)malloc(sizeof(char)*4);
    char *testMention = "abc";
    
    int len = snprintf(tmp, strlen(testMention), "%s", testMention);
    printf("strlen(testMention is %ld, len is %d\n", strlen(testMention), len);
    tmp[len] = '\0';
    

    *arg1 = tmp;
}

int main(int argc, char* argv[])
{
    char *ptr;
    double_ptr_test(&ptr);

    printf("ptr str : %s\n", ptr);
    printf("ptr ch : %c\n", *ptr);

    free(ptr);
    return 0;
}
