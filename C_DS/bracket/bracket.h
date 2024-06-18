#ifndef __BRACKET_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LEN 20

char *g_open = "[{(";
char *g_close = "]})";

typedef struct node
{
    int ch;
    struct node *next;
} Node;

#endif
