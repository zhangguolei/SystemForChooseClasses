#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include "functions.h"
#include "/usr/include/mysql/mysql.h"

void changeGrade(MYSQL* mysql, int maxSize, int maxNumber){
        char sno[maxSize];
	char cno[maxSize];
	char up[maxNumber];
	double grade;
	int flag;
	while(true)
	{
		printf("\t\t Input the student ID: ");
		scanf("%s",sno);
		printf("\t\t Input the course ID: ");
		scanf("%s",cno);
		printf("\t\t Enter the grade: ");
		scanf("%lf",&grade);
		if(grade<0)
		{
		  break;
		}
		else
		{
			char str[5];
			gcvt(grade,4,str);
			//printf("%s\n",str);
			strcpy(up,"update select_c set grade=");
			strcat(up,str);
			strcat(up," where sno='");
			strcat(up,sno);
			strcat(up,"' and cno='");
			strcat(up,cno);
			strcat(up,"'");
			if(!(flag=mysql_real_query(mysql,up,strlen(up))))
			{
				printf("\t\t\t Update Successfully! \n");
			}
			else
			{
				printf("%s\n ",mysql_error(mysql));
			}
		}
	}
	return;
}
