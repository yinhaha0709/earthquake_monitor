#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include "../include/config.h"
#include "../include/systime.h"
#include "../include/Crc16.h"


union union_change
{
    
    uint8_t i_array[4];
    float    f;
};
                
int main(void)
{
    int fd;
    struct termios old_cfg, new_cfg;
    int speed;
    int count, i, j, crc_check;
    uint8_t i_data[200];
    float sig_V[6], sig_g[6];
    double sys_time;
    union union_change U1;
    

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

    j = 0;

    while(1){
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
                    sig_g[1] = (sig_V[1] - 1.500000) / 0.300000;
                    sig_g[2] = (sig_V[2] - 1.800000) / 0.300000;
                    sig_g[3] = (sig_V[3] - 2.500000) / 1.250000;
                    sig_g[4] = (sig_V[4] - 2.500000) / 1.250000;
                    sig_g[5] = (sig_V[5] - 1.250000) / 1.250000;

                   printf("\n%f: %f %f %f %f %f %f\n", sys_time, sig_g[0], sig_g[1], sig_g[2], sig_g[3], sig_g[4], sig_g[5]);
                   
                }
            }
            j = 0;
    	}
    }
    close(fd);
    return 0;
}
