#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void interruptHandler(int sig)
{
    if (SIGINT == sig)
    {
        printf("sig : %d\n", sig);
        puts("This pg will be exited in 3 secs");
        sleep(3);
        exit(0);
    }

    if (
}


int main(int argc, char *argv[])
{
    signal(SIGINT, interruptHandler);

    puts("wait");
    pause();
    return 0;
}
