#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include "functions.h"
#include "/usr/include/mysql/mysql.h"

void check(char * s,char * t, MYSQL_RES * res_ptr, MYSQL* mysql, MYSQL_ROW *sqlrow, int maxNumber){
        char sel[maxNumber];
	if(strcmp(s,"teacher")==0)
	{
		strcpy(sel,"select * from teacher where tno='");
		strcat(sel,t);
		strcat(sel,"'");
		int flag=mysql_real_query(mysql,sel,strlen(sel));
		if(!flag)
		{
		//	printf("aaa...\n");
			res_ptr=mysql_use_result(mysql);
			if(res_ptr)
			{
				int count=0;
				sqlrow=mysql_fetch_row(res_ptr);
				printf("\t\t\t ID\tName\tAge\tSex\tClass\tPassword\n ");
				printf("\t\t\t");
				while(count<mysql_field_count(mysql))
				{
					printf("%s\t",sqlrow[count]);
					count++;
				}
				printf("\n");
			}
			mysql_free_result(res_ptr);
		}
	}
	else
	{
		 strcpy(sel,"select * from student where sno='");
		 strcat(sel,t);
		 strcat(sel,"'");
		 int flag;
		 flag=mysql_real_query(mysql,sel,strlen(sel));
		 if(!flag)
		 {
			 int count=0;
			 res_ptr=mysql_use_result(sql);
			 if(res_ptr)
			 {
				 sqlrow=mysql_fetch_row(res_ptr);
				 printf("\t\t\t ID\tName\tAge\tSex\tClass\tPassword\n ");
				 printf("\t\t\t");
				 while(count<mysql_field_count(sql))
				 {
					 printf("%s\t",sqlrow[count]);
					 count++;
				 }
				 printf("\n");
			 }
			 mysql_free_result(res_ptr);
		 }
		 else
		 {
			 printf("%s",mysql_error(sql));
		 }
	}return;
}
