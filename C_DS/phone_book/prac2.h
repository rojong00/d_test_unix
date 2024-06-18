#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BUF_SIZE        12
#define CAPACITY_INIT   2
#define CMD_ARGUMENT    3

struct __attribute__((packed)) Phone
{
    char tmp;
    int idx;
    char name[BUF_SIZE];
    char phoneNumber[BUF_SIZE];
};
