#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    char *buff = NULL;
    size_t len = 0;
    ssize_t read;

    char buff2[28];
    size_t len2 = 28;


    fp = fopen("text", "r");
    if (fp == NULL)
    {
        fclose(fp);
        printf("NULL\n");
        return 0;
    }

    while ( (read = getline(&buff, &len, fp) != -1) )
    {
        printf("buff (size : %ld, strlen : %ld ) : %s\n", len, strlen(buff), buff);
    }
    if ( len != 0 )
    {
        puts("free buff");
        free(buff);
    }
        
    fclose(fp);


    puts(" END getline, START fgetc ");
    fp = fopen("text", "r");
    if (fp == NULL)
    {
        fclose(fp);
        printf("NULL\n");
        return 0;
    }


    while ( fgets(buff2, len2, fp) )
    {
        printf("\n");
        printf("buff (size : %ld) : %s\n", strlen(buff2), buff2);
        for ( int i = 0 ; i <= strlen(buff2) ; i++ )
            printf("%x\t", *(buff2+i));
    }



    return 0;
}
