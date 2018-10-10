#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define finerate 5
#define MAX 100
FILE *fp;

typedef struct book{
    char title[MAX];
    char author[MAX];
    char ID[MAX];
    //insert the issue record linked list node here later lmao
}Book;
//This is a temporary linked list to store the data read from the data.txt file because idk shit about trees

typedef struct node{
    Book book;
    struct node *next;
}node;
node *START = NULL;

typedef struct dnode   // a doubly linked list
        {
           char bookid[MAX];
           int issuedate;
           int issuemonth;
           struct dnode *next,*prev;
        }dnode;

dnode *issue_record(char *bi,int issda,int ism,dnode *head);
int ntbe(int bi,dnode *head);
char* currtime();
void finecalc(int,int,int,int);
int datecalc();
int find_issue_date(dnode *head,char[MAX]);
int find_issue_month(dnode *head,char[MAX]);

node *create(Book, node*);
void insert(Book);
void replaceSpaces(char *);
void replaceUnder(char *);
void display();
void getBookData(Book *);
void writeToFile(Book *);
void readFromFile();
int monthcalc();
void displayir(dnode *head);
int main()

{
    int isd,cd,im,cm,ism;char bi[MAX];float fineamount=0.0;
    dnode *head = NULL;
    Book new;
    char c = 'y';
    int sw;
    do
    {
    printf("Yay I made something lmao\n");
    printf("1.Add Book\n2.Display Books\n3.Issue Books\n4.return books\n5.display issue records\n");
    scanf("%d", &sw);
    switch(sw)
    {
        case 1: printf("Enter the details yo\n");
                getBookData(&new);
                writeToFile(&new);
                printf("Do you want to continue? [y\\n]");
                scanf("%c", &c);
                break;
        case 2: readFromFile();
                display();
                break;
        case 3: printf("enter the book id\n");
                fflush(stdin);
                fgets(bi, MAX, stdin);
                isd=datecalc();
                im=monthcalc();
                head=issue_record(bi,isd,im,head);
                break;
        case 4: printf("enter the bookid\n");
                fflush(stdin);
                fgets(bi, MAX, stdin);
                isd=find_issue_date(head, bi);
                ism=find_issue_month(head, bi);
                cd=datecalc();
                cm=monthcalc();
                printf("current date::%d\n",cd);
                printf("issue date:::%d\n",isd);
                printf("current month::%d\n",cm);
                printf("issue month:::%d\n",ism);

                if(isd==-1)
                {
                    printf("book not found\n");
                }
                finecalc(isd,ism,cd,cm);
                break;
        case 5:
            displayir(head);
            break;

        default: printf("Wrong choice m8\n");
    }
    }while(c != 'n');
    return 0;
}

int datecalc()
{       int dd;
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

void finecalc(issuedate,issuemonth,curdate,curmonth)               // the fine calculation function
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

   printf("fine to b paid:::::%f",fine);
}

int find_issue_date(dnode *head,char bi[])
{    dnode *q;
    q=head;
    while(strcmp(q->bookid,bi)==0 && q->next!=NULL)
    {        q=q->next;
    }
    if(strcmp(q->bookid,bi)==0)
    {
        return (q->issuedate);
    }
    else if(q==NULL)
    {
        return -1;
    }

}

int find_issue_month(dnode *head,char bi[])
{
    dnode *q;
    q=head;
    while(strcmp(q->bookid,bi)==0 && q->next!=NULL)
    {
        q=q->next;

    }
    if(strcmp(q->bookid,bi)==0)
    {
        return (q->issuemonth);
    }
    else if(q==NULL)
    {
        return -1;
    }
}

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
        return (head);
    }
void displayir(dnode *head)
{
    dnode *p;
    p=head;
    while(p!=NULL)
    {
            printf("book id::%s\n",p->bookid);
            printf("issue date ::%d\n",p->issuedate);
            printf("issue month::%d\n",p->issuemonth);
            p=p->next;

    }

}

int ntbe(int nbi,dnode *head)    //THIS FN CALCULATES THE NUMBER OF TIMES A BOOK IS ISSUES ----IT ACCEPTS THE BOOKID FOR THIS PURPOSE
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

//Gets the book details from user
void getBookData(Book *new_book)
{
    fflush(stdin); //Flush the stdin so that no garbage value gets picked up
    printf("Enter the book title\n");
    fgets(new_book->title, MAX, stdin);
    new_book->title[strcspn(new_book->title, "\n")] = 0; //Replaces the \n character at the end with \0
    replaceSpaces(new_book->title);
    printf("Enter the author\n");
    fgets(new_book->author, MAX, stdin);
    new_book->author[strcspn(new_book->author, "\n")] = 0;
    replaceSpaces(new_book->author);
    printf("Enter the book ID\n");
    fgets(new_book->ID, MAX, stdin);
    new_book->ID[strcspn(new_book->ID, "\n")] = 0;
}

//Writes the book details to data.txt

void writeToFile(Book *b)
{
    fp = fopen("data.txt", "a");
    if(fp == NULL)
    {
        printf("Error\n");
    }
    else
    {
        fprintf(fp, "%s|%s|%s\n", b->title, b->author, b->ID);
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

node* create(Book b,node* next)
{
    node* new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("Error creating a new node.\n");
        exit(0);
    }
    new_node->book = b;
    new_node->next = next;

    return new_node;
}

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
        newnode = create(b, NULL);
        cursor->next = newnode;
    }
}

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
