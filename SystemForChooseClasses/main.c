#include <stdio.h>
#include <stdlib.h>

int main()
{
    int chooseStatus=0;
    printf("*******************************************************\n");
    printf("************* Welcome to class choose system *************\n\n");
    printf("********************* FUNCTIONS **********************\n");
    printf("***************** 1.  Choose Classes *********************\n");
    printf("***************** 2.  Add Student's Information ************\n");
    printf("***************** 3.  Add Teacher's Information ************\n");
    printf("***************** 4.  Add Class's Information ***************\n");
    printf("***************** 5.  Exit The System! *********************\n");
    printf("*******************************************************\n\n");
    while(true){
         printf("Choose function please(input the function's number):  ");
         scanf("%d", &chooseStatus);
         if(chooseStatus==5) break;
         switch(chooseStatus){
         case 1 : chooseClasses(); break;
         case 2 : addStudent(); break;
         case 3 : addTeacher(); break;
         case 4 : addClass(); break;
         default:
             printf("No illegal number!");
             putchar('\a');
    }
}
   return 0;
