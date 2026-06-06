#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ISOLATE_LIST "/data/openmask/isolate.list"
#define ISO_LOG "/data/openmask/log/isolate.log"

int isolate_app(const char *pkgname)
{
    char cmd[256];
    snprintf(cmd,sizeof(cmd),"mount --bind /dev/null /data/app/%s",pkgname);
    system(cmd);
    FILE *log = fopen(ISO_LOG,"a");
    if(log){
        fprintf(log,"[ISOLATE] %s\n",pkgname);
        fclose(log);
    }
    return 0;
}

#ifdef BUILD_EXE
int main(int argc,char**argv)
{
    isolate_app(argv[1]);
    return 0;
}
#endif
