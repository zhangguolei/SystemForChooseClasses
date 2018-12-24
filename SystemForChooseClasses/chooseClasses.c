#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "mysql.h"

void chooseClasses()
{
    MYSQL conn;
    int res;
    MYSQL_RES * result;
    MYSQL_ROW row;
    //mysql_init(&conn);
    //建立与数据库的连接，如果不成功则退出
    if(!mysql_real_connect(&conn,"127.0.0.1","root","123456","ChooseClassSystem",3306,NULL,0))
    {
        printf(mysql_error(&mysql));
        printf("\nCannot access to the database!!!\n");
        system("pause");
        exit(-1);
    }

    char studentId[80];
    //存放用户输入的密码
    char password[80];
    //存放查询到的密码
    char passwordQuery[80];
    char query[200] = "select * from students where studentId='";
    char queryForPass[200] = "select * from studentsPassword where studentId='";
    char queryForClassesInfo[200] = "select * from classes";
    printf("************ Login in ************\n");
    //提示用户输入学号（账户），读取用户输入
    printf("Your Student ID:  ");
    scanf("%s", studentId);
    getchar();
    //将查询语句和学生学号拼接起来
    strcat(query, studentId);
    strcat(query, "'");
    strcat(queryForPass, studentId);
    strcat(queryForPass, "'");
    printf("SQL sentence: %s\n", query);
    printf("SQL sentence: %s\n", queryForPass);

    if (mysql_query(&conn, query) != 0)
    {
        fprintf(stderr, "select fail\n");
        exit(1);
    }
    else
    {
        if ((result = mysql_store_result(&conn)) == NULL)
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
                printf("Your password:  ");
                scanf("%s", password);
                printf("\n");
                //再次查询数据库，查询表studentsPassword得到学生密码
                if(mysql_query(&conn, queryForPass) != 0){
                    fprintf(stderr, "select fail\n");
                    exit(1);
                }
                else{
                    if ((result = mysql_store_result(&conn)) == NULL)
                    {
                        fprintf(stderr, "save result set failure!\n");
                        printf("Sorry, we cannot find your password");
                        return;
                    }
                    else{
                        if((row = mysql_fetch_row(result))!=NULL){
                            passwordQuery = row[1];
                            if(passwordQuery == password){
                                printf("You are allowed!\n\n");
                                printf("*************Classes List**************");
                                if(mysql_query(&conn, queryForClassesInfo) == 0){
                                        //查询结果不为空的话
                                    if((result = mysql_store_result(&conn)) != NULL){
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

                                printf("\n\n")
                            }
                        }
                    }
                }
            }
        }
    }

}
