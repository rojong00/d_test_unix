#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore[3];

void *threadRoutine(void *argumentPointer)
{
    long id = (long)argumentPointer;
    int i;
    for (i=0 ; i<10000 ; i++)
    {

        printf("try     : sem_wait %ld.\n", id);
        sem_wait(&semaphore[id]);
        printf("success : sem_wait %ld.\n", id);

        printf("try     : sem_wait %ld.\n", 1-id);
        sem_wait(&semaphore[1-id]);
        printf("success : sem_wait %ld.\n", 1-id);

        printf("try     : sem_wait %ld.\n", id);
        sem_wait(&semaphore[id]);
        printf("success : sem_wait %ld.\n", id);

        printf("try     : sem_wait %ld.\n", 1-id);
        sem_wait(&semaphore[1-id]);
        printf("success : sem_wait %ld.\n", 1-id);
    }

    return NULL;
}

int main()
{
    pthread_t threadDs[3];
    
    sem_init(&semaphore[0], 0, 1);
    sem_init(&semaphore[1], 0, 1);

    pthread_create(&threadDs[0], NULL, threadRoutine, (void*)0);
    pthread_create(&threadDs[1], NULL, threadRoutine, (void*)1);


    pthread_join(threadDs[0], NULL);
    pthread_join(threadDs[1], NULL);

    printf("No DeadLock!\n");
    return 0;
}
