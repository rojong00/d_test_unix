#include <stdio.h>
#include <string.h>

int global_var = 0;
static int static_var;
int f_static(char* arg)
{
    int len = strlen(arg);
    int i = 0;
    int ret = 0;
    for (i = 0 ; i < len ; i++)
    {
        static_var += (int)(*(arg+i));
    }
}

int main(int argc, char *argv[])
{
    char *arg1 = "hi every body";
    char arg2[100];

    strncpy(arg2, arg1, strlen(arg1));
    printf("new str arg2 : %s\n", arg2);
    printf("arg1 size : %ld, arg2 size : %ld\n", strlen(arg1), strlen(arg2));

    char *arg3 = "abcdefghij";
    strncpy(arg2, arg3, strlen(arg3)-1);
    printf("arg2_-1 : %s(%ld)\n", arg2,strlen(arg2));
    strncpy(arg2, arg3, strlen(arg3));
    printf("arg2_0 : %s(%ld)\n", arg2, strlen(arg2));
    strncpy(arg2, arg3, strlen(arg3)+1);
    printf("arg2_+1 : %s(%ld)\n", arg2, strlen(arg2));
    global_var = 100;
    f_static(arg1);

    memset(arg2, 1, 100);
    puts("\n\nafter memset,\n");
    printf("strlen arg2 : %ld\n", strlen(arg2));
    printf("sizeof arg2 : %ld\n", sizeof(arg2));
    puts("after 5th = \\0,\n");
    arg2[5] = '\0';
    printf("strlen arg2 : %ld\n", strlen(arg2));
    printf("sizeof arg2 : %ld\n", sizeof(arg2));
    global_var = 1000;
    printf("static var : %d\n", static_var);

    puts("\nTEST sprintf, snprintf");
    char arg4[5];
    snprintf(arg4, sizeof(arg4), "%s", "1234567");
    printf("test arg4 1 : %s\n", arg4);
    snprintf(arg4, sizeof(arg4)-1, "%s", "1234567");
    printf("test arg4 2 : %s\n", arg4);
    sprintf(arg4, "%s", "1234567");
    printf("test arg4 3 : %s\n", arg4);
    /*
    sprintf(arg4, "%s", NULL);
    printf("test arg4 4 : %s\n", arg4);
    */
    unsigned char tmptmptmp = 'k';
    printf("tmptmptmp in %c : %05X %05x %05X %05x\n", tmptmptmp, (char*)tmptmptmp, (char*)tmptmptmp, tmptmptmp, tmptmptmp);
    char tmpCharTest = 'k';
    printf("char to int test : %d %d\n", tmptmptmp, tmpCharTest);

    int tmpIntTest = 70;
    printf("int to char test : %d %c\n", tmpIntTest, tmpIntTest);
    int tmpIntTest2 = 999;
    printf("int to char test : %d %c\n", tmpIntTest2, tmpIntTest2);
    
    return 0;
}
