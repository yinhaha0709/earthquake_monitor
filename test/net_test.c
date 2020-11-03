#include <stdio.h>

int main()
{
    FILE * p_file = NULL;

    p_file = popen("ping 202.108.22.5", "r");

    if(!p_file){
        printf("internet error!");
    }
    pclose(p_file);

    return 0;
}
