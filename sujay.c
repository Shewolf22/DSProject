#include <stdio.h>
#include <conio.h>
#include <string.h>
#define MAX 100

FILE *fp;

typedef struct book{
    char title[MAX];
    char author[MAX];
    char ID[MAX];
    //insert the issue record linked list node here later lmao
}Book;

void getBookData(Book *);
void writeToFile(Book *);

int main()
{
    Book new;
    char c = 'y';
    printf("Yay I made something lmao\n");
    do
    {
        printf("Enter the details yo\n");
        getBookData(&new);
        writeToFile(&new);
        printf("Do you want to continue? [y\\n]");
        scanf("%c", &c);
    }while(c != 'n');

    return 0;
}

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
