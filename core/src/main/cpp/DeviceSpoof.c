#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPOOF_LOG "/data/openmask/log/spoof.log"
//系统属性白名单，需要伪装的字段
static const char *prop_list[][2]={
    {"ro.product.model","Mi 14"},
    {"ro.product.brand","Xiaomi"},
    {"ro.build.fingerprint","xiaomi/cupid/cupid:14/UKQ1.230929.001/V14.0.3.0:user/release-keys"},
    {"ro.serialno","OM20260606XXXX"},
    {"ro.debuggable","0"},
    {NULL,NULL}
};

int device_spoof(void)
{
    FILE *log = fopen(SPOOF_LOG,"a");
    int idx=0;
    while(prop_list[idx][0]){
        char cmd[256];
        snprintf(cmd,sizeof(cmd),"setprop %s %s",prop_list[idx][0],prop_list[idx][1]);
        system(cmd);
        if(log) fprintf(log,"[SPOOF] set %s = %s\n",prop_list[idx][0],prop_list[idx][1]);
        idx++;
    }
    if(log) fclose(log);
    return 0;
}

#ifdef BUILD_EXE
int main(){return device_spoof();}
#endif
