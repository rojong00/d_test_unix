#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char str[] = "new # is the time # to start, preparing ### for the exam#";
    char delim[] = "#,";
    char* token;
    int sizeofstr = strlen(str);

    char tmp[100];
    strcpy(tmp, str);
    printf("str : %s\n", str);
    printf("tmp[sizeofstr-1] = %c\n", tmp[sizeofstr-1]);
    printf("tmp[sizeofstr] = (%%c:%c) (%%d:%d)\n", tmp[sizeofstr], tmp[sizeofstr]);
    printf("tmp[sizeofstr+1] = %c\n", tmp[sizeofstr+1]);
    token = strtok(tmp, delim);
    while ( token != NULL )
    {
        printf("next token is:%s(%d)\n", token, (int)strlen(token));
        token = strtok(NULL, delim);
    }
    printf("the original : %s\n", str);

    return 0;
}
