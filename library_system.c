#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int main()
{
   clrscr();
   printf("\n\n\n\t\t\tLibrary Management System\n\n\n\n\n\t\t\t\t\t\t\t");
   printf("\nPress Any Key To Continue");
   getch();
   mainmenu();
   return 0; 
}

void mainmenu()
{
   int choice;
   do{
       printf("\n\n\t\t#####Main Menu#####\n\n\t\t\t\t\t\t\t");
       printf("1.Add Book\n\t\t\t\t\t\t\t2.Delete Book\n\t\t\t\t\t\t\t3.Issue Book\n\t\t\t\t\t\t4.Exit");
       scanf("%d",&choice);
       switch(choice)
       {
           case 1: do
                    {
                        Add_book();
                    
                        printf("\n\n\n\t\t\tDo you want to continue? [y\\n]");
                        scanf("%c", &c);
                    }while(c!='n'); 
                
                
                    break;
           case 2: do
		            {
						
						Delete_book();
						printf("\n\n\n\t\t\tDo you want to continue? [y\\n]");
                        scanf("%c", &c);

					}while(c!='n');

					break;
		   case 3: do
		            {
						Issue_book();
                        printf("\n\n\n\t\t\tDo you want to continue? [y\\n]");
                        scanf("%c", &c);

                      

					}			
                    break;
					 
		
                
                      
        

       }
   }while(choice<=3);
  
}