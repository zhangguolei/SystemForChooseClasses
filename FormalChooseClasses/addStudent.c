#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include "functions.h"
#include "/usr/include/mysql/mysql.h"

void addStudent(MYSQL *mysql){
        FILE* fd;
	char buf[50]="";
	int i=0,j=0;
	char ch[2];
	char stu[6][50];
	char in[MAX];
	if((fd=fopen("student.txt","r"))==NULL)
	{
		perror("open file Error!");
		return;
	}
	else
	{
		while((ch[0]=fgetc(fd))!=EOF)
		{
			printf("%c",ch[0]);
			if(ch[0]=='\n')
			{
				strcpy(stu[i],buf);
				strcpy(buf,"");
				i=0;
				strcpy(in,"insert into student(sno,sname,age,sex,sclass,passwd) values('");
				strcat(in,stu[0]);
				strcat(in,"','");
				strcat(in,stu[1]);
				strcat(in,"',");
				strcat(in,stu[2]);
				strcat(in,",'");
				strcat(in,stu[3]);
				strcat(in,"','");
				strcat(in,stu[4]);
				strcat(in,"','");
				strcat(in,stu[5]);
				strcat(in,"')");
			//	printf("%s \n",in);
				if(!(j=mysql_real_query(mysql,in,strlen(in))))
				{
				printf("\t\t Insert Successfully! \n");
				}
				else
				{
				printf("\t\t Insert Failed! %s \n",mysql_error(mysql));
				}
			}
			else if(ch[0]==' ')
			{
				strcpy(stu[i],buf);
				strcpy(buf,"");
				i++;
			}
			else
			{
				strcat(buf,ch);
			}
		}
	}return;
}
