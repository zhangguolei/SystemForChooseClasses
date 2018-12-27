#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include "functions.h"
#include "/usr/include/mysql/mysql.h"

void chooseClass(const char* sno, MYSQL *mysql, int maxSize, int maxNumber){
    char cno[maxSize];
	char in[maxNumber];
	int flag;
	printf("\t\t Course ID: ");
	scanf("%s",cno);

	strcpy(in,"insert into select_c(sno,cno,grade) values('");
	strcat(in,sno);
	strcat(in,"','");
	strcat(in,cno);
	strcat(in,"',0)");

	if(!(flag=mysql_real_query(mysql,in, strlen(sql))))
	{
		printf("\t\t Choose the course successfully! \n");
	}
	else
	{
		printf("%s",mysql_error(mysql));
	}
	return;
}
