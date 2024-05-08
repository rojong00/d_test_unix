#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAXBUF 256

void child_process(void)
{
	sleep(2);
	char msg[MAXBUF];
	struct sockaddr_in addr = {0};
	int n, sockfd, num = 0;
	srandom(getpid());
	/* Create socket and connect to server */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));

	printf("child {%d} connected \n", getpid());
	while(1)
	{
        int sl = (random() % 10 ) +  1;
	    num++;
        sleep(sl);
  	    sprintf (msg, "Test message %dth from client %d(%ds)", num, getpid(), sl);
  	    n = write(sockfd, msg, strlen(msg));	/* Send message */
        if ( n < 0 )
        {
            printf("write failed : %d\n", getpid());
            break;
        }
    } // end while
}

int main()
{
	char buffer[MAXBUF];
	int fds[5];
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int n, i,max=0;
	uint32_t addrLen;
	int sockfd;
	fd_set rset, tmpSet;
    struct timeval timeout;
	for(i=0;i<5;i++)
	{
		if(fork() == 0)
		{
			child_process();
			exit(0);
		}
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&addr, 0, sizeof (addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&addr ,sizeof(addr));
	listen (sockfd, 5); 

	for (i=0;i<5;i++) 
	{
	  memset(&client, 0, sizeof (client));
	  addrLen = sizeof(client);
	  fds[i] = accept(sockfd,(struct sockaddr*)&client, &addrLen);
	  if(fds[i] > max)
	  	max = fds[i];
	}
  
	FD_ZERO(&rset);
	for (i = 0; i< 5; i++ ) 
    {
		FD_SET(fds[i],&rset);
	}

    int cnt = 0;
    while(1)
    {
        tmpSet = rset;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
	
	   	puts("round again");
		int ret = select(max+1, &tmpSet, NULL, NULL, &timeout);
        if ( ret == -1 )
        {
            puts("Err in select()\n");
            exit(1);
        }
        else if ( ret == 0 )
        {
            puts("Err in select() timeout\n");
            exit(1);
        }
        else
        {
		    //printf("RET is %d\n", ret);
			for(i=0;i<5;i++)
            {
				if (FD_ISSET(fds[i], &tmpSet))
                {
					memset(buffer,0,MAXBUF);
					n = read(fds[i], buffer, MAXBUF);
		            if ( n < 0 )
		            {
		                printf("read err in %d\n", i);
		                FD_CLR(fds[i], &tmpSet);
		            }
		            else
		            {
		                cnt++;
					    puts(buffer);
		            }
				} // fd[i] is the fd
		    } // for loop about fds
        } // if select return is okay

	    if ( cnt > 100 )
	    {
	        puts("cnts over 10");
	        break;
        }
    } // end while

    return 0;
}
