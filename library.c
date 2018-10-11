/*
Summary of the code:
1. getBookData() - Function gets the details of the book from the user
2. writeToFile() - Writes the book details to a file called "data.txt"
This is the format in which the book details are written:
<Book name>|<Author>|<Book ID>
All the spaces are replaced by underscores during writing for convenience
The details are separated by '|'
For example:
Art_Of_War|Sun_Tzu|001
3. readFromFile() - Reads all the data from the "data.txt" file and adds every book to a linked list
For example:
This is the data.txt file:
"The_Art_Of_War|Sun_Tzu|001
The_God_Delusion|Some_Atheist_idk|002
Let_Us_C|Yashwant_Kanetkar|003"
readFromFile() will then create a linked list with 3 nodes that contain the details of these three books
4. mainmenu() - Displays the main menu of the program
General Instructions:
1. Please use the same variable names as everyone else, so that there's no confusion about what's doing what
2. Please use comments to describe your code like this, so that its easier to understand what's going on and there's less confusion
3. Compile and check if your files are running, before uploading them, if there's an error, make a comment at that line and mention
the problem there
4. Please use this file as the base file when writing your code, write your code in this file only
5. Update your file as soon as it gets updated on GitHub so that we have everyone's code in here and nobody's code gets deleted
6. Debugging can be hard, have patience and everything will work
7. Update the above list of functions if you add new functions to the file
Cheers! :)
*/

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
void deleteBook(Book);
void clearList();
void replaceSpaces(char *);
void replaceUnder(char *);
void display();
void getBookData(Book *);
void writeToFile();
void readFromFile();
void writeIssueRecords(dnode *head);
dnode *readIssueRecords(dnode *head);
int ntbe(int bi,dnode *head);
char* currtime();
void finecalc(int,int,int,int);
int datecalc();
int find_issue_date(dnode *head,char[MAX]);
int find_issue_month(dnode *head,char[MAX]);
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
        printf("Error\n"); //Remove this line in the final version of the code
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
        printf("Error creating a new node\n");
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

        newnode =  create(b, NULL);
        cursor->next = newnode; 
    }
}

void clearList()
{
     START= NULL;
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

    printf("fine to b paid:::::%.2f",fine);
}

int find_issue_date(dnode *head,char bi[])
{
    dnode *q;
    q=head;

    while(strcmp(q->bookid,bi)==0 && q->next!=NULL)
    {
        q=q->next;
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

    return(head);
}

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

/*
typedef struct dnode
{
    char bookid[MAX];
    int issuedate;
    int issuemonth;
    struct dnode *next,*prev;
}dnode;
*/
dnode *readIssueRecords(dnode *head)
{
    fp = fopen("issuerec.txt", "r");
    if(fp == NULL)
    {
        printf("Error\n"); //Remove this line in the final version of the code
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
            while(temp1[i] != '\0')
            {
                temp2[j] = temp1[i];
                i++;
                j++;
            }
            temp2[j] = '\0';
            ism = atoi(temp2);

            head = issue_record(id, isdate, ism, head);
        }
    }
    fclose(fp);
    return head;
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

            case 2: //Incomplete
                    break;

            case 3: printf("enter the book id\n");
                    fflush(stdin);
                    fgets(bi, MAX, stdin);
                    bi[strcspn(bi, "\n")] = 0; //Replaces the '\n' at the end with '\0'
                    isd=datecalc();
                    im=monthcalc();
                    head=issue_record(bi,isd,im,head);
                    break;

            case 4: printf("enter the bookid\n");
                    fflush(stdin);
                    fgets(bi, MAX, stdin);
                    bi[strcspn(bi, "\n")] = 0; //Replaces the '\n' at the end with '\0'
                    isd=find_issue_date(head, bi);
                    ism=find_issue_month(head, bi);
                    cd=datecalc();
                    cm=monthcalc();
                    printf("current date::%d\n",cd);
                    //printf("issue date:::%d\n",isd);
                    printf("current month::%d\n",cm);
                    //printf("issue month:::%d\n",ism);
                    if(isd==-1)
                    {
                        printf("book not found\n");
                    }

                    finecalc(isd,ism,cd,cm);
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
