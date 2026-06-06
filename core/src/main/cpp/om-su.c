#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "kern_auth.c"

#define MAGISK_ROOT_TOGGLE "/data/adb/modules/openmask/root_enable"

//面具面板写入开关，同步到kern_auth的root_switch
void sync_magisk_root(void)
{
    if(access(MAGISK_ROOT_TOGGLE,F_OK)==0){
        system("touch /data/openmask/magisk_root_switch");
    }else{
        system("rm -f /data/openmask/magisk_root_switch");
    }
}

int main(int argc,char**argv)
{
    sync_magisk_root();
    uid_t cur = getuid();
    if(check_uid_auth(cur)){
        setuid(0);
        execv("/system/bin/sh",argv);
    }else{
        fprintf(stderr,"ROOT权限已被面具关闭\n");
        return 1;
    }
}
