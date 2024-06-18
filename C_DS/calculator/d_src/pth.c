#include "main.h"

pthread_mutex_t g_mutex;

void *threadSort(void *arg)
{
    Polynomial **polys = (Polynomial **)arg;
    int ret = 0;
    while (1)
    {
        sleep(8);
        
        pthread_mutex_lock(&g_mutex);
        ret = sorting(polys);
        if ( ret != 0 )
            printf("Err occured in threadSort!\n");
        pthread_mutex_unlock(&g_mutex);
    }
}

// BUBBLE
int sorting(Polynomial **list)
{
    int i = 0, j = 0;;
    Polynomial *tmp;
    for (i = 0 ; i < MAX_POLYS-1 ; i++)
    {
        for (j = 0 ;j < MAX_POLYS-1-i ; j++)
        {
            if ( list[j] == NULL && list[j+1] == NULL )
                continue;

            if ( list[j] != NULL && list[j+1] == NULL )
                continue;

            if ( list[j] == NULL && list[j+1] != NULL )
            {
                list[j] = list[j+1];
                list[j+1] = NULL;
                continue;
            }

            if (list[j]->name > list[j+1]->name)
            {
                tmp = list[j];
                list[j] = list[j+1];
                list[j+1] = tmp;
                continue;
            }

            if (list[j]->name <= list[j+1]->name)
                continue;

            return 1;
        }
    }

    return 0;
}
