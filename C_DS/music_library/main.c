#include "music.h"

Node *find(Node *ptr_head, char *word);
Node *get_node(Node* const ptr_head, int index);
void add_first(Node**, char*);
int add_after(Node** prev, char* item);
int remove_first(Node** ptr_head);
int remove_after(Node** ptr_prev);
int remove_by_index(Node **ptr_head, int index);
Node *remove_by_data(Node **ptr_head, char *);
int add(Node** ptr_head, int index, char* item);

int main(int argc, char* argv[])
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = "something";
    head->next = NULL;

    add_after(&head, "something3");
    add_after(&head, "something2");


    Node* p = head;
    while (p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }

    printf("2\n");
    p = find(head, "something9");
    while (p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }

    printf("3\n");
    p = find(head, "something2");
    remove_after(&p);
    p = head;
    while (p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }

    printf("5\n");
    p = get_node(head, 3);
    if ( p != NULL )
        printf("%s\n", p->data);
    else 
        printf("it's over\n");

    printf("6\n");
    remove_first(&head);
    p = head;
    while (p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }

    printf("7\n");
    add(&head, 0, "something10");
    add(&head, 1, "something5");
    add(&head, 2, "something6");
    remove_by_index(&head, 1);
    p = head;
    while (p != NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }

    return 0;
}

void add_first(Node** ptr_head, char* item)
{
    Node* tmp = (Node*)malloc(sizeof(Node));

    //tmp->data = item;
    tmp->data = strdup(item);
    
    tmp->next = *ptr_head;
    *ptr_head = tmp;
}

int add_after(Node** prev, char* item)
{
    if ( *prev == NULL )
        return 0;

    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->data = strdup(item);
    tmp->next = (*prev)->next;
    (*prev)->next = tmp;
    return 1;
}

int remove_first(Node** ptr_head)
{
    if ( *ptr_head == NULL )
        return 0;

    Node *tmp = (*ptr_head)->next;
    free(*ptr_head);
    *ptr_head = tmp;

    return 1;
}

int remove_after(Node** ptr_prev)
{
    if (*ptr_prev == NULL || (*ptr_prev)->next == NULL)
        return 0;

    Node* tmp = (*ptr_prev)->next;
    (*ptr_prev)->next = tmp->next;
    free(tmp);
    return 1;
}

int remove_by_index(Node **ptr_head, int index)
{
    if (index == 0)
    {
        return remove_first(ptr_head);
    }

    Node *prev = get_node(*ptr_head, index-1);
    if (prev == NULL)
        return 0;
    else 
        return remove_after(&prev);
}

Node *remove_by_data(Node **ptr_head, char* word)
{
    Node* tmp = *ptr_head;

    if ( strcmp(tmp->data, word) )
        return tmp;

    while ( strcmp(tmp->next->data, word) || tmp != NULL )
    {
        tmp = tmp->next;
    } 

    return tmp;
}

Node *find(Node *ptr_head, char *word)
{
    Node *p = ptr_head;
    while ( p != NULL ) 
    {
        if (strcmp(p->data, word) == 0)
            return p;
        else
            p = p->next;
    }
    printf("find : can't find %s\n", word);
    return NULL;
}

Node *get_node(Node* const ptr_head, int index)
{
    if (index < 0)
        return NULL;

    Node *p = ptr_head;
    while (index-- > 0)
    {
        if (p==NULL)
            return NULL;
        p = p->next;
    }

    return p;
}

int add(Node** ptr_head, int index, char* item)
{
    if (index < 0)
        return 0;

    if (index == 0)
    {
        add_first(ptr_head, item);
        return 1;
    }

    Node *tmp = (Node*)malloc(sizeof(Node));
    tmp->data = item;
    tmp->next = NULL;
    
    Node *prev = get_node(*ptr_head, index-1);
    if (prev != NULL)
    {
        add_after(&prev, item);
        return 1;
    }

    return 0;
}
