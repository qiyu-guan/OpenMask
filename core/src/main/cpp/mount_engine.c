#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>

#define MOUNT_LOG "/data/openmask/log/mount.log"

int mount_part(const char *src,const char *target,const char *fstype,int flag)
{
    int ret = mount(src,target,fstype,flag,NULL);
    FILE *log = fopen(MOUNT_LOG,"a");
    if(log){
        fprintf(log,"[MOUNT]%s -> %s ret:%d\n",src,target,ret);
        fclose(log);
    }
    return ret;
}
int umount_part(const char *target)
{
    int ret = umount(target);
    FILE *log = fopen(MOUNT_LOG,"a");
    if(log){
        fprintf(log,"[UMOUNT]%s ret:%d\n",target,ret);
        fclose(log);
    }
    return ret;
}

#ifdef BUILD_EXE
int main(int argc,char**argv)
{
    if(!strcmp(argv[1],"mount")) mount_part(argv[2],argv[3],argv[4],0);
    else umount_part(argv[2]);
    return 0;
}
#endif
