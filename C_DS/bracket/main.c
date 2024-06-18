#include "bracket.h"

int readLine(char *stack);
uint32_t is_open(char arg);
uint32_t is_close(char arg);
int judge(char ch, char *stPtr, int *top, int *chkBalanced);

int main()
{
    char stack[100] = {0,};
    int ret = 0;
    while (ret != -1)
    {
        ret = readLine(stack);
        printf("%s\n", ret == 0 ? "err" : "good");
        memset(stack, 0, 100);
    }

    int i = 0; tmp
        asm;
    return 0;
}

int readLine(char *stack)
{
    int ch = 0;
    int ret = 0;
    int stTop = 0;
    int chkBalanced = 1;
    int index = 0;
    char buff[100];

    while ((ch=getc(stdin)) != '\n' && chkBalanced)
    {
        buff[index++] = ch;
        ret = judge(ch, stack, &stTop, &chkBalanced);
        if (ret == 0)
            break;
    }
    buff[index] = 0;
    if ( !strncmp(buff, "exit", strlen("exit")) )
    {
        puts("chked exit");
        return -1;
    }

    return ( chkBalanced == 1 && *stack=='\0');
}

__inline uint32_t is_open(char arg)
{
    size_t i = 0;
    for (i = 0 ; i < strlen(g_open) ; i++)
    {
        if (g_open[i]==arg)
            return i;
    }
    return -1;
}

__inline uint32_t is_close(char arg)
{
    size_t i = 0;
    for (i = 0 ; i < strlen(g_close) ; i++)
    {
        if (g_close[i]==arg)
            return i;
    }
    return -1;
}

int judge(char ch, char *stPtr, int *top, int *chkBalanced)
{
    int ret = 0;
    //printf("##%c==%d##\n", ch, ch);
    ret = is_open(ch);
    if (ret > -1)
    {
        // stack PUSH
        *(stPtr+(*top)++) = ret;
        return 1;
    }

    ret = is_close(ch);
    if (ret > -1)
    {
        if (*top == 0)
        {
            *chkBalanced = 0;
            puts("Empty stPtr err");
            return 0;
        }
            
        if ( *(stPtr+*top-1) != ret )
        {
            *chkBalanced = 0;
            puts("Unbalanced bracket err");
            return 0;
        }

        // stack POP
        *(stPtr+(--(*top))) = '\0';
        return 1;
    }


    /*
    if ( !( ch-'0' > -1 && ch-'0' < 10 ))
    {
        if ( ch != '+' && ch != '*' && ch!='/' && ch!='-' )
        {
            puts("Wrong input type");
            return 0;
        }
    }
    */

    if ( *top == MAX_LEN-1 )
    {
        puts("stPtr is full");
        return 0;
    }
    
    return 1;
}
