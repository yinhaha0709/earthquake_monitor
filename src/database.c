#include <mysql/mysql.h>
#include "../include/config.h"
#include "../include/database.h"

/* 连接mysql */  
void mysqldb_connect(MYSQL *mysql)
{  
    if(!mysql_real_connect(mysql, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD, DB_NAME, 3306, NULL, 0)) {  
        printf("\nFailed to connect:%s\n", mysql_error(mysql));  
    } else {
       //printf("\nConnect sucessfully!\n"); 
    }
}   

/* 插入数据 */
void mysqldb_insert(MYSQL *mysql, double timestrap, double value)
{  
    int t;  
    char *head = "INSERT INTO ";  
    char query[120];
    char field[24] = "timestrap, value";
    char *left = "(";  
    char *right = ") ";  
    char *values = "VALUES";  
    char message[100] = {0};  

    sprintf(message, "%f, %f", timestrap, value);

    /* 拼接sql命令 */  
    sprintf(query, "%s%s%s%s%s%s%s%s%s", head, TABLE_NAME1, left, field, right, values, left, message, right);
    //printf("%s\n", query);  

    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("Failed to query: %s\n", mysql_error(mysql));  
    } 
    else {
        //printf("\nInsert sucessfully!\n");
    }
    
}  

/* 删除数据 */
void mysqldb_delete(MYSQL *mysql, char *field_name, char *num)
{  
    int t;
    char *head = "DELETE FROM ";  
    char query[120];  

    sprintf(query, "%s%s where 1=1 order by %s limit %s", head, TABLE_NAME1, field_name, num);
    //printf("%s\n", query);

    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("\nFailed to query: %s\n", mysql_error(mysql));  
    } else {
        //printf("\nDelete data sucessfully!\n");  
    }
    
}   

/* 更新数据 */
void mysqldb_update(MYSQL *mysql, char *field_name, int value)
{  
    int t;
    char *head = "UPDATE ";
    char query[120];

    sprintf(query, "%s%s SET %s=%d WHERE id=1", head, TABLE_NAME2, field_name, value);
    //printf("%s\n", query);

    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("Failed to update: %s\n", mysql_error(mysql));  
        return;
    }
    //printf("\nUpdate data sucessfully!\n");
}

/* 查询数据 */
void mysqldb_query(MYSQL *mysql, char *content, char *table_name, char *name, char *value)  
{  
    int t;
    char *head = "SELECT  ";
    char query[120] = {0};

    sprintf(query, "%s%s FROM %s WHERE %s=%s", head, content, table_name, name, value);

    t = mysql_real_query(mysql, query, strlen(query));  

    if (t) {
        printf("Failed to query: %s\n", mysql_error(mysql)); 
    } else {
        //printf("\nQuery successfully!\n");  
    }

    res = mysql_store_result(mysql);
    row = mysql_fetch_row(res);

    //printf("%s\n", row[0]);  
    
    mysql_free_result(res);
}  

/* 断开mysql连接 */ 
void close_connection(MYSQL *mysql)
{
    mysql_close(mysql);
}