#include <mysql/mysql.h>
#include <pthread.h>

#define BUF_SIZE 30
#define MYSQL_HOST    "localhost"
#define MYSQL_USER    "root"
#define MYSQL_PASSWD  "zncg123456"
#define DB_NAME "workbench_test"
#define TABLE_NAME1 "data_test"
#define TABLE_NAME2 "data_message"
#define MESSAGE_INT "message_int_content"
int row_num = 0;
double **c;
pthread_mutex_t mutex, mutex_row_check;
MYSQL_RES *res = NULL;
MYSQL_ROW row; 
int simple_rate = 200;