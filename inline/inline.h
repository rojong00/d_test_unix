#ifndef __INLINE_H__
#define __INLINE_H__

#include <stdio.h>


inline int* max(int* a, int* b)
{
    return *a > *b ? a : b;
}

int get_sum_of_array(int len, int arg[len]);

#endif
