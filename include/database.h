#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <mysql/mysql.h>

void mysqldb_connect(MYSQL *mysql);
void mysqldb_insert(MYSQL *mysql, double timestrap, double value);
void mysqldb_delete(MYSQL *mysql, char *field_name, char *num);
void mysqldb_update(MYSQL *mysql, char *field_name, int value);
void mysqldb_query(MYSQL *mysql, char *content, char *table_name, char *name, char *value);
void close_connection(MYSQL *mysql);

#endif