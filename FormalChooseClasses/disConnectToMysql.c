#include<stdio.h>
#include<stdlib.h>
#include "/usr/include/mysql/mysql.h"
#include "functions.h"

void disConnectToMysql(MYSQL* mysql){
    mysql_close(*mysql);
}
