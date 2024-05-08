#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

// FIFO like pipe
// Enables the communication between processors using FIFO file name
int main(int argc, char *argv[])
{
    if ( argc < 2 )
    {
        puts("arg is lacked");
        return 1;
    }

    char buff[100] = {0,};
    int readfd = open(argv[1], O_RDONLY);
    if ( 0 > readfd )
    {
        puts("err in open readfd");
        return 2;
    }


    while (1)
    {
        int n;
        if ( (n = read(readfd, buff, 99) ) > 0 )
        {
            buff[n] = '\0';
            printf("%s", buff);
        }
        else if ( n == 0 )
        {
            puts("ENDED");
            break;
        }
        else
        {
            puts("Err in read");
            printf("n : %d, buff : %s\n", n, buff);
            break;
        }
    }

    return 0;
}
