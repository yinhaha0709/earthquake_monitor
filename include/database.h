#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <mysql/mysql.h>

void mysqldb_connect(MYSQL *mysql);
void mysqldb_insert(MYSQL *mysql, char *table_name, char *feild_name, char *content_value);
//void mysqldb_insert_test(MYSQL *mysql, double timestrap, double value);
//void mysqldb_insert_cal(MYSQL *mysql, char *table_name, char *field_name, char *content_value);
void mysqldb_alter(MYSQL *mysql, char *table_name, char *field_name);
void mysqldb_delete(MYSQL *mysql, char *table_name, char *field_name, int num);
void mysqldb_update(MYSQL *mysql, char *field_name, int value);
//void mysqldb_update_double(MYSQL *mysql, char *field_name, double value, int id);
int  mysqldb_query_row(MYSQL *mysql, char *content, char *table_name, char *name, char *value);
int mysqldb_query(MYSQL *mysql, char *content, char *table_name, char *name, char *value);
void close_connection(MYSQL *mysql);

#endif