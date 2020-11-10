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

    mysqldb_query(mysql, "value1, value2, value3, value4, value5, value6", TABLE_NAME1, "1", "1 order by timestrap desc limit 200");

    /*
    printf("finish1\n");
    mysqldb_query(mysql, "value", TABLE_NAME1, "1", "1 order by timestrap asc limit 200");
    for(i=0; i<200; i++)
    {
        printf("%f\n", data_check_array[i]);
    }
    printf("finish2\n");

    mysqldb_query(mysql, "min_data_value", TABLE_NAME3, "1", "1 order by id desc limit 200");
    for(i=0; i<30; i++)
    {
        printf("%f\n", min_check_array[i]);
    }
    printf("finish3\n");
    */
    close_connection(mysql);
}