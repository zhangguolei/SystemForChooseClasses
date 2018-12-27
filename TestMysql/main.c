#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"
#include <string.h>
#pragma comment(lib,"libmysql.lib")
    MYSQL* sql;
    MYSQL_RES *res_ptr;
    MYSQL_ROW sqlrow;
int main()
{
    int t=0;
    //mysql_create_db(sql,"mysql2") ;
    sql=mysql_init(NULL);
		if(!sql)
		{
			printf("\t\t初始化失败！\n");
		}

   // mysql_create_db(sql, "ok");
		sql=mysql_real_connect(sql,"localhost","root","zy0101zy","mysql",3306,NULL,0);
		if(!sql)
			printf("\t\t链接失败！\n");
        char query[50] = "select * from testTable where id=3";
        char query2[50] = "insert into testTable values(5, 30, 'm', 'NWAFU')";
        mysql_real_query(sql, query, strlen(query));     //对数据库进行操作
       res_ptr = mysql_store_result(sql);



            /*while(sqlrow=mysql_fetch_row(res_ptr)){
            for(; t<mysql_num_fields(res_ptr); t++){
                printf("%s\t", sqlrow[t]);
            }
            printf("\n");
        }*/

        mysql_free_result(res_ptr);
        mysql_real_query(sql, query2, strlen(query2));



    return 0;
}
