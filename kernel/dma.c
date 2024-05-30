#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define BULK

enum ENUM
{
    my_A,
    my_B,
    my_C
};

static char *lb = NULL;

int main()
{
    unsigned char* text = "text";
    long tmp0 = 9;
    long long tmp1 = 10;
    int32_t tmp2 = 11;
    unsigned long long tmp3 = 12;
    
    printf("tmp0 : %ld(size:%ld)\n", tmp0, sizeof(tmp0));
    printf("tmp1 : %lld(size:%ld)\n", tmp1, sizeof(tmp1));
    printf("tmp2 : %d(size:%ld)\n", tmp2, sizeof(tmp2));
    printf("tmp3 : %llu(size:%ld)\n", tmp3, sizeof(tmp3));

    printf("enum test : %d\n", my_A);
    enum ENUM tmp4 = my_B;
    printf("enum test : %d\n", tmp4);

    printf("%s\n", text);

    lb = (char*)malloc(sizeof(char)*100);

    int i = 0;
    for (i = 0 ; i < strlen(text) ; i++)
    {
        printf("text : %02X\n", (*(text+i)));
        //printf("text : %02X\n", (char*)(*(text+i)));
        lb += sprintf(lb, "%02X ", *(text+i));
    }
    printf("casting text : %X \n", *text);
    puts("0");
    lb += sprintf(lb, "\n");

    printf("lb : %s\n", lb);

    free(lb);

    return 0;
}
