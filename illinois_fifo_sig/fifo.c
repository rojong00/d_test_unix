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
        exit(0);
    }

    int ret = mkfifo(argv[1], S_IRWXU | S_IRWXG | S_IRWXO);
    if (ret < 0)
    {
        perror("mkfifo error\n");
        exit(0);
    }

    //int fifo = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
    int fifo = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);

    int tmpFd;

    //dup2(fifo, tmpFd);
    tmpFd = dup(fifo);

    char line[1024];
    /*
    while(fgets(line, 1024, fifo))
    {
        printf("I got this : %s\n", line);
    }
    */
    //while ((ret = read(stdin->_fileno, line, 1024)) != 0)
    while ((ret = read(0, line, 1024)) > 0)
    {
        line[ret] = '\0';
        printf("I got this(%d) : %s", ret, line);
        write(tmpFd, line, ret);

        if (0==strncmp(line, "exit\n", strlen("exit\n")))
        {
            puts("(agree) exit");
            unlink(argv[1]);
            break;
        }
    }

    return 0;
}
