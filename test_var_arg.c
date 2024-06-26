#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int vaPrint(const char* arg, ...)
{
    va_list var;
    int i = 0;

    va_start(var, arg);
    while (*(arg+i))
    {
        if (*(arg+i) == '%')
        {
            i++;
            switch (*(arg+i))
            {
                case 'd':
                    {
                        int tmp = va_arg(var, int);
                        printf("tmp : %d\n", tmp);
                        break;
                    }
                case 'c':
                    {
                        char tmp = (char)va_arg(var, int);
                        printf("tmp : %c\n", tmp);
                        break;
                    }
                case 's':
                    {
                        char* tmp = va_arg(var, char*);
                        printf("tmp : %s\n", tmp);
                        break;
                    }
                default:
                    continue;
            }
            i += 1;
        }
        else
        {
            i++;
        }
    }
    va_end(var);
}

int main(int argc, char* argv[])
{
    vaPrint("%d %d %c %s", 3, 10, 'c', "abc");
    
    printf("And test strchr func.\n");
    
    char* cstring = "abcd e pw xyz";
    char ch = 'p';
    char* ptr = strchr(cstring, (int)ch);
    printf("cstring is \"%s\", ptr is \"%s\"\n", cstring, ptr);


    return 0;
}
