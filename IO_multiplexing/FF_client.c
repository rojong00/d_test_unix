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


    puts("in while loop for readfd");
    while (1)
    {
        int n;
        if ((n = read(readfd, buff, 99)) < 0)
        {
            puts("Err in read");
            printf("n : %d, buff : %s\n", n, buff);
            break;
        }
        if ( n != 0 ) // EOF
        { 
            buff[n] = '\0';

            if ( strncmp(buff, "Exit", strlen(buff)) == 0)
            {
                printf("END : %s\n", argv[1]);
                break;
            }

            printf("<%s> %s\n", argv[1], buff);
        }
        /*
        else if ( n == 0 )
        {
            puts("ENDED");
            break;
        }
        */
    }

    close(readfd);
    return 0;
}
