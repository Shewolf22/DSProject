#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100

FILE *fp;

typedef struct book{
    char title[MAX];
    char author[MAX];
    char ID[MAX];
}Book;

typedef struct node{
    Book book;
    struct node *next;
    struct node *prev;
}node;
node *START = NULL;

typedef struct dnode
{
    char bookid[MAX];
    int issuedate;
    int issuemonth;
    struct dnode *next,*prev;
}dnode;

node *create(Book, node*);
dnode *issue_record(char *bi,int issda,int ism,dnode *head);
void insert(Book);
void deleteBook(char *);
void replaceSpaces(char *);
void replaceUnder(char *);
void display();
void getBookData(Book *);
void writeToFile();
void readFromFile();
void writeIssueRecords(dnode *head);
dnode *readIssueRecords(dnode *head);
int ntbe(int bi,dnode *head);
void finecalc(int,int,int,int);
int datecalc();
void currentdate();
int find_issue_date(dnode *head,char[MAX]);
int find_issue_month(dnode *head,char[MAX]);
int isPresent(char *);
void mainmenu();


int main()
{
    printf("\n\n\n\t*******Library Management System*******\n\n\t\t");
    printf("Go To Main Menu");
    printf("\nPress Any Key To Continue....");
    getch();

    mainmenu();

    return 0;
}

//Gets the book details from user
void getBookData(Book *new_book)
{
    fflush(stdin); //Flush the stdin so that no garbage value gets picked up

    printf("Enter the book title\n");
    fgets(new_book->title, MAX, stdin);
    new_book->title[strcspn(new_book->title, "\n")] = 0; //Replaces the \n character at the end with \0

    printf("Enter the author\n");
    fgets(new_book->author, MAX, stdin);
    new_book->author[strcspn(new_book->author, "\n")] = 0;

    printf("Enter the book ID\n");
    fgets(new_book->ID, MAX, stdin);
    new_book->ID[strcspn(new_book->ID, "\n")] = 0;
}

//Writes the book details from the linked list to data.txt
void writeToFile()
{
    Book b;
    node *cursor;
    fp = fopen("data.txt", "w");
    if(fp == NULL)
    {
        printf("Error\n");
    }
    else
    {
        cursor = START;
        if(START != NULL)
        {
            while(cursor != NULL)
            {
                b = cursor->book;
                replaceSpaces(b.title);
                replaceSpaces(b.author);
                fprintf(fp, "%s|%s|%s\n", b.title, b.author, b.ID);
                cursor = cursor->next;
            }
        }
        
    }
    fclose(fp);
}

//Reads the books from data.txt and creates a linked list to store them
void readFromFile()
{
    fp = fopen("data.txt", "r");
    if(fp == NULL)
    {
        printf("Error\n");
    }
    else
    {
        char temp[MAX];
        while(fscanf(fp, "%s\n", temp) != EOF)
        {
            Book b;
            int i = 0, j = 0, k = 0;
            replaceUnder(temp);

            //Extract the Book title
            while(temp[i] != '|')
            {
                b.title[i] = temp[i];
                i++;
            }
            b.title[i] = '\0';

            i++;
            ///Extracts the Book Author
            while(temp[i] != '|')
            {
                b.author[j] = temp[i];
                i++;
                j++;
            }
            b.author[j] = '\0';

            i++;
            //Extracts the Book ID
            while(temp[i] != '\0')
            {
                b.ID[k] = temp[i];
                i++;
                k++;
            }
            b.ID[k] = '\0';
            insert(b);
        }
    }
    fclose(fp);
}

//Allocates space and initializes a new node
node* create(Book b,node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating a new node\n");
        exit(0);
    }
    new_node->book = b;
    new_node->next = next;

    return new_node;
}

//Creates a new node in the books linked list
void insert(Book b)
{
    node *newnode, *cursor;

    if(START == NULL)
    {
        newnode = create(b, NULL);
        START = newnode;
    }
    else
    {
        cursor = START;
        while(cursor->next != NULL)
        {
            cursor = cursor->next;
        }

        newnode =  create(b, NULL);
        cursor->next = newnode; 
    }
}

//Displays the books
void display()
{
    node *cursor;
    cursor = START;
    while(cursor != NULL)
    {
        printf("Book Title: %s\t\t", cursor->book.title);
        printf("Book Author: %s\t\t", cursor->book.author);
        printf("Book ID: %s\n", cursor->book.ID);
        cursor = cursor->next;
    }
}

//Deletes a book from the list
void deleteBook(char *id)
{
    node *cursor, *pre;

    if(START == NULL)
    {
        printf("No books found\n");
    }
    else
    {
        cursor = pre = START;
        while((strcmp(cursor->book.ID, id) != 0) && (cursor->next != NULL))
        {
            pre = cursor;
            cursor = cursor->next;
        }

        if(strcmp(cursor->book.ID, id) == 0)
        {
            if(cursor == START)
                START = cursor->next;
            else
                pre->next = cursor->next;
            printf("Book succesfully deleted\n");
            free(cursor);
        }
        else
        {
            printf("Book not found\n");
        }
    }
}

void replaceSpaces(char *c)
{
    int i;
    for(i = 0; i < strlen(c); i++)
    {
        if(c[i] == ' ')
        {
            c[i] = '_';
        }
    }
}

void replaceUnder(char *c)
{
    int i;
    for(i = 0; i < strlen(c); i++)
    {
        if(c[i] == '_')
        {
            c[i] = ' ';
        }
    }
}

int datecalc()
{ 
    int dd;
    char subdate[2];
    int c=0,d=2,p;
    char sn[100];
    time_t ct;
    ct=time(NULL);
    char* cts;
    cts=ctime(&ct);
    strcpy(sn,cts);
    p=9;
    while(c<d)
    {
        subdate[c]=sn[p+c-1];
        c++;
    }
    subdate[c]='\0';
    dd=atoi(subdate);

    return dd;
}

int monthcalc()
{
    char submonth[2];
    int c=0,m=3,p;
    char sn[100];
    time_t ct;
    ct=time(NULL);
    char* cts;
    cts=ctime(&ct);
    strcpy(sn,cts);
    p=5;
    while(c<3)
    {
        submonth[c]=sn[p+c-1];
        c++;
    }
    submonth[c]='\0';
    if(strcmp(submonth,"Jan")==0)
    {
        return 1;
    }else
    if(strcmp(submonth,"Feb")==0)
    {
        return 2;
    }else
    if(strcmp(submonth,"Mar")==0)
    {
        return 3;
    }else
    if(strcmp(submonth,"Apr")==0)
    {
        return 4;
    }else
    if(strcmp(submonth,"May")==0)
    {
        return 5;
    }else
    if(strcmp(submonth,"Jun")==0)
    {
        return 6;
    }else
    if(strcmp(submonth,"Jul")==0)
    {
        return 7;
    }else
    if(strcmp(submonth,"Aug")==0)
    {
        return 8;
    }else
    if(strcmp(submonth,"Sep")==0)
    {
        return 9;
    }else
    if(strcmp(submonth,"Oct")==0)
    {
        return 10;
    }else
    if(strcmp(submonth,"Nov")==0)
    {
        return 11;
    }else
    if(strcmp(submonth,"Dec")==0)
    {
        return 12;
    }
}

void currentdate()
{
    time_t ct;
    ct=time(NULL);
    char* cts;
    cts=ctime(&ct);
    printf("%s",cts);
}

// the fine calculation function
void finecalc(issuedate,issuemonth,curdate,curmonth)
{
    fflush(stdin);
    float fine=0.0;
    if((issuedate+10)<=curdate&&issuemonth==curmonth)
    {
       fine=0.0;
    }
    if((curmonth-issuemonth)<2&&(curmonth-issuemonth)!=0)
    {
        fine=((30-issuedate)+(curdate))*5;
    }
    if((curmonth-issuemonth)>2)
    {
        fine=(curmonth-issuemonth)*30*5+curdate*5;
    }

    printf("Fine to be paid: %.2f",fine);
}

int find_issue_date(dnode *head,char bi[])
{
    dnode *q;
    q=head;

    while(strcmp(q->bookid, bi)!=0 && q->next!=NULL)
    {
        q=q->next;
    }

    if(strcmp(q->bookid, bi)==0)
    {
        return (q->issuedate);
    }
    else
    {
        return -1;
    }
}

int find_issue_month(dnode *head,char bi[])
{
    dnode *q;
    q=head;

    while(strcmp(q->bookid, bi)!=0 && q->next!=NULL)
    {
        q=q->next;
    }

    if(strcmp(q->bookid, bi)==0)
    {
        return(q->issuemonth);
    }
    else
    {
        return -1;
    }
}

//Creates a new node in the issue records linked list
dnode *issue_record(char *bi,int issda,int im,dnode *head)
{
    dnode *p,*q;
    p=(dnode*)malloc(sizeof(dnode));
    strcpy(p->bookid, bi);
    p->issuedate=issda;
    p->issuemonth=im;

    if(head==NULL)
    {
        head=p;
        p->prev=NULL;
        p->next=NULL;
    }
    else
    {
        q=head;
        
        while(q->next!=NULL)
        {
            q=q->next;
        }

        q->next=p;
        p->prev=q;
        p->next=NULL;
    }

    return(head);
}

//Displays the issue records
void displayir(dnode *head)
{
    dnode *p;
    p=head;
    while(p!=NULL)
    {
        printf("Book ID:: %s\t\t",p->bookid);
        printf("Issue Day :: %d\t\t",p->issuedate);
        printf("Issue Month:: %d\n",p->issuemonth);
        p=p->next;
    }
}

//CALCULATES THE NUMBER OF TIMES A BOOK IS ISSUED ---- IT ACCEPTS THE BOOKID FOR THIS PURPOSE
int ntbe(int nbi,dnode *head)
{
    dnode *p;
    p=head;
    int count=0;

    while(p->next!=NULL)
    {
        if(p->bookid==nbi)
        {
            count++;
        }
        p=p->next;
    }

    if(p->bookid==nbi)
    {
        count++;
    }

    return count;
}

//Writes the issue records to issuerec.txt file
void writeIssueRecords(dnode *head)
{
    dnode *cursor;

    fp = fopen("issuerec.txt", "w");
    if(fp == NULL)
    {
        printf("Error\n");
    }
    else
    {
        cursor = head;
        if(START != NULL)
        {
            while(cursor != NULL)
            {
                fprintf(fp, "%s|%d|%d\n", cursor->bookid, cursor->issuedate, cursor->issuemonth);
                cursor = cursor->next;
            }
        }
    }
    fclose(fp);
}

//Reads the issue records from the file and stores it in a linked list
dnode *readIssueRecords(dnode *head)
{
    fp = fopen("issuerec.txt", "r");
    if(fp == NULL)
    {
        printf("Error\n");
    }
    else
    {
        char temp1[MAX], temp2[MAX], id[MAX];
        int ism, isdate, i, j;
        while(fscanf(fp, "%s\n", temp1) != EOF)
        {
            i = 0;
            j = 0;
            //Extract the Book ID
            while(temp1[i] != '|')
            {
                id[i] = temp1[i];
                i++;
            }
            id[i] = '\0';

            i++;
            //Extract the issue day
            while(temp1[i] != '|')
            {
                temp2[j] = temp1[i];
                i++;
                j++;
            }
            temp2[j] = '\0';
            j = 0;
            isdate = atoi(temp2);

            i++;
            //Extract the issue month
            while(temp1[i] != '\0')
            {
                temp2[j] = temp1[i];
                i++;
                j++;
            }
            temp2[j] = '\0';
            ism = atoi(temp2);
            
            //Add entry to the issue records linked list
            head = issue_record(id, isdate, ism, head);
        }
    }
    fclose(fp);
    return head;
}

int isPresent(char *id)
{
    node *cursor = START;
    int flag = 0;

    while(cursor->next != NULL)
    {
        if(strcmp(id, cursor->book.ID) == 0)
            flag = 1;
        
        cursor = cursor->next;
    }

    return flag;
}

void mainmenu()
{
    Book newBook;
    int choice;
    int isd,cd,im,cm,ism;char bi[MAX];float fineamount=0.0;
    dnode *head = NULL;

    readFromFile();
    head = readIssueRecords(head);
    do
    {
        printf("\n\n\t\t#####Main Menu#####\n\n\t\t");
        printf("1.Add Books\n\t\t2.Delete Books\n\t\t3.Issue Books\n\t\t4.Return Books\n\t\t5.Display Books\n\t\t6.Display Issue Records\n\t\t7.Exit");
        printf("\nEnter your choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: getBookData(&newBook);
                    insert(newBook);
                    break;

            case 2: printf("Enter the book ID of the book you want to delete\n");
                    fflush(stdin);
                    fgets(bi, MAX, stdin);
                    bi[strcspn(bi, "\n")] = 0; //Replaces the '\n' at the end with '\0'
                    deleteBook(bi);
                    break;

            case 3: printf("Enter the book ID\n");
                    fflush(stdin);
                    fgets(bi, MAX, stdin);
                    bi[strcspn(bi, "\n")] = 0; //Replaces the '\n' at the end with '\0'

                    //To check if the book is actually present in the database
                    if(isPresent(bi))
                    {
                        isd=datecalc();
                        im=monthcalc();
                        head=issue_record(bi,isd,im,head);
                    }
                    else
                        printf("Book not found\n");
                    
                    break;

            case 4: printf("Enter the book ID\n");
                    fflush(stdin);
                    fgets(bi, MAX, stdin);
                    bi[strcspn(bi, "\n")] = 0; //Replaces the '\n' at the end with '\0'
                    isd=find_issue_date(head, bi);
                    ism=find_issue_month(head, bi);
                    if(isd==-1)
                    {
                        printf("Book not found\n");
                    }
                    else
                    {
                        cd=datecalc();
                        cm=monthcalc();
                        printf("current date::%d\n",cd);
                        //printf("issue date:::%d\n",isd);
                        printf("current month::%d\n",cm);
                        //printf("issue month:::%d\n",ism);
                    
                        finecalc(isd,ism,cd,cm);
                    }
                    break;

            case 5: display();
                    break;
            
            case 6: displayir(head);
                    break;
            
            case 7: writeToFile();
                    writeIssueRecords(head);
                    exit(0);

            default:  printf ("\n\tPlease Enter a Valid Choice(1/2/3/4/5/6/7)");
        }
    }while(choice!=7);
}
