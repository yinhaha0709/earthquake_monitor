#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "../include/config.h"
#include "../include/database.h"

double min_check_array[30];
double max_check_array[30];
double ave_check_array[60];
double data_check_array[200];

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

void mysqldb_insert_cal(MYSQL *mysql, char *table_name, char *field_name, char *content_value)
{  
    int t;  
    char *head = "INSERT INTO ";  
    char query[900];
    char *left = "(";  
    char *right = ") ";  
    char *values = "VALUES";  
    char message[400] = {0};  

    sprintf(message, "%s", content_value);

    /* 拼接sql命令 */  
    sprintf(query, "%s%s%s%s%s%s%s%s%s", head, table_name, left, field_name, right, values, left, message, right);
    //printf("%s\n", query);  

    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("Failed to query: %s\n", mysql_error(mysql));  
    } 
    else {
        //printf("\nInsert sucessfully!\n");
    }
    
}

void mysqldb_alter(MYSQL *mysql, char *table_name, char *field_name)
{
    int t;
    char query1[120], query2[120];
    sprintf(query1, "ALTER TABLE %s DROP %s", table_name, field_name);
    t = mysql_real_query(mysql, query1, strlen(query1));

    if (t) {  
        printf("Failed to alter1: %s\n", mysql_error(mysql));  
    } 
    else {
        printf("\nalter1 sucessfully!\n");
    }

    sprintf(query2, "ALTER TABLE %s add %s int(11) primary key auto_increment first", table_name, field_name);
    t = mysql_real_query(mysql, query2, strlen(query2));

    if (t) {  
        printf("Failed to alter2: %s\n", mysql_error(mysql));  
    } 
    else {
        printf("\nalter2 sucessfully!\n");
    }
}

/* 删除数据 */
void mysqldb_delete(MYSQL *mysql, char *table_name, char *field_name, int num)
{  
    int t;
    char *head = "DELETE FROM ";  
    char query[120];  

    sprintf(query, "%s%s where 1=1 order by %s limit %d", head, table_name, field_name, num);
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

//updata double data in table2
/*
void mysqldb_update_double(MYSQL *mysql, char *field_name, double value, int id)
{  
    int t;
    char *head = "UPDATE ";
    char query[120];

    sprintf(query, "%s%s SET %s=%f WHERE id=%d", head, TABLE_NAME2, field_name, value, id);
    //printf("%s\n", query);

    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("Failed to update: %s\n", mysql_error(mysql));  
        return;
    }
    //printf("\nUpdate data sucessfully!\n");
}
*/
/* 查询数据 */
MYSQL_ROW mysqldb_query(MYSQL *mysql, char *content, char *table_name, char *name, char *value)  
{  
    int t, i = 0;
    char *head = "SELECT  ";
    char query[120] = {0};
    MYSQL_RES *res = NULL;
    MYSQL_ROW row; 

    sprintf(query, "%s%s FROM %s WHERE %s=%s", head, content, table_name, name, value);

    t = mysql_real_query(mysql, query, strlen(query));  

    if (t) {
        printf("Failed to query: %s\n", mysql_error(mysql)); 
    } else {
        //printf("\nQuery successfully!\n");  
    }

    res = mysql_store_result(mysql);
    row = mysql_fetch_row(res);

    mysql_free_result(res);
    return row;
} 

void mysqldb_query_row(MYSQL *mysql, char *content, char *table_name, char *name, char *value)  
{  
    int t, i;
    char *head = "SELECT  ";
    char query[120] = {0};
    MYSQL_RES *res = NULL;
    MYSQL_ROW row; 

    sprintf(query, "%s%s FROM %s WHERE %s=%s", head, content, table_name, name, value);

    t = mysql_real_query(mysql, query, strlen(query));  

    if (t) {
        printf("Failed to query: %s\n", mysql_error(mysql)); 
    } else {
        //printf("\nQuery successfully!\n");  
    }

    res = mysql_store_result(mysql);
    i = 0;
    if(strcmp(table_name, TABLE_NAME1) == 0){
        while(row = mysql_fetch_row(res)) {  
            for(t = 0; t < mysql_num_fields(res); t++) { 
                //printf("%s %d\n", row[t], t);
                data_check_array[i] = atof(row[t]);
                //printf("%f\n", data_check_array[i]);
            }
            i++;
            //printf("\n");
        }
    }
    if(strcmp(table_name, TABLE_NAME3) == 0){
        while(row = mysql_fetch_row(res)) {  
            for(t = 0; t < mysql_num_fields(res); t++) { 
                //printf("%s %d\n", row[t], t);
                min_check_array[i] = atof(row[t]);
                //printf("%f\n", data_check_array[i]);
            }
            i++;
            //printf("\n");
        }
    }
    if(strcmp(table_name, TABLE_NAME4) == 0){
        while(row = mysql_fetch_row(res)) {  
            for(t = 0; t < mysql_num_fields(res); t++) { 
                //printf("%s %d\n", row[t], t);
                max_check_array[i] = atof(row[t]);
                //printf("%f\n", data_check_array[i]);
            }
            i++;
            //printf("\n");
        }
    }
    if(strcmp(table_name, TABLE_NAME5) == 0){
        while(row = mysql_fetch_row(res)) {  
            for(t = 0; t < mysql_num_fields(res); t++) { 
                //printf("%s %d\n", row[t], t);
                ave_check_array[i] = atof(row[t]);
                //printf("%f\n", data_check_array[i]);
            }
            i++;
            //printf("\n");
        }
    }

/*
    while(row = mysql_fetch_row(res)) {  
        for(t = 0; t < mysql_num_fields(res); t++) { 
            //printf("%s %d\n", row[t], t);
            data_check_array[i] = atof(row[t]);
            //printf("%f\n", data_check_array[i]);
        }
        i++;
        //printf("\n");
    }
*/
    mysql_free_result(res);
} 

/* 断开mysql连接 */ 
void close_connection(MYSQL *mysql)
{
    mysql_close(mysql);
}