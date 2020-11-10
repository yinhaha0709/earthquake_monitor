#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <errno.h>

int main(int agrc, char* argv[])
{
    int fd_watchdog = open("/dev/watchdog", O_WRONLY);
    if(fd_watchdog == -1){
        int err = errno;
        printf("\n!!!FAILED to open /dev/watchdog, errno: %d\n", err);
        syslog(LOG_WARNING, "FAILED to open /dev/watchdog, errno: %d\n", err);
    }

    //feed the dog
    while(1)
    {
    	if(fd_watchdog >= 0){
        	static unsigned char food = 0;
        	ssize_t eaten = write(fd_watchdog, &food, 1);
	
        	if(eaten != 1){
            		puts("\n!!!FAILED feeding watchdog");
            		syslog(LOG_WARNING, "FAILED feeding watchdog");
        	}
    	}
    }

    return 0;
}
