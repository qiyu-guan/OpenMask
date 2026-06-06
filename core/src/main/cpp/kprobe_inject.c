#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUGFS_KPROBE "/sys/kernel/debug/kprobes/enabled"
#define KP_LOG "/data/openmask/log/kprobe.log"

//注册kprobe钩子
int kprobe_register(const char *sym_name,const char *cmd)
{
    FILE *kp = fopen("/sys/kernel/debug/kprobes/write","w");
    FILE *log = fopen(KP_LOG,"a");
    if(!kp) return -1;
    fprintf(kp,"%s %s",sym_name,cmd);
    fclose(kp);
    if(log){
        fprintf(log,"[KPROBE] REG:%s\n",sym_name);
        fclose(log);
    }
    return 0;
}
//卸载全部kprobe
int kprobe_clear(void)
{
    FILE *kp = fopen("/sys/kernel/debug/kprobes/remove","w");
    if(kp){
        fputs("all",kp);
        fclose(kp);
    }
    FILE *log = fopen(KP_LOG,"a");
    if(log){
        fprintf(log,"[KPROBE] CLEAR ALL\n");
        fclose(log);
    }
    return 0;
}

#ifdef BUILD_EXE
int main(int argc,char**argv)
{
    if(!strcmp(argv[1],"clear")) return kprobe_clear();
    else return kprobe_register(argv[1],argv[2]);
}
#endif
