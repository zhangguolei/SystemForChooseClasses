#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void chooseClasses(MYSQL *conn, MYSQL_RES *result, MYSQL_ROW row, char *stu)
{
  //  conn = mysql_init(NULL);
    //建立与数据库的连接，如果不成功则退出
    //if(!mysql_real_connect(conn,"localhost","root","zy0101zy","mysql",3306,NULL,0))
  //  {
      //  printf("\nCannot access to the database!!! \n");
      //  return;
   // }

    //char *studentId = (char *)malloc(sizeof(studentId)*50);
    //存放用户输入的密码
    char password[50] = "";
    //存放查询到的密码
    char *passwordQuery;
    char *query = "select * from students where studentId='";
    //char queryForPass[200] = "select * from studentsPassword where studentId='";
    char *queryForPass = "select * from studentsPassword where studentId='";
    char *queryForClass = "select * from chooseClasses where studentId='";
    char *queryForInsertChoose = "insert into chooseClasses values(";
    char *queryForClassesInfo = "select * from classes";
    char *queryForClassesName = "select * from classes where classId='";
    char *className;
    char *classId = "";
    //char stuName[100];
    char *stuName;
    //int studentClassesScore=0;
    printf("************ Login in ************\n");
    //提示用户输入学号（账户），读取用户输入
    printf("Your Student ID:  ");
    scanf("%s", stu);
   //gets(studentId);
    printf("Your Student ID:  ");
    printf("%s", stu);
    //getchar();
    //将查询语句和学生学号拼接起来
    strcat(query, stu);
    strcat(query, "'");
    strcat(queryForPass, stu);
    strcat(queryForPass, "'");
    strcat(queryForClass, stu);
    strcat(queryForClass, "' and classId='");
    printf("SQL sentence: %s\n", query);
    printf("SQL sentence: %s\n", queryForPass);
    if (mysql_real_query(conn, query, strlen(query)) != 0)
    {
        fprintf(stderr, "select fail\n");
        return;
    }
    else
    {
        if ((result = mysql_store_result(conn)) == NULL)
        {
            fprintf(stderr, "save result set failure!\n");
            printf("Sorry, we cannot find your ID");
            return;
        }
        else
        {
            if ((row = mysql_fetch_row(result)) != NULL)
            {
                //表示有此学号的学生，继续输入密码
               // studentClassesScore = row[5];
                stuName = row[1];
                printf("Your password:  ");
                scanf("%s", password);
                printf("\n");
                //再次查询数据库，查询表studentsPassword得到学生密码
                if(mysql_query(conn, queryForPass) != 0){
                    fprintf(stderr, "select fail\n");
                   return;
                }
                else{
                    if ((result = mysql_store_result(conn)) == NULL)
                    {
                        fprintf(stderr, "save result set failure!\n");
                        printf("Sorry, your password is wrong.");
                        return;
                    }
                    else{
                        if((row = mysql_fetch_row(result))!=NULL){
                            passwordQuery = row[1];
                            if(passwordQuery == password){
                                printf("You are allowed!\n\n");
                                printf("*************Classes List**************");
                                if(mysql_query(conn, queryForClassesInfo) == 0){
                                        //查询结果不为空的话
                                    if((result = mysql_store_result(conn)) != NULL){
                                        if(mysql_num_rows(result))
                                        {
                                            //将课程信息循环打印出来
                                            printf("id\tname\tcollege\tteachers\tscore\thours\tsemester\n");
                                            while((row=mysql_fetch_row(result)))
                                                {printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6]);}
                                        }
                                else {printf("no classes yet!\n"); return;}
                                    }
                                    else {printf("select error!\n"); return;}
                                }
                                else {printf("select error!\n"); return;}

                                printf("\n\n");
                                while(strcmp(classId, "exit")){
                                    printf("Input the number of the class that you want to choose (input 'exit' to exit class choose):  ");
                                    scanf("%s", classId);
                                    strcat(queryForClass, classId);
                                    strcat(queryForClass, "'");
                                    if(mysql_query(conn, queryForClass) == 0){
                                            //说明该同学已经选过这门课程
                                        if((result = mysql_store_result(conn)) != NULL){
                                            printf("You has choose this class.");
                                                    continue;
                                        }
                                        //说明该同学没有选过这门课程，下面将这门课程的信息添加到数据库中去
                                        else{
                                            strcat(queryForClassesName, classId);
                                            strcat(queryForClassesName, "'");
                                             if(mysql_query(conn, queryForClassesName) == 0){
                                                if((result = mysql_store_result(conn)) != NULL){
                                                        row=mysql_fetch_row(result);
                                                    className = row[1];
                                                }
                                             }
                                             strcat(queryForInsertChoose, stu);
                                             strcat(queryForInsertChoose, ",");
                                             strcat(queryForInsertChoose, classId);
                                             strcat(queryForInsertChoose, ",");
                                             strcat(queryForInsertChoose, stuName);
                                             strcat(queryForInsertChoose, ",");
                                             strcat(queryForInsertChoose, className);
                                             if(mysql_query(conn, queryForInsertChoose) == 0){
                                                printf("Add your choose information successfully!\n");
                                             }
                                             else {
                                                printf("Add your choose information failed!\n");
                                                continue;
                                             }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


int main()
{
    MYSQL* mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char stuId[50];
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
         case 1 : chooseClasses(mysql, res, row, stuId); break;
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

