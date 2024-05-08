#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void lenPtr(char *buf);
char **fnStrTok(char *buf);
int main()
{
    char tmp[] = "apple";
    char tmp2[] = "applea\0";
    char tmp3[] = "apple\0a";
    char tmp4[] = "apple:bpp:le";
    printf("strlen tmp : %ld\n", strlen(tmp));
    printf("sizeof tmp : %ld\n", sizeof(tmp));
    
    lenPtr(tmp);
    lenPtr(tmp2);
    lenPtr(tmp3);

    char **pptr = fnStrTok(tmp4);
    int i = 0 ;
    while ( pptr[i])
    {
        printf("pptr[%d] : %s,  ", i, pptr[i]);
        printf("strlen : %ld\n", strlen(pptr[i++]));
    }

    i = 0;
    while ( pptr[i] )
    {
        free(pptr[i++]);
    }
    free(pptr);
    
    return 0;
}

void lenPtr(char *buf)
{
    int a = strlen(buf);
    printf("buf in fn:lenPtr : %d\n", a);
}

char **fnStrTok(char *buf)
{
    char *ptr;
    char *ptr_next;
    char *del = ":";
    char **arr = (char**)malloc(sizeof(char*));
    int cnt = 0;
    int len = 0;

    ptr = strtok_r(buf, del, &ptr_next);
    while (ptr!= NULL)
    {
        cnt++;
        len = strlen(ptr);
        printf("len : %d\n", len);
        arr = (char**)realloc(arr, cnt*sizeof(char*)+1);
        arr[cnt-1] = (char*)malloc(len*sizeof(char)+1);
        strncpy(arr[cnt-1], ptr, len);
        arr[cnt-1][len] = '\0';

        ptr = strtok_r(NULL, del, &ptr_next);
    }

    return arr;
}
