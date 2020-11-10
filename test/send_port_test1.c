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
    float sig_V[6], sig_g[6], sys_time; 
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
		printf("start: ");
		for(i=0; i<count; i++)
			printf("%x ", i_data[i]);
		
		printf("finish\n");
	}
    }
    close(fd);
    return 0;
}
