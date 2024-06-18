#include "main.h"

Term *create_term_instance()
{
    Term *t = (Term*)malloc(sizeof(Term));
    memset((void*)t, 0, sizeof(Term));
//    t->coef = 0;
//    t->expo = 0;
//    t->next = NULL;
    
    return t;
}

Polynomial *create_polynomial_instance(char name)
{
    Polynomial *p = (Polynomial*)malloc(sizeof(Polynomial));
    p->name = name;
    p->size = 0;
    p->first = NULL;

    return p;
}
