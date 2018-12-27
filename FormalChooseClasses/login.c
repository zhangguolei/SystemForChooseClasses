#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>
#include "functions.h"
#include "/usr/include/mysql/mysql.h"

int login( const char* f,char * no, int maxSize, int maxNumber, MYSQL *mysql, MYSQL_RES * res_ptr, MYSQL_ROW sqlrow){
         char name[MAX_SIZE+1],pawd[MAX_SIZE];
		char sel[MAX+1],select1[MAX+1],insert[MAX+1];
		time_t t;
		printf("\t\t\t User name: ");
		scanf("%s",name);
		printf("\t\t\t Password: ");
		scanf("%s",pawd);
		if(strcmp(f,"teacher")==0)
		{
			strcpy(sel,"select tno,tname,passwd from teacher where tno=");
			strcat(sel,name);
			int flag = mysql_real_query(mysql,sel,strlen(sel));
			if(flag==0)
				{
					strcpy(no,name);
					if(vertify(name,pawd,"teacher", res_ptr, mysql, sqlrow))
					{
						time(&t);
						char str[20];
						gcvt(t,19,str);
						strcpy(insert,"insert into login(lno,num,Time) values(");
						strcat(insert,str);
						strcat(insert,",'");
						strcat(insert,name);
						strcat(insert,"','");
						strcat(insert,ctime(&t));
						strcat(insert,"')");

						int re = mysql_real_query(mysql,insert,strlen(insert));
						if(!re)
						{
							printf("\t\t\t Insert successed! \n");
							printf("\t\t\t Welcome  %s! \n",name);
							return 1;
						}
						else
						{
							printf("%s\n",mysql_error(mysql));
							return 0;
						}
					}
					else
					{
					return 0;
					}
				}
		}
		else
		{
				strcpy(sel,"select sno,sname,passwd from student where sno=");
				strcat(sel,name);
				int flag=mysql_real_query(mysql,sel,strlen(sel));
				if(flag)
				{
					printf("\t\t User is not exist! \n");
				}
				else
				{
					strcpy(no,name);
					if(yanzheng(name,pawd,"student"))
					{
						//printf("dshfh...\n");
						time(&t);
						char str[20];
						gcvt(t,19,str);
						strcpy(insert,"insert into login(lno,num,Time) values(");
						strcat(insert,str);
						strcat(insert,",'");
						strcat(insert,name);
						strcat(insert,"','");
						strcat(insert,ctime(&t));
						strcat(insert,"')");
						int re = mysql_real_query(mysql,insert,strlen(insert));

						if(!re)
						{
							printf("\t\t insert successed! \n");
							printf("\t\t\t Welcome  %s!\n",name);
							return 1;
						}
						else
						{
							printf("error:%s\n",mysql_error(sql));
						}
					}
					else
						return 0;
				}
			}
}
