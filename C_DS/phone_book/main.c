#include "prac2.h"

void readCmd(char**);
struct Phone* add(struct Phone*, char*, char*, int);
void _remove(struct Phone*, char*);
void status(struct Phone*);
int _load(struct Phone*, char*);
int save(struct Phone*, char*);
int find(struct Phone*, char*);
void help();

static int CAPACITY = CAPACITY_INIT;

int main(int argc, char* argv[])
{
	struct Phone* List = (struct Phone*)malloc(sizeof(struct Phone)*CAPACITY);
	printf("struct size (sizeof) : %ld\n", sizeof(struct Phone));
	printf("IF YOU DONT KNOW WHAT TO DO : type \"help\"\n");

	int idx = 0;
	int i = 0;
	char** cmd = (char**)malloc(sizeof(char*)*CMD_ARGUMENT);
	for ( i = 0 ; i < CMD_ARGUMENT ; i++ )
		*(cmd+i) = (char*)malloc(sizeof(char)*BUF_SIZE);

	while (1)
	{
		printf("$ ");
		readCmd(cmd);

		if (cmd[0][0] == '\n' || cmd[0][0] == '\0')
			continue;
		else if (strcmp(cmd[0], "add") == 0)
		{
			for ( i = 0 ; i < CAPACITY ; i++ )
			{
				idx = 0;
				if (List[i].idx != 0)
					idx++;
			}
			List = add(List, cmd[1], cmd[2], idx);
		}
		else if (strcmp(cmd[0], "find") == 0)
		{
			int indexFound = 0;
			indexFound = find(List, cmd[1]) - 1;
			if ( !indexFound )
				printf("(phone number) %s\n", List[indexFound].phoneNumber);
			else 
				printf("There is nobody like %s\n", cmd[1]);
		}
		else if (strcmp(cmd[0], "status") == 0)
			status(List);
		else if (strcmp(cmd[0], "remove") == 0)
			_remove(List, cmd[1]);
		else if (strcmp(cmd[0], "exit") == 0)
			break;
		else if (strcmp(cmd[0], "help") == 0)
			help();
		else if (strcmp(cmd[0], "save") == 0)
            save(List, cmd[1]);
		else if (strcmp(cmd[0], "load") == 0)
            _load(List, cmd[1]);
        else if (strcmp(cmd[0], "") == 0 || strcmp(cmd[0], "\0") == 0)
            printf("TYPE SOMETHING!\n");
		else 
			printf("CHK THE CMD WHETHER IT IS RIGHT\n");
	}

	free(List);
	for ( i = 0 ; i < CMD_ARGUMENT ; i++ )
		free(cmd[i]);
	free(cmd);

	return 0;
}

void readCmd(char** str)
{
	char ch;
	bool chkSpace = false;
	int i = 0, idx = 0;

	str[0][0] = '\0';
	str[1][0] = '\0';
	str[2][0] = '\0';

	while ( (ch = getchar()) != '\n' )	
	{
		if ( !chkSpace && isspace(ch) )
			continue;

		if ( idx >= 3 )
		{
			str[0][0] = '\0';
			return;
		}

		chkSpace = true;
		if ( i <= BUF_SIZE-2 )
			str[idx][i++] = ch;
		if ( isspace(ch) )
		{
			chkSpace = false;
			str[idx][i-1] = '\0';
			idx++;
			i = 0;
		}
	}

	str[idx][i] = '\0';
	//printf("cmd CHK : [%s] [%s] [%s]\n", str[0], str[1], str[2]);
}

struct Phone* add(struct Phone* List, char* name, char* phoneNumber, int num)
{
	int chkExistance = find(List, name);
    void* tmpList;
	if ( chkExistance < CAPACITY )
	{
		printf("Already inserted name\n");
        return List;
	}
	if ( strlen(name) == 0 || strlen(phoneNumber) == 0 )
	{
		printf("CHK THE CMD GRAMMAR\n");
		return List;
	}
    // List is full
    if ( chkExistance > CAPACITY )
    {
        CAPACITY += 5;
        tmpList = (struct Phone*)realloc(List, sizeof(struct Phone)*CAPACITY);
        if (tmpList)
        {
            printf("realloc List.\n");
            List = tmpList;
        }
        else
            printf("Err in realloc.\n");
    }
		
	int i = CAPACITY-2;
	int len = 0;
    while ( i >= 0 && ( List[i].idx == 0 || strcmp(List[i].name, name) > 0 ))
    {
        //printf("COMPARED : %s %s %d\n", List[i].name, name, strcmp(List[i].name, name));
        if (List[i].idx != 0)
        {
            List[i+1].idx = i+2;
            strcpy(List[i+1].name, List[i].name);
            strcpy(List[i+1].phoneNumber, List[i].phoneNumber);
        }
        i--;
        //printf("%d\t", i);
    }
    //printf("List[%d] : %s, name : %s\n", i+1, List[i+1].name, name);

    // need improvement to use sort
	List[i+1].idx = i+2;
	len = strlen(name)+1;
    snprintf(List[i+1].name, len, "%s", name);
	len = strlen(phoneNumber)+1;
	strncpy(List[i+1].phoneNumber, phoneNumber, len);
    printf("ADDED\n");
    
    return List;
}

void _remove(struct Phone* List, char* name)
{
    int i = 0;
	int chkExistance = find(List, name);
	if ( chkExistance >= CAPACITY )
	{
		printf("There is no such guy, named %s\n", name);
		return;
	}

	for ( i = chkExistance ; i < CAPACITY-1 ; i++ )
	{
        strcpy(List[i].name, List[i+1].name);
        strcpy(List[i].phoneNumber, List[i+1].phoneNumber);
        if ( List[i+1].idx == 0 )
        {
            List[i].idx = 0;
            break;
        }
	}
}

void status(struct Phone* List)
{
	int i = 0;
	int flagEmpty = 0;
	for ( i = 0 ; i < CAPACITY ; i++ )
	{
		if ( List[i].idx != 0 )
		{
			printf("%d\t%s\t%s\n", List[i].idx, List[i].name, List[i].phoneNumber);
			flagEmpty++;
		}
	}	
	
	if ( !flagEmpty )
		printf("It's empty\n");
}

int find(struct Phone* List, char* name)
{
	int i = 0;
	int Ret = CAPACITY+1;
	for ( i = 0 ; i < CAPACITY ; i++ )
	{
        if ( List[i].idx == 0 )
        {
            Ret = CAPACITY;
            break;
        }

		if ( !strcmp(List[i].name, name) )
		{
			//printf("(phone number) %s\n", List[i].phoneNumber);
			Ret = i;
			break;
		}
	}

	return Ret;
}

int _load(struct Phone* List, char* fileName)
{
    int i = 0;
    int Ret = 0;
    int len = 0;
    char buff1[CAPACITY];
    char buff2[CAPACITY];
    FILE* fp = fopen(fileName, "r");
    if ( fp == NULL )
    {
        printf("Open failed.\n");
        return Ret;
    }

    for ( i = 0 ; i < CAPACITY ; i++ )
    {
        List[i].idx = 0;
        List[i].name[0] = '\0';
    }

    i = 0;
    while ( fscanf(fp, "%s", buff1) != EOF )
    {
        int retFscanf = 0;
        retFscanf = fscanf(fp, "%s", buff2);
        if (retFscanf == EOF)
        {
            printf("error EOF occured.\n");
            return 0;
        }
        List[i].idx = i+1;
        len = strlen(buff1);
        strncpy(List[i].name, buff1, len);
        len = strlen(buff2);
        strncpy(List[i].phoneNumber, buff2, len);
        i++;
    }

    fclose(fp);
    Ret = 1;
	return Ret;
}

int save(struct Phone* List, char* fileName)
{
	int i = 0;
	int Ret = 0;
    FILE* fp = fopen(fileName, "w");
    if ( fp == NULL )
    {
        printf("Save failed.\n");
        return Ret;
    }

    for ( i = 0 ; i < CAPACITY ; i++ )
    {
        if (List[i].idx != 0)
            fprintf(fp, "%s %s\n", List[i].name, List[i].phoneNumber);
    }

    fclose(fp);
    Ret = 1;
	return Ret;
}

void help()
{
	printf("\t*** MANUAL ***\n");
	printf("\tstatus\t <- shows all info listing name - phone numbers\n"
			"\tfind [human_name]\t <- show [human_name] info if registerd\n"
			"\tadd [human_name] [phone_number]\t <- add [human_name] and [phone_number]\n"
			"\tremove [human_name]\t <- remove [human_name] and following [phone_number]\n"
			"\tload [fileName]\t <- load file on List\n"
            "\tsave [fileName]\t <- save file of List\n"
			"\texit\t <- program shut down\n");
}
