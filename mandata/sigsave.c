#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>
#include <pthread.h>
#include "../include/config.h"
#include "../include/database.h"
#include "../include/systime.h"
#include "../include/arrayop.h"
#include "../include/sigsave.h"


void * signal_save(void * arg)
{
    double runtime;
    int m = 0;
    int data_row_num = 0;    
    //double **d = allocation_memory_double(50, 7);
    double d[50][7];
    char message[200] = {0};
    MYSQL *mysql_sig;
    //MYSQL *mysql;

    runtime = get_system_time3f();
    printf("data save pthread start time: %f\n", runtime);

    pthread_mutex_lock(&mutex);
    //printf("mutex data ok");
    for(m=0; m<50; m++)
    {
        //d[m][0] = c[m][0];
        //d[m][1] = c[m][1];
        d[m][0] =((double*)arg)[m * 7];
        d[m][1] = ((double*)arg)[m *7 + 1];
        d[m][2] = ((double*)arg)[m * 7 + 2];
        d[m][3] = ((double*)arg)[m * 7 + 3];
        d[m][4] = ((double*)arg)[m * 7 + 4];
        d[m][5] = ((double*)arg)[m * 7 + 5];
        d[m][6] = ((double*)arg)[m * 7 + 6];
        //printf("%f %f\n", d[m][0], d[m][1]);
    }
    //printf("copy data ok\n");
    pthread_mutex_unlock(&mutex);
    //printf("mutex data ok\n");
/*
    mysql = mysql_init(NULL); 
    if (!mysql) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql);
*/
    if(earthquake_status == 1)
    {
        FILE *fp_csv;
        fp_csv = fopen("../data/temp.csv", "a+");
        for(m=0; m<50; m++)
        {
            fprintf(fp_csv, "%f\t%f\t%f\t%f\t%f\t%f\n", d[m][1], d[m][2], d[m][3], d[m][4], d[m][5], d[m][6]);
        }
        fclose(fp_csv);
    }

    mysql_sig = mysql_init(NULL); 
    if (!mysql_sig) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql_sig);

    for(m=0; m<50; m++)
    {
	    sprintf(message, "%f, %f, %f, %f, %f, %f, %f", d[m][0], d[m][1], d[m][2], d[m][3], d[m][4], d[m][5], d[m][6]);
        mysqldb_insert(mysql_sig, TABLE_NAME1, "timestrap, value1, value2, value3, value4, value5, value6", message);
	    memset(message, 0, sizeof(message));
    }

    close_connection(mysql_sig);
    //mysql_library_end();

    //free_memory_double(d, 50);

    runtime = get_system_time3f();
    printf("data save pthread finish time: %f\n", runtime);

    pthread_detach(pthread_self());

}