#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define AUTH_LIST "/data/openmask/auth.list"
#define ROOT_SWITCH "/data/openmask/magisk_root_switch"

static int check_root_switch(void)
{
    return access(ROOT_SWITCH,F_OK)==0 ? 1 : 0;
}
int check_uid_auth(uid_t uid)
{
    if(!check_root_switch()) return 0;
    if(uid == 0) return 1;
    FILE *fp = fopen(AUTH_LIST,"r");
    if(!fp) return 0;
    uid_t tmp;
    while(fscanf(fp,"%d",&tmp)!=EOF){
        if(tmp == uid){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
int add_auth_uid(uid_t uid)
{
    FILE *fp = fopen(AUTH_LIST,"a");
    if(!fp) return -1;
    fprintf(fp,"%d\n",uid);
    fclose(fp);
    return 0;
}

#ifdef BUILD_EXE
int main(int argc,char**argv)
{
    if(argc==2){
        uid_t u=atoi(argv[1]);
        printf("%d",check_uid_auth(u));
    }else if(argc==3 && !strcmp(argv[1],"add")){
        add_auth_uid(atoi(argv[2]));
    }
    return 0;
}
#endif
