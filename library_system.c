#include<stdio.h>
#include<conio.h>
void mainmenu();
void Add_book();
void Delete_book();
void Issue_book();
int main()
{
   
   printf("\n\n\n\t*******Library Management System*******\n\n\t\t");
   printf("Go To Main Menu");
   printf("\nPress Any Key To Continue....");
   getch();
   mainmenu();
   return 0; 
}

void mainmenu()
{
   int choice;
   char c;
   do{
       printf("\n\n\t\t#####Main Menu#####\n\n\t\t");
       printf("1.Add Books\n\t\t2.Delete Books\n\t\t3.Issue Books\n\t\t4.Exit");
       printf("\nEnter your choice:");
       scanf("%d",&choice);
       switch(choice)
       {
           case 1:
                    
           case 2:
					
           case 3: 
                
           case 4:   exit(0);
		   
           default:  printf ("\n\tPlease Enter a Valid Choice(1/2/3/4)");
       }
   }while(choice!=4);
  
}


