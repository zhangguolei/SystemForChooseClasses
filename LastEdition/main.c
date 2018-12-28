#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdbool.h>
#include "/usr/include/mysql/mysql.h"
#define MAX_SIZE 20
#define MAX 500
MYSQL *mysql;
MYSQL_RES *res;
MYSQL_ROW row;
int login( const char* f,char * no)
{
     char name[MAX_SIZE+1],pawd[MAX_SIZE];
  char sel[MAX+1],select1[MAX+1],insert[MAX+1];
  time_t t;
  printf("\t\t User ID: ");
  scanf("%s",name);
  printf("\t\t Password: ");
  scanf("%s",pawd);
  if(strcmp(f,"teacher")==0)
  {
   strcpy(sel,"select tno,tname,passwd from teacher where tno=");
   strcat(sel,name);
   int flag = mysql_real_query(mysql,sel,strlen(sel));
   if(flag==0)
    {
     strcpy(no,name);
     if(vertify(name,pawd,"teacher"))
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
       //printf("\t\t\t Insert successfully!\n");
       printf("\t Welcome you %s! \n",name);
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
     printf("\t\t User isn't exist! \n");
    }
    else
    {
     strcpy(no,name);
     if(vertify(name,pawd,"student"))
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
       //printf("\t\t Insert successfully!");
       printf("\t Welcome you %s!\n",name);
       return 1;
      }
      else
      {
       printf("Error:%s\n",mysql_error(mysql));
      }
     }
     else
      return 0;
    }
   }
}
int vertify(char* name,char*  passwd,const char* type)
{
 char str[20]="";
 char str1[20]="";
 int flag=0;
 res=mysql_use_result(mysql);
 if(res!=NULL)
 {
  while((row=mysql_fetch_row(res)))
  {
   strcpy(str,row[0]);
   strcpy(str1,row[2]);
   flag=0;
  }
  if(strcmp(name,str)!=0)
  {
    printf("\t\t User name is not correct! \n");
    mysql_free_result(res);
    return 0;
  }
  if(strcmp(passwd,str1)!=0)
  {
   printf("\t\t Wrong password! \n");
   mysql_free_result(res);
   return 0;
  }
  mysql_free_result(res);
  return 1;
 }
 else
 {
  printf("\t\t User isn't exist! \n");
  return 0;
 }
}
void queryForInfo(char *s,char *t)
{
 char sel[MAX];
 if(strcmp(s,"teacher")==0)
 {
  strcpy(sel,"select * from teacher where tno='");
  strcat(sel,t);
  strcat(sel,"'");
  int flag=mysql_real_query(mysql,sel,strlen(sel));
  if(!flag)
  {
   res=mysql_use_result(mysql);
   if(res)
   {
    int count=0;
    row=mysql_fetch_row(res);
    printf("\t\t\ttno\ttname\tage\tpasswd\n");
    printf("\t\t\t");
    while(count < mysql_field_count(mysql))
    {
     printf("%s\t",row[count]);
     count++;
    }
    printf("\n");
   }
   mysql_free_result(res);
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
    res=mysql_use_result(mysql);
    if(res)
    {
     row=mysql_fetch_row(res);
     printf("\t\t\tsno\tsname\tsage\tsex\tsclass\tpasswd\n");
     printf("\t\t\t");
     while(count < mysql_field_count(mysql))
     {
      printf("%s\t",row[count]);
      count++;
     }
     printf("\n");
    }
    mysql_free_result(res);
   }
   else
   {
    printf("%s",mysql_error(mysql));
   }
 }
}
void changePassword(const char* name,const char * no)
{
 char sel[MAX];
    char old_pass[MAX_SIZE];
 printf("\t Enter the old password: ");
 scanf("%s",old_pass);
 if(strcmp(name,"teacher")==0)
 {
  strcpy(sel,"select tno,passwd from teacher where tno=");
  strcat(sel,no);
  int flag=mysql_real_query(mysql,sel,strlen(sel));
  if(!flag)
  {
   res=mysql_use_result(mysql);
   row=mysql_fetch_row(res);
   if(strcmp(row[1],old_pass)!=0)
   {
    printf(" The old password is not correct!\n");
    mysql_free_result(res);
   }
   else
   {
    mysql_free_result(res);
    char in[MAX];
    char new_passwd[MAX_SIZE];
    printf("\t Enter the new password:");
    scanf("%s",new_passwd);
    strcpy(in,"update teacher set passwd='");
    strcat(in,new_passwd);
    strcat(in,"'");
    strcat(in,"where tno='");
    strcat(in,no);
    strcat(in,"'");
    //printf("%s \n",in);
    int re= mysql_real_query(mysql,in,strlen(in));
    if(!re)
    {
     printf(" Password reset successfully!\n");
    }
    else
    {
     printf(" Failed!\n");
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
  if(!(flag = mysql_real_query(mysql,sel,strlen(sel))))
  {
   res=mysql_use_result(mysql);
   row=mysql_fetch_row(res);
   if(strcmp(row[1],old_pass)!=0)
   {
      printf(" The old password is not correct!\n");
    mysql_free_result(res);
   }
   else
   {
    char in[MAX];
    char new_passwd[MAX_SIZE];
    printf("\t Enter the new password:");
    scanf("%s",new_passwd);
    strcpy(in,"update student set passwd='");
    strcat(in,new_passwd);
    strcat(in,"'");
     mysql_free_result(res);
    int re;
    if(!(re = mysql_real_query(mysql,in,strlen(in))))
    {
      printf("Change successfully!\n");
    }
   }
  }
  else
  {
   printf("%s \n",mysql_error(mysql));
  }
 }
}
void chooseClass(const char* sno)
{
 char cno[MAX_SIZE];
 char in[MAX];
 int flag;
 printf("\t\t Class ID: ");
 scanf("%s",cno);
 strcpy(in,"insert into select_c(sno,cno,grade) values('");
 strcat(in,sno);
 strcat(in,"','");
 strcat(in,cno);
 strcat(in,"',0)");
 if(!(flag=mysql_query(mysql,in)))
 {
  printf("\t\t\t Choose class successfully!\n");
 }
 else
 {
  printf("%s",mysql_error(mysql));
 }
}
void changeGrade()
{
 char sno[MAX_SIZE];
 char cno[MAX_SIZE];
 char up[MAX];
 double grade;
 int flag;
 while(true)
 {
  printf("\t\t Input student ID: ");
  scanf("%s",sno);
  if(!strcmp(sno, "exit")) break;
  printf("\t\t Input class ID: ");
  scanf("%s",cno);
  printf("\t\t Enter grade: ");
  scanf("%lf",&grade);
  if(grade<0)
  {
    break;
  }
  else
  {
   char str[5];
   gcvt(grade,4,str);
   strcpy(up,"update select_c set grade=");
   strcat(up,str);
   strcat(up," where sno='");
   strcat(up,sno);
   strcat(up,"' and cno='");
   strcat(up,cno);
   strcat(up,"'");
   if(!(flag=mysql_real_query(mysql,up,strlen(up))))
   {
    printf("\t\t\t Change successfully!\n");
   }
   else
   {
    printf("%s\n ",mysql_error(mysql));
   }
  }
 }
}
void addStudent()
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
   // printf("%s \n",in);
    if(!(j=mysql_real_query(mysql,in,strlen(in))))
    {
                    printf("\t\t Insert successfully!\n");
    }
    else
    {
    printf("\t\t Insert failed! %s \n",mysql_error(mysql));
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
 }
}
void connectToMysql()
{
     mysql=mysql_init(NULL);
  if(!mysql)
  {
   printf("\t\t Initialize successfully! \n");
  }
  //printf("111\n");
  mysql=mysql_real_connect(mysql,"localhost","root","zy0101zy","zhang",3306,NULL,0);
  if(!mysql)
   printf("\t\t Connect failed! \n");
}
void disConnectToMysql()
{
     mysql_close(mysql);
}
void addStudent2(){
    //char stuId[80] = "", stuName[80] = "";
    char sid[20], sname[20];
    //char stuAge[20];
    char query[200] = "select * from student where sno='";
    char insertQuery[100] = "insert into student(sno, sname) values('";
    char ins[100];
    char insert[200];

    printf("Student ID:  ");
    scanf("%s", sid);
    printf("Student Name:  ");
    scanf("%s", sname);

    strcat(query, sid);
    strcat(query, "')");
    printf("%s", query);

    mysql_real_query(mysql, query, strlen(query));
    int result=mysql_affected_rows(mysql);
    if(!result){
        printf("already in the table!\n");return;
    }
    mysql_free_result(res);
            //strcpy(insertQuery, insertQuery);
            strcpy(ins, "insert into student(sno, sname, sex) values('");
            strcat(ins, sid);
            strcat(ins, "','");
            strcat(ins, sname);
            //strcat(ins, "','");
            //strcat(insertQuery, stuAge);
            //trcat(insert, "','");
            //strcat(ins, stuSex);
            strcat(ins, "')");
            if(!mysql_query(mysql, ins)){
                printf("Add student information successfully!\n");
                return;
            }
            else printf("Add student information failed!\n");
            return;
}
void addCourse(){
    char cno[20], cname[30], cre[50];
    double credit=0;
    char query[50] = "select * from course where cno='";
    char insertQuery[200] = "insert into course(cno, cname) values('";
    printf("Course ID:  ");
    scanf("%s", cno);
    printf("Course Name:  ");
    scanf("%s", cname);
    //printf("Course credit:  ");
    //scanf("%lf", &credit);
    //ecvt(credit, 5, cre);
    strcat(query, cno);
    strcat(query, "')");
    if(mysql_real_query(mysql, query, strlen(query)) == 0){
        printf("already exist!\n");return;
    }
    else{
        strcat(insertQuery, cno);
        strcat(insertQuery, "','");
        strcat(insertQuery, cname);
       // strcat(insertQuery, "','");
       // strcat(insertQuery, cre);
        strcat(insertQuery, "')");
        if(mysql_real_query(mysql, insertQuery, strlen(insertQuery)) == 0){
            printf("Add course information successfully!\n");
        }
        else{
            printf("Add course information failed!\n");
        }
    }
    return;
}
int main()
{
 int a,b;
 int c=1;
 int count,count1;
 char temp[MAX_SIZE];
 connectToMysql();
 addStudent();
 printf("****************************************************************\n");
 printf("\t\t System For Class Choosing \t\t\t\n");
 printf("\t\t 1.Login \t\t\t\t\n");
 printf("\t\t 2.Exit \t\t\t\t\n");
 printf("****************************************************************\n");
 printf("Select Please: ");
 scanf("%d",&a);
 //printf("Input any number to continue......\n");
 //getchar();
 getchar();
 switch(a)
 {
  case 1:
   {
    while(c)
    {
     system("clear");
     printf("====================================\n");
     printf("\t Select your identity. \n");
     printf("\t 1. Teacher \n");
     printf("\t 2. Student \n");
     //printf("\t\t\t Input any number to continue...... \n");
     printf("====================================\n");
     printf("\t\t Select Please: ");
     scanf("%d",&b);
     switch(b)
     {
      case 1:
       if(login("teacher",temp))
       {
        while(true)
        {
         //system("clear");
         printf("================================\n");
         printf("\t Select Operation. \n");
         printf("\t 1. Add Grade \n");
         printf("\t 2. Add Student\n");
         printf("\t 3. Add Course\n");
         printf("\t 4. Exit \n");
         printf("================================\n");
         printf("\t Select Please: ");
         scanf("%d",&count1);
         switch(count1)
         {
          case 1:
           changeGrade();
           break;
          case 2:
           addStudent2();break;
          case 3:
            addCourse();break;
          default:
           count1=0;
           break;
         }
         if(count1==0)
         break;
         getchar();
        }
       }
       break;
      case 2:
       if(login("student",temp))
       {
        while(true)
        {
         //system("clear");
         printf("=============================\n");
         printf("\t\t Select Operation. \n");
         //printf("\t\t\t\t 1. Change Password \n");
         printf("\t\t 1. Choose Class \n");
         //printf("\t\t 2. Looking For Information\n");
         printf("\t\t 2. Exit \n");
         printf("=============================\n");
         printf("\t\t Select Please: ");
         scanf("%d",&count);
         switch(count)
         {
          case 1:
           chooseClass(temp);
           break;
          //case 2:
           //queryForInfo("student",temp);
           //break;
          default :
           count=0;
           break;
         }
         if(count==0)
          break;
         //printf("Input any number to continue......\n");
         //getchar();
         getchar();
        }
       }
       break;
      default:
       c=0;
       break;
      //printf("Input any number to continue......\n");
      //getchar();
      getchar();
     }
    }
   }
   break;
  default:
   break;
 }
 disConnectToMysql(mysql);
 return 0;
}
