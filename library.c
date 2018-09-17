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
#include <string.h>
#include <stdlib.h>
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
    struct node *prev;
}node;
node *START = NULL;

node *create(Book, node*);
void insert(Book);
void addBook(Book);
void deleteBook(Book);
void clearMemory();
void replaceSpaces(char *);
void replaceUnder(char *);
void display();
void getBookData(Book *);
void writeToFile(Book *);
void readFromFile();
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
    //replaceSpaces(new_book->title);

    printf("Enter the author\n");
    fgets(new_book->author, MAX, stdin);
    new_book->author[strcspn(new_book->author, "\n")] = 0;
    //replaceSpaces(new_book->author);

    printf("Enter the book ID\n");
    fgets(new_book->ID, MAX, stdin);
    new_book->ID[strcspn(new_book->ID, "\n")] = 0;
}

void addBook(Book newBook)
{
    insert(newBook);
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
        replaceSpaces(b->title);
        replaceSpaces(b->author);
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

/*void clearMemory()
 {
     node *cursor, *temp;
     while(START != NULL)
     {
         cursor = START;
         while(cursor->next != NULL)
         {
             cursor = cursor->next;
         }
         temp = cursor->prev;
         if(temp != NULL)
         {
             temp->next = NULL;
         }

         free(cursor);
     }
 }*/

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

void mainmenu()
{
    Book newBook;
    int choice;

    readFromFile();
    do
    {
        printf("\n\n\t\t#####Main Menu#####\n\n\t\t");
        printf("1.Add Books\n\t\t2.Delete Books\n\t\t3.Issue Books\n\t\t4.Display\n\t\t5.Exit");
        printf("\nEnter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: getBookData(&newBook);
                    addBook(newBook);
                    break;

            case 2: //Incomplete
                    break;

            case 3: //Sneha add you functions here
                    break;

            case 4: readFromFile();
                    display();
                    break;

            case 5: //writeToFile();
                    //clearMemory();
                    exit(0);

            default:  printf ("\n\tPlease Enter a Valid Choice(1/2/3/4)");
       }
   }while(choice!=5);
}
