#include<stdio.h>
#include<stdlib.h>
#include "/usr/include/mysql/mysql.h"
#include "functions.h"

void connectToMysql(MYSQL* mysql){
    mysql = mysql_init(NULL);
    if(!mysql) {
        printf("initialize failure!\n");
    }
    else{
        mysql = mysql_real_connect(mysql, "localhost", "root", "zy0101zy", "mysql", 3306, NULL, 0);
        if(!mysql){
            printf("connect failure!\n");
        }
    }
    return;
}
