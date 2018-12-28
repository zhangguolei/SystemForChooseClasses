#include<stdio.h>
#include<stdlib.h>
#include "/usr/include/mysql/mysql.h"
#include<time.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdbool.h>
#define MAX_SIZE 20
#define MAX 500
MYSQL* sql;
MYSQL_RES * res_ptr;
MYSQL_ROW sqlrow;
void connect_()
{
	    sql=mysql_init(NULL);
		if(!sql)
		{
			printf("\t\t初始化失败！\n");
		}
		sql=mysql_real_connect(sql,"localhost","root","zy0101zy","llei",3306,NULL,0);
		if(!sql)
			printf("\t\t链接失败！\n");

		if ( mysql_set_character_set( sql, "utf8" ) ) {
           		fprintf ( stderr , "错误, %s/n" , mysql_error( sql) ) ;
        	}

}

void unconnect()
{
	    mysql_close(sql);
}
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
			 printf("\t\t用户名不正确！\n");
			 mysql_free_result(res_ptr);
			 return 0;
		}
		if(strcmp(passwd,str1)!=0)
		{
			printf("\t\tpasswd is error！\n");
			mysql_free_result(res_ptr);
			return 0;
		}
		mysql_free_result(res_ptr);
		return 1;
	}
	else
	{
		printf("\t\tuser not ex!\n");
		return 0;
	}
}

int login( const char* f,char * no)
{
	    char name[MAX_SIZE+1],pawd[MAX_SIZE];
		char sel[MAX+1],select1[MAX+1],insert[MAX+1];
		time_t t;
		printf("\t\t\t用户名：");
		scanf("%s",name);
		printf("\t\t\t密码：");
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
					//printf("aaa...\n");
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
							printf("\t\t\tinsert successed!");
							printf("\t\t\tWelcome  %s! \n",name);
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
					printf("\t\t用户不存在！\n");
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
							printf("\t\tinsert successed!");
							printf("\t\t\tWelcome  %s!\n",name);
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

void see(char * s,char * t)
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
				printf("\t\t\ttno\ttname\tage\tpasswd\n");
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
			// printf("ffff...\n");
			 int count=0;
			 res_ptr=mysql_use_result(sql);
			 if(res_ptr)
			 {
				 sqlrow=mysql_fetch_row(res_ptr);
				 printf("\tsno\t\tsname\tsage\tsex\tsclass\t\tpasswd\n");
				 printf("\t");
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
	printf("\tenter the old passwd:");
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
				printf("the old passwd is false!\n");
				mysql_free_result(res_ptr);
			}
			else
			{
				mysql_free_result(res_ptr);

				char in[MAX];
				char new_passwd[MAX_SIZE];
				printf("\tenter the new passwd:");
				scanf("%s",new_passwd);
				strcpy(in,"update teacher set passwd='");
				strcat(in,new_passwd);
				strcat(in,"'");
				strcat(in,"where tno='");
				strcat(in,no);
				strcat(in,"'");
				//printf("%s \n",in);
				int re= mysql_real_query(sql,in,strlen(in));
				if(!re)
				{
					printf("passwd reset successed!\n");
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
			  	printf("the old passwd is false!\n");
				mysql_free_result(res_ptr);
			}
			else
			{
				 //ysql_free_result(res_ptr);
				char in[MAX];
				char new_passwd[MAX_SIZE];
				printf("\tenter the new passwd:");
				scanf("%s",new_passwd);
				strcpy(in,"update student set passwd='");
				strcat(in,new_passwd);
				strcat(in,"'");
				 mysql_free_result(res_ptr);
				int re;
				if(!(re= mysql_real_query(sql,in,strlen(in))))
				{
					 printf("rechange successed!\n");
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
		printf("\t\t输入学生学号:");
		scanf("%s",sno);
		printf("\t\t输入课程号：");
		scanf("%s",cno);
		printf("\t\tenter grade：");
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
				printf("\t\t\t修改成功！\n");
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
	printf("\t\t课程号：");
	scanf("%s",cno);

	strcpy(in,"insert into select_c(sno,cno,grade) values('");
	strcat(in,sno);
	strcat(in,"','");
	strcat(in,cno);
	strcat(in,"',0)");

	if(!(flag=mysql_query(sql,in)))
	{
		printf("\t\t\t恭喜，选课成功！\n");
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
				strcat(in,"');");

		 		printf("%s \n",in);

				if(!(j=mysql_real_query(sql,in,strlen(in))))
				{
				printf("\t\t插入成功...\n");
				}
				else
				{
				printf("\t\t插入失败... %s \n",mysql_error(sql));
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
}


int main()
{
	int a,b;
	int c=1;
	int count,count1;
	char temp[MAX_SIZE];
	connect_();
	addstudent();
	printf("________________________________________________________________\n");
	printf("|\t\t\t\t选课系统\t\t\t|\n");
	printf("|\t\t\t\t1.登录\t\t\t\t|\n");
	printf("|\t\t\t\t2.退出\t\t\t\t|\n");
	printf("|_______________________________________________________________|\n");
	printf("\t\t\t\t选择:");
	scanf("%d",&a);
	printf("任意键继续......\n");
	getchar();
	getchar();

	switch(a)
	{
		case 1:
			{
				while(c)
				{
					system("clear");
					printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
					printf("|\t\t\t\t选择\n");
					printf("|\t\t\t\t1.老师\n");
					printf("|\t\t\t\t2.学生\n");
					printf("|\t\t\t\t其他退出\n");
					printf("|+++++++++++++++++++++++++++++++++++++++++++++\n");
					printf("\t\t\t\t选择:");
					scanf("%d",&b);

					switch(b)
					{
						case 1:
							if(login("teacher",temp))
							{
							//system("clear");
								while(true)
								{
									system("clear");
									printf("+++++++++++++++++++++++++++++++++++++++\n");
									printf("|\t\t\t\t选择操作\n");
									printf("|\t\t\t\t1.修改密码\n");
									printf("|\t\t\t\t2.修改成绩\n");
									printf("|\t\t\t\t3.查看基本信息\n");
									printf("|\t\t\t\t4.退出\n");
									printf("|++++++++++++++++++++++++++++++++++++++\n");
									printf("\t\t\t\t选择:");
									scanf("%d",&count1);
									switch(count1)
									{
										case 1:
											ch_passwd("teacher",temp);
											break;
										case 2:
											change_G();
											break;
										case 3:
											see("teacher",temp);
											break;
										default:
											count1=0;
											break;
									}
									if(count1==0)
									break;
									printf("任意键继续....");
									getchar();
									getchar();
								}
							}
							break;
						case 2:
							if(login("student",temp))
							{
								while(true)
								{
									system("clear");
									printf("___________________________________________\n");
									printf("|\t\t\t\t选择操作\n");
									printf("|\t\t\t\t1.修改密码\n");
									printf("|\t\t\t\t2.选课\n");
									printf("|\t\t\t\t3.查看基本信息\n");
									printf("|\t\t\t\t4.退出\n");
									printf("|___________________________________________\n");
									printf("==================:");
									scanf("%d",&count);

									switch(count)
									{
										case 1:
											ch_passwd("student",temp);
											break;
										case 2:
											choose_C(temp);
											break;
										case 3:
											see("student",temp);
											break;
										default :
											count=0;
											break;
									}
									if(count==0)
										break;
									printf("任意键继续......\n");
									getchar();
									getchar();
								}

							}
							break;
						default:
							c=0;
							break;

						printf("任意键继续......\n");
						getchar();
						getchar();
					}
				}
			}
			break;
		default:
			break;
	}
	unconnect(sql);
	return 0;
}
