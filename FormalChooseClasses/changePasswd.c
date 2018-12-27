#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include "functions.h"
#include "/usr/include/mysql/mysql.h"

void changePasswd(const char* name,const char * no, MYSQL_RES * res_ptr, MYSQL* mysql, MYSQL_ROW sqlrow, int maxSize, int maxNumber){
    char sel[maxNumber];
   char old_pass[maxSize];
   mysql_free_result(res_ptr);
	printf("\t Enter the old passwd: ");
	scanf("%s",old_pass);
	if(strcmp(name,"teacher")==0)
	{
		strcpy(sel,"select tno,passwd from teacher where tno=");
		strcat(sel,no);

		int flag=mysql_real_query(mysql,sel,strlen(sel));
		if(!flag)
		{
			res_ptr=mysql_use_result(mysql);
			sqlrow=mysql_fetch_row(res_ptr);

			if(strcmp(sqlrow[1],old_pass)!=0)
			{
				printf("The old passwd is uncorrect!\n");
				mysql_free_result(res_ptr);
			}
			else
			{
				mysql_free_result(res_ptr);

				char in[maxNumber];
				char new_passwd[maxSize];
				printf("\t Enter the new passwd: ");
				scanf("%s",new_passwd);
				strcpy(in,"update teacher set passwd='");
				strcat(in,new_passwd);
				strcat(in,"'");
				strcat(in,"where tno='");
				strcat(in,no);
				strcat(in,"'");
				int re= mysql_real_query(mysql,in,strlen(in));
				if(!re)
				{
					printf("Password reset successfully! \n");
				}
				else
				{
					printf("failed!\n");
				}
			}
		}
	}
	else
	{
		strcpy(sel,"select sno,passwd from student where sno='");
		strcat(sel,no);
		strcat(sel,"'");
		int flag;
		if(!(flag =mysql_real_query(mysql,sel,strlen(sel))))
		{
			res_ptr=mysql_use_result(mysql);
			&sqlrow=mysql_fetch_row(res_ptr);
			//mysql_free_result(res_ptr);

			if(strcmp(sqlrow[1],old_pass)!=0)
			{
			  	printf("The old passwd is uncorrect! \n");
				mysql_free_result(res_ptr);
			}
			else
			{
				 //ysql_free_result(res_ptr);
				char in[maxNumber];
				char new_passwd[maxSize];
				printf("\t Enter the new password: ");
				scanf("%s",new_passwd);
				strcpy(in,"update student set passwd='");
				strcat(in,new_passwd);
				strcat(in,"'");
				 mysql_free_result(res_ptr);
				int re;
				if(!(re= mysql_real_query(mysql,in,strlen(in))))
				{
					 printf("Successful! \n");
				}
			}
		}
		else
		{
			printf("%s \n",mysql_error(mysql));
		}
	}
	return;
}
