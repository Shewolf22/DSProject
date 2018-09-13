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
}node;
node *START = NULL;

node *create(Book, node*);
void insert(Book);
void replaceSpaces(char *);
void replaceUnder(char *);
void display();
void getBookData(Book *);
void writeToFile(Book *);
void readFromFile();

int main()
{
    Book new;
    char c = 'y';
    int sw;
    printf("Yay I made something lmao\n");
    printf("1.Add Book\n2.Display Books\n");
    scanf("%d", &sw);

    switch(sw)
    {
        case 1: do
                {
                    printf("Enter the details yo\n");
                    getBookData(&new);
                    writeToFile(&new);
                    printf("Do you want to continue? [y\\n]");
                    scanf("%c", &c);
                    //clrscr();
                }while(c != 'n');
                break;
        case 2: readFromFile();
                display();
                break;
        default: printf("Wrong choice m8\n");
    }

    return 0;
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
