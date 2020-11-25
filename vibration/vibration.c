#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
//#include <mosquitto.h>
#include <string.h>
#include <pthread.h>
#include <mysql/mysql.h>
#include "../include/config.h"
#include "../include/systime.h"
//#include "../include/arrayop.h"
#include "../include/database.h"
#include "../include/sigsave.h"
#include "../include/rowchange.h"
#include "../include/commfeature.h"
#include "../include/mqtt.h"
#include "../include/Crc16.h"
#include "../include/infoinit.h"
#include "../include/register.h"
#include "../include/idchange.h"
#include "../include/ontime.h"

pthread_mutex_t mutex, mutex_row_check, mutex_cal, mutex_min, mutex_max, mutex_ave;
float sig_g[6];
double timestrap;
char station_id[8], mode, version;
float longitude, latitude, strain, acceleration;
short int simple_rate, simple_num;
char position_num[2], station_num[2];
char topic_regpub[30], topic_regsub[33], topic_feature[29], topic_ontimepub[28], topic_ontimesub[31], topic_event[27];
char threshold_status[6];

union union_change
{
    uint8_t i_array[4];
    float f;
};
                
int main(void)
{
    int fd;
    pthread_t id_t1, id_t2, id_t3, id_t4, id_t5;
    struct termios old_cfg, new_cfg;
    int speed;
    int count, row_count, crc_check;
    int  i, j, k;
    uint8_t i_data[200];
    float sig_V[6];
    double sys_time, time_temp1, time_temp2, time_temp3, time_temp4;
    union union_change U1;
    MYSQL *mysql1;

    mysql1 = mysql_init(NULL); 
    if (!mysql1) {
        printf("\nMysql init failed.\n");
    }

    mysqldb_connect(mysql1);

    ontime_status = mysqldb_query_row(mysql1, MESSAGE_INT, TABLE_NAME2, "id", "1");
    ftp_status = mysqldb_query_row(mysql1, MESSAGE_INT, TABLE_NAME2, "id", "2");

    printf("%d, %d\n", ontime_status, ftp_status);
    close_connection(mysql1);

    running = 0, ontime_block_num = 0;
    for(i=0; i<6; i++)
        threshold_status[i] = 0;
    

    double c[350];
    for(j=0; j<350; j++)
        c[j] = 0;    

    fd = open(DATA_PORT, O_RDWR | O_NOCTTY | O_NDELAY);

    if(fd < 0){
        perror("open serial port");
        return -1;
    }

    if(fcntl(fd, F_SETFL, 0) < 0){
        perror("fcntl F_SETFL");
        return -1;
    }
    if(tcgetattr(fd, &old_cfg) != 0){
        perror("tcgetattr");
        return -1;
    }

    new_cfg = old_cfg;
    cfmakeraw(&new_cfg);
    new_cfg.c_cflag &= ~CSIZE;

    speed = B115200;
    cfsetispeed(&new_cfg, speed);
    cfsetospeed(&new_cfg, speed);

    new_cfg.c_cflag |= CS8;

    new_cfg.c_cflag &= ~PARENB;
    new_cfg.c_iflag &= ~INPCK;

    new_cfg.c_cflag &= ~CSTOPB;

    new_cfg.c_cc[VTIME] = 0;
    new_cfg.c_cc[VMIN] = 0;

    tcflush(fd, TCIFLUSH);

    if((tcsetattr(fd, TCSANOW, &new_cfg)) != 0){
        perror("tcsetattr");
        return -1;
    }

/////////////////////////////////////

    information_init();
    register_send();

/////////////////////////////////////

    row_count = 0; j = 0;

    time_temp1 = get_system_time3f();
    time_temp2 = time_temp1 + 0.5;
    time_temp3 = time_temp1 + 5;
    time_temp4 = time_temp1 + 7.5;

    while(1){
        if(row_count >= 350){
            row_count = 0;
            pthread_create(&id_t1, NULL, signal_save, (void*)&c);

            if(ontime_status == 1){
                //ontime_block_num++;
                pthread_create(&id_t5, NULL, ontime_send, (void*)&c);
            }
        }

        if((sys_time - time_temp2) >= 5.0){
            pthread_create(&id_t2, NULL, row_change, NULL);
            time_temp2 = sys_time;
        }

        if((sys_time - time_temp3) >= 1.0){
            pthread_create(&id_t3, NULL, common_feature, NULL);
            time_temp3 = sys_time;        
        }

        if((sys_time - time_temp4) >= 30.0){
            pthread_create(&id_t4, NULL, id_change, NULL);
            time_temp4 = sys_time;
        }

    	if((count = read(fd, i_data, 200)) > 0){
            if((i_data[0] == 0x70) && (i_data[1] == 0x03) && (i_data[2] == 0x18)){
                if((crc_check = calc_crc16(i_data, count)) == 0){

                    sys_time = get_system_time3f();
                    for(i=3; i<24; i=i+4)
                    {
                        U1.i_array[0] = i_data[i];
                        U1.i_array[1] = i_data[i + 1];
                        U1.i_array[2] = i_data[i + 2];
                        U1.i_array[3] = i_data[i + 3];
                        sig_V[j] = U1.f;
			//printf("%f\n", U1.f);
                        j++;
			//printf("\n%x %x %x %x\n", i_data[i], i_data[i+1], i_data[i+2], i_data[i+3]);
                    }

                    sig_g[0] = (sig_V[0] - 1.500000) / 0.300000;
                    sig_g[1] = (sig_V[1] - 1.500000) / 0.300000 + 0.04;
                    sig_g[2] = ((sig_V[2] - 1.500000) / 0.300000) - 1.09;
                    sig_g[3] = (sig_V[3] - 2.500000) / 1.250000;
                    sig_g[4] = (sig_V[4] - 2.500000) / 1.250000;
                    sig_g[5] = ((sig_V[5] - 2.500000) / 1.250000) + 1.0;


                    c[row_count] = sys_time;
                    row_count++;

                    for(k=0; k<6; k++)
                    {
                        c[row_count] = sig_g[k];
			            //printf("\n%d %f: %d %f\n", row_count, c[row_count], k, sig_g[k]);
			            row_count++;
                    }
                }
            }
            i = 0; j = 0; k = 0;
    	}
    }

}