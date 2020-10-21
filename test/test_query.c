#include <stdio.h>
#include <mysql/mysql.h>
#include "../include/database.h"
#include "../include/config.h"

int main(int argc, void *argv[])
{
    MYSQL *mysql;
    MYSQL_ROW array1;
    int i = 0;

    mysql = mysql_init(NULL);
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }
    mysqldb_connect(mysql);

    mysqldb_query_row(mysql, "value", TABLE_NAME1, "1", "1 order by timestrap desc limit 200");
    for(i=0; i<200; i++)
    {
        printf("%f\n", data_check_array[i]);
    }
    printf("finish");
    close_connection(mysql);
}