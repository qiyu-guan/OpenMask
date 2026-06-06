#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define LOG_ROOT "/data/openmask/log/"
#define LOG_SWITCH "/data/openmask/log_switch"
#define MAX_LOG_SIZE (1024*1024*10) //单日志上限10MB

//日志总开关：0关闭 1开启
int log_set_switch(int on)
{
    FILE *fp = fopen(LOG_SWITCH,"w");
    if(fp){
        fprintf(fp,"%d",on);
        fclose(fp);
    }
    return 0;
}
//日志自动轮转
int log_rotate(const char *logpath)
{
    struct stat st;
    stat(logpath,&st);
    if(st.st_size > MAX_LOG_SIZE){
        char bak[256];
        snprintf(bak,sizeof(bak),"%s.bak",logpath);
        rename(logpath,bak);
    }
    return 0;
}

#ifdef BUILD_EXE
int main(int argc,char**argv)
{
    if(!strcmp(argv[1],"on")) log_set_switch(1);
    else if(!strcmp(argv[1],"off")) log_set_switch(0);
    else log_rotate(argv[1]);
    return 0;
}
#endif
