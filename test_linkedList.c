#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char* data;
    struct node* next;
};
typedef struct node Node;

int delete(Node** head, char* days, int lenDays);
int main(int argc, char* argv[])
{
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = "Tuesday";
    head->next = NULL;

    Node* q = (Node*)malloc(sizeof(Node));
    q->data = "Wednesday";
    q->next = NULL;
    
    head->next = q;

    q = (Node*)malloc(sizeof(Node));
    q->data = "Monday";
    q->next = head;

    head = q;

    // INIT END

    Node* p = head;
    while (p!=NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }

    delete(&head, "Monday", strlen("Monday"));

    puts("\nREPRINT\n");

    p = head;
    while (p!=NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }

    delete(&head, "Wednesday", strlen("Wednesday"));

    puts("\nREPRINT\n");
    p = head;
    while (p!=NULL)
    {
        printf("%s\n", p->data);
        p = p->next;
    }

    return 0;
}

int delete(Node** head, char* days, int lenDays)
{
    int ret = 1;
    Node* q = *head;
    printf("\ntest q : q->data : %s\n", q->data);
    //Node* q = *head;
    if (q != NULL)
    {
        if (strncmp(q->data, days, lenDays) == 0)
        {
            Node* tmp = q->next;
            free(*head);
            *head = tmp;
        }
        else
        {
	        while ((q->next)!=NULL)
		    {
		        if (strncmp((q->next)->data, days, lenDays) == 0)
		        {
                    if (q->next->next != NULL)
                    {
                        Node* tmp = q->next->next;
                        free(q->next);
                        q->next = tmp;
                    }
                    else
                    {
                        free(q->next);
                        q->next = NULL;
                        break;
                    }
		        }
		        q = q->next;
		    }
        }
    }

    return ret;
}
