#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

bool connectToMysql(MYSQL* mysql);
void disConnectToMysql(MYSQL* mysql);
int vertify(char* name, char*  password, const char* type, MYSQL_RES * res_ptr, MYSQL* mysql);
#endif // FUNCTIONS_H_INCLUDED
