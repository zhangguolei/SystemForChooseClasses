#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<time.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdbool.h>
#include "functions.h"
#include "/usr/include/mysql/mysql.h"
#define MAX_SIZE 20
#define MAX 500
/*void connect_()
{
	    sql=mysql_init(NULL);
		if(!sql)
		{
			printf("\t\t Initialize failed! \n");
		}
		//printf("111\n");
		sql=mysql_real_connect(sql,"localhost","root","zy0101zy","mysql",0,NULL,0);
		if(!sql)
			printf("\t\t Connect failed! \n");
}

void unconnect()
{
	    mysql_close(sql);
}
//vertify()
int yanzheng(char* name,char*  passwd,const char* type)
{
	char str[20]="";
	char str1[20]="";
	int flag=0;
	res_ptr=mysql_use_result(sql);
	if(res_ptr!=NULL)
	{
		while((sqlrow=mysql_fetch_row(res_ptr)))
		{
			strcpy(str,sqlrow[0]);
			strcpy(str1,sqlrow[2]);
			flag=0;
		}
		//printf("%s %s %s %s\n",str,str1,name,passwd);
		if(strcmp(name,str)!=0)
		{
			 printf("\t\t User name not correct! \n");
			 mysql_free_result(res_ptr);
			 return 0;
		}
		if(strcmp(passwd,str1)!=0)
		{
			printf("\t\t password is error! \n");
			mysql_free_result(res_ptr);
			return 0;
		}
		mysql_free_result(res_ptr);
		return 1;
	}
	else
	{
		printf("\t\t user not exist! \n");
		return 0;
	}
}

int login( const char* f,char * no)
{
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
			int flag = mysql_real_query(sql,sel,strlen(sel));
			if(flag==0)
				{
					strcpy(no,name);
					if(yanzheng(name,pawd,"teacher"))
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

						int re = mysql_real_query(sql,insert,strlen(insert));
						if(!re)
						{
							printf("\t\t\t Insert successed! \n");
							printf("\t\t\t Welcome  %s! \n",name);
							return 1;
						}
						else
						{
							printf("%s\n",mysql_error(sql));
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
				int flag=mysql_real_query(sql,sel,strlen(sel));
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
						int re = mysql_real_query(sql,insert,strlen(insert));

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

void check(char * s,char * t)
{
	char sel[MAX];

	if(strcmp(s,"teacher")==0)
	{
		strcpy(sel,"select * from teacher where tno='");
		strcat(sel,t);
		strcat(sel,"'");
		int flag=mysql_real_query(sql,sel,strlen(sel));
		if(!flag)
		{
		//	printf("aaa...\n");
			res_ptr=mysql_use_result(sql);
			if(res_ptr)
			{
				int count=0;
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
	}
	else
	{
		 strcpy(sel,"select * from student where sno='");
		 strcat(sel,t);
		 strcat(sel,"'");
		 int flag;
		 flag=mysql_real_query(sql,sel,strlen(sel));
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
	}
}
void ch_passwd(const char* name,const char * no)
{
	char sel[MAX];
   char old_pass[MAX_SIZE];
	printf("\t Enter the old passwd: ");
	scanf("%s",old_pass);
	if(strcmp(name,"teacher")==0)
	{
		strcpy(sel,"select tno,passwd from teacher where tno=");
		strcat(sel,no);

		int flag=mysql_real_query(sql,sel,strlen(sel));
		if(!flag)
		{
			res_ptr=mysql_use_result(sql);
			sqlrow=mysql_fetch_row(res_ptr);

			if(strcmp(sqlrow[1],old_pass)!=0)
			{
				printf("The old passwd is uncorrect!\n");
				mysql_free_result(res_ptr);
			}
			else
			{
				mysql_free_result(res_ptr);

				char in[MAX];
				char new_passwd[MAX_SIZE];
				printf("\t Enter the new passwd: ");
				scanf("%s",new_passwd);
				strcpy(in,"update teacher set passwd='");
				strcat(in,new_passwd);
				strcat(in,"'");
				strcat(in,"where tno='");
				strcat(in,no);
				strcat(in,"'");
				int re= mysql_real_query(sql,in,strlen(in));
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
		if(!(flag =mysql_real_query(sql,sel,strlen(sel))))
		{
			res_ptr=mysql_use_result(sql);
			sqlrow=mysql_fetch_row(res_ptr);
			//mysql_free_result(res_ptr);

			if(strcmp(sqlrow[1],old_pass)!=0)
			{
			  	printf("The old passwd is uncorrect! \n");
				mysql_free_result(res_ptr);
			}
			else
			{
				 //ysql_free_result(res_ptr);
				char in[MAX];
				char new_passwd[MAX_SIZE];
				printf("\t Enter the new password: ");
				scanf("%s",new_passwd);
				strcpy(in,"update student set passwd='");
				strcat(in,new_passwd);
				strcat(in,"'");
				 mysql_free_result(res_ptr);
				int re;
				if(!(re= mysql_real_query(sql,in,strlen(in))))
				{
					 printf("Successful! \n");
				}
			}
		}
		else
		{
			printf("%s \n",mysql_error(sql));
		}
	}
}


void change_G()
{
	char sno[MAX_SIZE];
	char cno[MAX_SIZE];
	char up[MAX];
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

			if(!(flag=mysql_real_query(sql,up,strlen(up))))
			{
				printf("\t\t\t Update Successfully! \n");
			}
			else
			{
				printf("%s\n ",mysql_error(sql));
			}
		}
	}
}
void choose_C(const char* sno)
{
	char cno[MAX_SIZE];
	char in[MAX];
	int flag;
	printf("\t\t Course ID: ");
	scanf("%s",cno);

	strcpy(in,"insert into select_c(sno,cno,grade) values('");
	strcat(in,sno);
	strcat(in,"','");
	strcat(in,cno);
	strcat(in,"',0)");

	if(!(flag=mysql_real_query(sql,in, strlen(sql))))
	{
		printf("\t\t Choose the course successfully! \n");
	}
	else
	{
		printf("%s",mysql_error(sql));
	}
}

void addstudent()
{
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
				if(!(j=mysql_real_query(sql,in,strlen(in))))
				{
				printf("\t\t Insert Successfully! \n");
				}
				else
				{
				printf("\t\t Insert Failed! %s \n",mysql_error(sql));
				}
			}
			else if(ch[0]==' ')
			{
				strcpy(stu[i],buf);
				strcpy(buf,"");
				//printf("%s \n",stu[i]);
				i++;
			}
			else
			{
				strcat(buf,ch);
			}
		}
	}
}*/

int main()
{

    MYSQL* sql;
    MYSQL_RES * res_ptr;
    MYSQL_ROW sqlrow;

	int a,b;
	int c=1;
	int count,count1;
	char temp[MAX_SIZE];
	connectToMysql(sql);
	addStudent(sql);
	printf("************************************************\n");
	printf("***** The System For Classes Choosing *****\n");
	printf("\t\t 1.Log in\t\t\t\t\n");
	printf("\t\t 2.Log out\t\t\t\t\n");
	printf("Input any number to exit......\n");
	printf("***********************************************\n");
	printf("Select Please: ");
	scanf("%d",&a);
	getchar();
	getchar();

	switch(a)
	{
		case 1:
			{
				while(c)
				{
					system("clear");
					printf("**********************************************\n");
					printf("\t\t\t  Select Please\n");
					printf("\t\t\t\t1.Teacher\n");
					printf("\t\t\t\t2.Student\n");
					printf("\t\t\t Input any other numbers to exit... \n");
					printf("*********************************************\n");
					printf("\t\t\t\t Choose:");
					scanf("%d",&b);

					switch(b)
					{
						case 1:
							if(login("teacher",temp, MAX_SIZE, MAX, sql, res_ptr, sqlrow))
							{
								while(true)
								{
									system("clear");
									printf("*********************************\n");
									printf("\t\t\t Select Operation Please \n");
									printf("\t\t\t 1. Change Password\n");
									printf("\t\t\t 2. Change Student's Grade\n");
									printf("\t\t\t 3. Looking basic Information\n");
									printf("\t\t\t 4.Exit \n");
									printf("*********************************\n");
									printf("\t\t\t Select: ");
									scanf("%d",&count1);
									switch(count1)
									{
										case 1:
											changePasswd("teacher",temp, res_ptr, sql, sqlrow, MAX_SIZE, MAX);
											break;
										case 2:
											changeGrade(sql, MAX_SIZE, MAX);
											break;
										case 3:
											check("teacher",temp, res_ptr, sql, sqlrow, MAX);
											break;
										default:
											count1=0;
											break;
									}
									if(count1==0)
									break;
									printf("Input any number to exit......");
									getchar();
									getchar();
								}
							}
							break;
						case 2:
							if(login("student",temp, MAX_SIZE, MAX, sql, res_ptr, sqlrow))
							{
								while(true)
								{
									system("clear");
									printf("**********************************************\n");
                            printf("|\t\t\t\t Select Please\n");
                            printf("|\t\t\t\t1.Teacher\n");
                            printf("|\t\t\t\t2.Student\n");
                            printf("|\t\t\t\t Input any other numbers to exit... \n");
                            printf("|*********************************************\n");
                            printf("\t\t\t\t Choose:");
									scanf("%d",&count);

									switch(count)
									{
										case 1:
											changePasswd("student",temp, res_ptr, sql, sqlrow, MAX_SIZE, MAX);
											break;
										case 2:
											chooseClass(temp, sql, MAX_SIZE, MAX);
											break;
										case 3:
											check("student",temp, res_ptr, sql, sqlrow, MAX);
											break;
										default :
											count=0;
											break;
									}
									if(count==0)
										break;
									printf("Input any number to exit......\n");
									getchar();
									getchar();
								}

							}
							break;
						default:
							c=0;
							break;

						printf("Input any number to exit......\n");
						getchar();
						getchar();
					}
				}
			}
			break;
		default:
			break;
	}
	disConnectToMysql(sql);
	return 0;
}
