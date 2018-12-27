#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

bool connectToMysql(MYSQL* mysql);
void disConnectToMysql(MYSQL* mysql);
int vertify(char* name, char*  password, const char* type, MYSQL_RES * res_ptr, MYSQL* mysql, MYSQL_ROW *sqlrow);
int login( const char* f,char * no, int maxSize, int maxNumber, MYSQL *mysql, MYSQL_RES * res_ptr, MYSQL_ROW *sqlrow);
void check(char * s,char * t, MYSQL_RES * res_ptr, MYSQL* mysql, MYSQL_ROW *sqlrow, int maxNumber);
void changePasswd(const char* name,const char * no, MYSQL_RES * res_ptr, MYSQL* mysql, MYSQL_ROW sqlrow, int maxSize, int maxNumber);
void changeGrade(MYSQL* mysql, int maxSize, int maxNumber);
void chooseClass(const char* sno, MYSQL *mysql, int maxSize, int maxNumber);
void addStudent(MYSQL *mysql);

#endif // FUNCTIONS_H_INCLUDED
