

int vertify(char* name, char*  password, const char* type, MYSQL_RES * res_ptr, MYSQL* mysql){
    char str[20]="";
	char str1[20]="";
	MYSQL_ROW rows;
	int flag=0;
	*res_ptr=mysql_use_result(*mysql);
	if(res_ptr!=NULL)
	{
		while((rows=mysql_fetch_row(res_ptr)))
		{
			strcpy(str,rows[0]);
			strcpy(str1,rows[2]);
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
