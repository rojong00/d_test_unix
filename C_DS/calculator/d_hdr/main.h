#ifndef __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_POLYS   10
#define BUF_SIZE    20
#define MAX_INT     999999

typedef struct term
{
    int coef;
    int expo;
    struct term *next;
} Term;

typedef struct polynomial
{
    char name;
    int size;
    struct term *first;
} Polynomial;

// in PTH.c
extern pthread_mutex_t g_mutex;

// in FUNC.c
Term *create_term_instance();
Polynomial *create_polynomial_instance(char name);

// in PTH.c
void *threadSort(void *arg);
int sorting(Polynomial **list);

// in MAIN.c
int readLine(char *buff, int n);
int readCmd(char **buff);
int convertCharP2Int(char* buf);
int addParsing(Polynomial *poly, char* buf);
int addTerm(Polynomial *poly, int c, int e);
int createPoly(Polynomial **polys, Polynomial* p);
int findPoly(Polynomial **polys, char c);
int eval(Polynomial *poly, int x);
int eval_sub(Term *term, int x);
int printPoly(Polynomial *poly);
int printPoly_sub(Term *term);
int printPolys(Polynomial **polys);

#endif
