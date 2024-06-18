#include "inline.h"

extern inline int* max(int* a, int* b);
int get_sum_of_array(int len, int arg[len])
{
    int ret = 0;
    int i = 0;
    while (i < len)
    {
        ret += arg[i++];
    }

    return ret;
}

