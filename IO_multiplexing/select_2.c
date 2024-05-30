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
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#define MAXBUF 256

static pthread_mutex_t s_mutex;

void child_process(int idenfier, int *pCnt)
{
	char msg[MAXBUF];
	struct sockaddr_in addr = {0,};
	int n, sockfd, num = 0;
	srandom(getpid());
	/* Create socket and connect to server */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) != 0)
    {
        printf("err in sockfd of child\n");
        exit(-1);
    }

    int writefd;
    char fifoName[10];
    sprintf(fifoName, "fifo_%d", idenfier);
    if ( (writefd = open(fifoName, O_WRONLY)) > 2)
    {
        puts("write fd already made, and will use it");
    }
    tmp
        test
    else
    {
        //close(writefd);
        if (mkfifo(fifoName, 0666) < 0)
        {
            perror("err in making fifo");
            exit(1);
        }
        if ( (writefd = open(fifoName, O_WRONLY)) < 0 )
        {
            puts("err in open write fd 2");
        }
    }

	while(1)
	{
        int sl = (random() % 5 ) +  1;
	    num++;

        pthread_mutex_lock(&s_mutex);
        *pCnt++;
        pthread_mutex_unlock(&s_mutex);

        sleep(sl);
  	    sprintf (msg, "Test message %dth from client %d(%ds)", num, getpid(), sl);
  	    n = write(sockfd, msg, strlen(msg)+1);	/* Send message */
        if ( n < 0 )
        {
            printf("write failed : %d\n", getpid());
            break;
        }
        else
        {
            n = write(writefd, msg, strlen(msg)+1);
            if (n < 0)
            {
                printf("write(fifo) failed : %d\n", getpid());
                break;
            }
        }

        n = read(sockfd, msg, 99);
        msg[n] = '\0';
        if ( n > 0 )
        {
            char* szExit = "Exit";
            if (strncmp(msg, szExit, strlen(msg)) == 0)
            {
                n = write(writefd, msg, strlen(msg)+1);
                break;
            }
        }
    }

    if (shmdt(p) == -1)
    {
        puts("Err in shmdt");
        exit(7);
    }
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        puts("Err in shmctt");
        exit(8);
    }
    close(sockfd);
    close(writefd);
    unlink(fifoName);
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

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&addr, 0, sizeof (addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(2000);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&addr ,sizeof(addr));
	listen (sockfd, 5); 

    //shared mem
    key_t shmKey;
    int shmId = 0;
    int *pCnt = NULL;
    shmKey = ftok ("/dev/null", 5);       
    printf("shmkey for p = %d\n", shmKey);
    if ((shmId = shmget(shmkey, sizeof(int), 0644 | IPC_CREAT)) < 0)
    {
        perror ("shmget\n");
        exit (5);
    }
    p = (int *)shmat(shmid, NULL, 0);
    *p = 0;

	for(i=0;i<5;i++)
	{
		if(fork() == 0)
		{
			child_process(i, pCnt);
			exit(0);
		}
	}

	for (i=0;i<5;i++) 
	{
	  memset(&client, 0, sizeof (client));
	  addrLen = sizeof(client);
	  fds[i] = accept(sockfd,(struct sockaddr*)&client, &addrLen);
      if (fds[i] == -1)
      {
          exit(-1);
      }
	  if (fds[i] > max)
          max = fds[i];
	}
  
	FD_ZERO(&rset);
	for (i = 0; i< 5; i++ ) {
		FD_SET(fds[i], &rset);
	}
    while(1){
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
        /*
        else if ( ret == 0 )
        {
            puts("Err in select() timeout\n");
            exit(1);
        }
        */
        else{
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
		                //cnt++;
                        puts(buffer);
		            }
				}
		    } // for loop about fds
        } // if ret if okay

	    if (pCnt >= 10)
	    {
            strncpy(buffer, "Exit", strlen("Exit")+1);
	        puts("cnts over 10");
            for (i = 0; i < 5 ; i++)
            {
                sleep(5);
                n = write(fds[i], buffer, strlen(buffer)+1);
            }
	        break;
        }
        else
        {
            strncpy(buffer, "no", strlen("no")+1);
            for (i = 0; i < 5 ; i++)
            {
                n = write(fds[i], buffer, strlen(buffer)+1);
            }
        }
    }

    close(sockfd);
    for (i = 0 ; i < 5 ; i++)
        close(fds[i]);

    if (shmdt(p) == -1)
    {
        puts("Err in shmdt");
        exit(7);
    }
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        puts("Err in shmctt");
        exit(8);
    }

    //while (waitpid(-1, NULL, 0))
    while (!waitpid(-1, NULL, WNOHANG))
    {
        if (errno == ECHILD)
            break;
    }
    

    return 0;
}
