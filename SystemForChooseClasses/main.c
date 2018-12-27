#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "functions.h"
#include "/usr/include/mysql/mysql.h"

/*void addStudent(){
    char pass[20] = "123456";
    char input[20];
    printf("please input the pass code:  ");
    scanf("%s", input);
    if(!strcmp(input, pass)){
        printf("ok!\n");
    }
    else printf("fail!\n");
    return;
}*/

void print1(){
   printf("hello1\n");
   }
   void print2(){
   printf("hello2\n");
   }
   void print3(){
   printf("hello3\n");
   }
   void print4(){
   printf("hello4\n");
   }

int main()
{
    MYSQL* mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql=mysql_init(NULL);
		if(!mysql)
		{
			printf("\t\t初始化失败！exit system......\n");
			return -1;
		}
		mysql=mysql_real_connect(mysql,"localhost","root","zy0101zy","mysql",3306,NULL,0);
		if(!mysql){
            printf("\t\t链接失败！\n");
            return -1;
		}

        /*char query[50] = "select * from testTable where id=3";
        char query2[50] = "insert into testTable values(5, 30, 'm', 'NWAFU')";
        mysql_real_query(mysql, query, strlen(query));     //对数据库进行操作
        res = mysql_store_result(mysql);
        mysql_free_result(res);
        mysql_real_query(mysql, query2, strlen(query2));*/


    int chooseStatus=0;
    //bool flag=true;
    printf("*******************************************************\n");
    printf("************* Welcome to class choose system *************\n\n");
    printf("********************* FUNCTIONS **********************\n");
    printf("***************** 1.  Choose Classes *********************\n");
    printf("***************** 2.  Add Student's Information ************\n");
    printf("***************** 3.  Add Teacher's Information ************\n");
    printf("***************** 4.  Add Class's Information ***************\n");
    printf("***************** 5.  Exit The System! *********************\n");
    printf("*******************************************************\n\n");

    //连接数据库，初始化三个变量

     while(1){
         printf("Choose function please(input the function's number):  ");
         scanf("%d", &chooseStatus);
         if(chooseStatus==5) break;
         else{
            switch(chooseStatus){
         case 1 : chooseClasses(); break;
         case 2 : print2(); break;
         case 3 : print3(); break;
         case 4 : print4(); break;
         default:
             printf("No illegal number!");
    }
         }

}
   return 0;}



/**/

