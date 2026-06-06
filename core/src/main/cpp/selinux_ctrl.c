#include <stdio.h>
#include <stdlib.h>

#define SELINUX_LOG "/data/openmask/log/se.log"

int set_selinux(int permissive)
{
    FILE *fp = fopen("/sys/fs/selinux/enforce","w");
    if(fp){
        fprintf(fp,"%d",permissive);
        fclose(fp);
    }
    FILE *log = fopen(SELINUX_LOG,"a");
    if(log){
        fprintf(log,"[SE] set to %s\n",permissive?"Permissive":"Enforce");
        fclose(log);
    }
    return 0;
}

#ifdef BUILD_EXE
int main(int argc,char**argv)
{
    set_selinux(atoi(argv[1]));
    return 0;
}
#endif
