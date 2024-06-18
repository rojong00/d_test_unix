#include "main.h"

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
// what the fuck~
int printPolys(Polynomial **polys);

int main()
{
    int i = 0;
    int tmpChk = 0;
    Polynomial *polys[MAX_POLYS] = {NULL,};
    pthread_t threadSorting;
    pthread_create(&threadSorting, NULL, threadSort, (void*)polys);

    char **buff = (char**)malloc(sizeof(char*)*3);
    for ( i = 0 ; i < 3 ; i++ )
    {
        buff[i] = (char*)malloc(sizeof(char)*BUF_SIZE);
    }

    puts("*** welcome polynomial calculatr ***");
    puts(" if you dont know, how to use this, ");
    puts(" just type 'help' ");
    puts(" * Variable should be x");

    while (1)
    {
        printf("$ ");
        readCmd(buff);
        if (buff[0][0] == '\n')
            continue;

        tmpChk = 0;
        if (strcmp(buff[0], "create") == 0)
        {
            if (strlen(buff[1]) != 1)
            {
                puts("It's wrong Character. the len of char should be 1");
            }
            else 
            {
                tmpChk = findPoly(polys, buff[1][0]);
                if ( tmpChk < MAX_POLYS )
                    puts("It's already registered character");
                else
                {
                    Polynomial *tmpCreatePoly = create_polynomial_instance(buff[1][0]);
                    createPoly(polys, tmpCreatePoly);
                }
            }
        }
        else if (strcmp(buff[0], "add") == 0)
        {
            if (strlen(buff[1]) != 1)
            {
                puts("It's wrong Character. the len of char should be 1");
            }
            else 
            {
                tmpChk = findPoly(polys, buff[1][0]);
                if (tmpChk < MAX_POLYS)
                {
                    tmpChk = addParsing(polys[tmpChk], buff[2]);
                    if (tmpChk != 0)
                        puts("Err occured");
                    else
                        puts("poly added");
                }
                else
                    puts("It's wrong character. there is no charactor.");
            }
        }
        else if (strcmp(buff[0], "print") == 0)
        {
            if (strlen(buff[1]) != 1)
                puts("It's wrong Character. the len of char should be 1");
            else
            {
                if ( *buff[1] == '*' )
                {
                    printPolys(polys);
                    continue;
                }
                tmpChk = findPoly(polys, *buff[1]);
                if (tmpChk < MAX_POLYS)
                    printPoly(polys[tmpChk]);
                else
                    printf("there is no %c type charactor\n", *buff[1]);
            }
        }
        else if (strcmp(buff[0], "eval") == 0)
        {
            if (strlen(buff[1]) != 1)
                puts("It's wrong Character. the len of char should be 1");
            else
            {
                tmpChk = findPoly(polys, *buff[1]);
                if (tmpChk < MAX_POLYS)
                {
                    int numOfEvalPara = convertCharP2Int(buff[2]);
                    if ( numOfEvalPara == MAX_INT )
                    {
                        puts("Err in converting");
                        continue;
                    }
                    tmpChk = eval(polys[tmpChk], numOfEvalPara);
                    printf("Eval(%d) : %d\n", numOfEvalPara, tmpChk);
                }
                else
                    printf("there is no %c type function\n", *buff[1]);
            }
        }
        else if (strcmp(buff[0], "exit") == 0)
        {
            puts("OFF");
            break;
        }
        else if (strcmp(buff[0], "help") == 0)
        {
            puts("\t*** Manual ***");
            puts("\tcreate [char]           <- create polynomial");
            puts("\tadd [char] [polynomial] <- add some polynomial to char");
            puts("\teval [char] [x]         <- calculate evaluation of char in case of x");
            puts("\tprint [char]            <- print polynomial of char");
            puts("\tprint *                 <- print every polynomial");
            puts("\texit                    <- EIXT");
        }
        else
        {
            puts("CHK THE CMD WHETHER IT IS RIGHT.");
        }

	    for ( i = 0 ; i < 3 ; i++ )
	    {
	        buff[i][0] = '\0';
	    }
    }

    pthread_cancel(threadSorting);

    for ( i = 0 ; i < MAX_POLYS ; i++ )
        if (polys[i] != NULL)
            free(polys[i]);

    for ( i = 0 ; i < 3 ; i++ )
    {
        free(buff[i]);
    }
    free(buff);

    pthread_join(threadSorting, NULL);

    return 0;
}

int readLine(char *buff, int n)
{
    int i = 0;
    char c;
    while ((c = getchar()) != '\n')
    {
        if ( i < n-1 )
            buff[i++] = c;
    }
    buff[i] = '\0';
    return i;
}

int readCmd(char **buff)
{
    int i = 0;
    char tmpBuf[100];
    char *token, *forSave;
    const char *del = " ";
    readLine(tmpBuf, 100);
    
    token = strtok_r(tmpBuf, del, &forSave);
    //strncpy(buff[i++], token, strlen(token));
    while (token != NULL)
    {
        if ( i == 3 ) 
        {
            buff[0][0] = 'X';
            break;
        }
        strncpy(buff[i++], token, strlen(token));
        buff[i-1][strlen(token)] = '\0';
        token = strtok_r(NULL, del, &forSave);
    }
    
    return 0;
}

int createPoly(Polynomial **polys, Polynomial* p)
{
    int idx = 0;
    int retFind = findPoly(polys, p->name);
    if (retFind >= MAX_POLYS)
    {
       pthread_mutex_lock(&g_mutex);
       while (*(polys+idx) != NULL)
           idx++;

       if (idx <= MAX_POLYS)
       {
           polys[idx] = p;
           printf("poly \"%c\" has been created.\n", polys[idx]->name);
       }
       pthread_mutex_unlock(&g_mutex);
       
       return 1;
    }
    else
    {
        printf("It's already entered character.\n");
    }

    return 0;
}

int findPoly(Polynomial **polys, char c)
{
    int i = 0;
    pthread_mutex_lock(&g_mutex);
    while (i < MAX_POLYS) 
    {
        if (*(polys+i) != NULL &&
                polys[i]->name == c)
        {
            break;
        }
        i++;
    }
    pthread_mutex_unlock(&g_mutex);

    return i;
}

int convertCharP2Int(char* buf)
{
    int len = strlen(buf);
    int ret = 0;
    int tmp = 0;
    int i = 0;
    int chkSign = 0;
    
    if (*buf == '-')
    {
        chkSign = 1;
        i++;
    }
    while ( len > i )
    {
        ret *= 10;
        tmp = *(buf+i)-'0';
        if (tmp>9 || tmp<0)
        {
            tmp = MAX_INT;
            ret = tmp;
            break;
        }
        ret += tmp;
        if (ret >= MAX_INT)
        {
            ret = MAX_INT;
            break;
        }
        i++;
    }

    if (chkSign)
        ret *= -1;
    return ret;
}

int addParsing(Polynomial *poly, char* buf)
{
    int len = 0;
    char *ptr_1;
    char *ptr_next;
    char *del_1 = "+";
    char arg[100];
    int c = 0;
    int e = 0;
    int i = 0;
    int idx_x = 0;
    int idx_e = 0;

    ptr_1 = strtok_r(buf, del_1, &ptr_next);
    while (ptr_1 != NULL)
    {
        c = 0, e = 0, i = 0;
        idx_x = 0, idx_e = 0;
        len = strlen(ptr_1);
        for (i = 0 ; i < len ; i++)
            if (*(ptr_1 + i)=='x')
            {
                idx_x = i+1;
                break;
            }

        if ( idx_x != 0 )
        {
            idx_e = idx_x;
            if ( idx_e < len && *(ptr_1+idx_e) == '^')
                idx_e = 1;
            else
                idx_e = 0;

            strncpy(arg, ptr_1, idx_x-1);
            arg[idx_x-1] = '\0';
            c = convertCharP2Int(arg);
            if ( c == MAX_INT)
            {
                puts("converting Err in Adding");
                return 1;
            }

            if (idx_e != 0)
            {
                memset(arg, 0, 100);
                strncpy(arg, ptr_1+idx_x+idx_e, len-(idx_x+idx_e));
                arg[len-(idx_x+idx_e)] = '\0';
                e = convertCharP2Int(arg);
                if ( c == MAX_INT)
	            {
	                puts("converting Err in Adding");
	                return 1;
	            }
            }
            else
            {
                e = 1;
            }
        }
        else
        {
            e = 0;
            strncpy(arg, ptr_1, len);
            arg[len] = '\0';
            c = convertCharP2Int(arg);
            if ( c == MAX_INT)
            {
                puts("converting Err in Adding");
                return 1;
            }
        }

        addTerm(poly, c, e);
        ptr_1 = strtok_r(NULL, del_1, &ptr_next);
    }


    return 0;
}

int addTerm(Polynomial *poly, int c, int e)
{
    if (c != 0)
    {
        Term *p = poly->first;
        Term *q = NULL;
        while ( p != NULL && p->expo > e )
        {
            q = p;
            p = p->next;
        }
        if ( p!= NULL && p->expo == e)
        {
            p->coef += c;
            if ( p->coef == 0 )
            {
                if ( q == NULL )
                    poly->first = p->next;
                else 
                    q->next = p->next;
                poly->size -= 1;
                free(p);
            }
        }
        else
        {
            Term *new = create_term_instance();
            new->coef = c;
            new->expo = e;
            new->next = p;
            if ( q == NULL )
            {
                poly->first = new;
            }
            else
            {
                q->next = new;
            }
            poly->size += 1;
        }

        return 1;
    }
    return 0;
}

int eval(Polynomial *poly, int x)
{
    int ret = 0;
    Term *tmp = poly->first;
    while ( tmp != NULL )
    {
        ret += eval_sub(tmp, x);
        tmp = tmp->next;
    }
    return ret;
}

int eval_sub(Term *term, int x)
{
    int ret = term->coef;
    int i = 0;
    for ( i = 0 ; i < term->expo ; i++ ) 
        ret *= x;
    return ret;
}

int printPoly(Polynomial *poly)
{
    printf("%c = ", poly->name);
    Term *tmp = poly->first;
    int cnt = poly->size;
    while ( tmp != NULL )
    {
        cnt--;
        printPoly_sub(tmp);
        tmp = tmp->next;
        if (cnt != 0)
            printf("+");
    }
    fputc('\n', stdout);
        
    return 0;
}

int printPoly_sub(Term *term)
{
    if (term->expo != 1 && term->expo != 0)
        printf("%dx^%d",term->coef, term->expo);
    else if (term->expo == 0)
        printf("%d", term->coef);
    else 
        printf("%dx",term->coef);

    return 0;
}

int printPolys(Polynomial **polys)
{
    int i = 0;
    for (i = 0 ; i < MAX_POLYS ; i++)
    {
        if (polys[i])
            printPoly(polys[i]);
    }

    return 0;
}
