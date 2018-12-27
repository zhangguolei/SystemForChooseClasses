#include<stdio.h>
#include<stdlib.h>
#include "/usr/include/mysql/mysql.h"
#include "functions.h"

bool connectToMysql(MYSQL* mysql){
    mysql = mysql_init(NULL);
    if(!mysql) {
        printf("initialize failure!\n");
        return false;
    }
    else{
        mysql = mysql_real_connect(mysql, "localhost", "root", "123", "llei", 0, NULL, 0);
        if(!mysql){
            printf("connect failure!\n");
            return false;
        }
    }
    return true;
}
