#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "/usr/include/mysql/mysql.h"

void chooseClasses(MYSQL *mysql)
{
    MYSQL_RES * result;
    MYSQL_ROW row;
  //  conn = mysql_init(NULL);
    //建立与数据库的连接，如果不成功则退出
   /* if(!mysql_real_connect(mysql,"127.0.0.1","root","zy0101zy","mysql",3306,NULL,0))
    {
        printf("\nCannot access to the database!!! \n");
        return;
    }*/
    char *studentId;
    //存放用户输入的密码
    char *password = "";
    //存放查询到的密码
    char *passwordQuery;
    char *query = "select * from students where studentId='";
    //char queryForPass[200] = "select * from studentsPassword where studentId='";
    char *queryForPass = "select password from studentsPassword where studentId='";
    char *queryForClass = "select * from chooseClasses where studentId='";
    char *queryForInsertChoose = "insert into chooseClasses values(";
    char *queryForClassesInfo = "select * from classes";
    char *queryForClassesName = "select * from classes where classId='";
    char *className;
    char *classId;
    //char stuName[100];
    char *stuName;
    //int studentClassesScore=0;
    printf("************ Login in ************\n");
    //提示用户输入学号（账户），读取用户输入
    printf("Your Student ID:  ");
    scanf("%s", studentId);
    //getchar();
    //将查询语句和学生学号拼接起来
    strcat(query, studentId);
    strcat(query, "'");
    strcat(queryForPass, studentId);
    strcat(queryForPass, "'");
    strcat(queryForClass, studentId);
    strcat(queryForClass, "' and classId='");
    printf("SQL sentence: %s\n", query);
    printf("SQL sentence: %s\n", queryForPass);
    mysql_free_result(result);
    if (mysql_real_query(mysql, query, strlen(query))!= 0)
    {
        fprintf(stderr, "select fail\n");
        return;
    }
    else
    {
        if ((result = mysql_store_result(mysql)) == NULL)
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
                //再次查询数据库，查询表studentsPassword得到学生密码，再次查询前要释放上一次的数据集
                mysql_free_result(result);
                if(mysql_real_query(mysql, queryForPass, strlen(queryForPass)) != 0){
                    fprintf(stderr, "select fail\n");
                   return;
                }
                else{
                    if ((result = mysql_store_result(mysql)) == NULL)
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
                                mysql_free_result(result);

                                if(mysql_real_query(mysql, queryForClassesInfo, strlen(queryForClassesInfo))== 0){
                                        //查询结果不为空的话
                                    if((result = mysql_store_result(mysql)) != NULL){
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
                                    printf("Input the id of the class that you want to choose (input 'exit' to exit class choose):  ");
                                    scanf("%s", classId);
                                    strcat(queryForClass, classId);
                                    strcat(queryForClass, "'");

                                    mysql_free_result(result);
                                    if(mysql_real_query(mysql, queryForClass, strlen(queryForClass)) == 0){
                                            //说明该同学已经选过这门课程
                                        if((result = mysql_store_result(mysql)) != NULL){
                                            printf("You has choose this class before.\n");
                                                    continue;
                                        }
                                        //说明该同学没有选过这门课程，下面将这门课程的信息添加到数据库中去
                                        else{
                                            strcat(queryForClassesName, classId);
                                            strcat(queryForClassesName, "'");

                                            mysql_free_result(result);
                                             if(mysql_real_query(mysql, queryForClassesName, strlen(queryForClassesName))== 0){
                                                if((result = mysql_store_result(mysql)) != NULL){
                                                        row=mysql_fetch_row(result);
                                                    className = row[1];   //查询得到课程的名称，需要将它添加到选课表
                                                }
                                             }
                                             strcat(queryForInsertChoose, studentId);
                                             strcat(queryForInsertChoose, ",");
                                             strcat(queryForInsertChoose, classId);
                                             strcat(queryForInsertChoose, ",");
                                             strcat(queryForInsertChoose, stuName);
                                             strcat(queryForInsertChoose, ",");
                                             strcat(queryForInsertChoose, className);
                                             mysql_free_result(result);

                                             if(mysql_real_query(mysql, queryForInsertChoose, strlen(queryForInsertChoose)) == 0){
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
