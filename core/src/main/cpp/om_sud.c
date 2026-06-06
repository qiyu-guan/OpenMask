#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "cache_clean.c"
#include "log_ctrl.c"

#define PID_FILE "/data/openmask/om_sud.pid"

void daemon_run(void)
{
    while(1){
        cache_main();
        log_rotate("/data/openmask/log/all.log");
        sleep(3600); //1小时执行一次
    }
}

int main()
{
    FILE *pidf = fopen(PID_FILE,"w");
    if(pidf){
        fprintf(pidf,"%d",getpid());
        fclose(pidf);
    }
    daemon_run();
    return 0;
}
