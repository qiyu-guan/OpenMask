#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

#define CACHE_SYS_PATH "/proc/sys/vm/drop_caches"
#define OM_CACHE_DIR "/data/openmask/cache/"

static int drop_kernel_cache(void)
{
    int fd = open(CACHE_SYS_PATH,O_WRONLY);
    if(fd < 0) return -1;
    write(fd,"3",1);
    close(fd);
    return 0;
}
static int clean_om_cache(void)
{
    DIR *dir = opendir(OM_CACHE_DIR);
    if(!dir){
        mkdir(OM_CACHE_DIR,0755);
        return 0;
    }
    struct dirent *ent;
    char buf[256];
    while((ent = readdir(dir)) != NULL){
        if(ent->d_name[0]=='.') continue;
        snprintf(buf,sizeof(buf),"%s%s",OM_CACHE_DIR,ent->d_name);
        unlink(buf);
    }
    closedir(dir);
    return 0;
}

int cache_main(void)
{
    drop_kernel_cache();
    clean_om_cache();
    FILE *log = fopen("/data/openmask/log/cache.log","a");
    if(log){
        fprintf(log,"[CACHE] %lld:缓存清理执行完毕\n",(long long)time(NULL));
        fclose(log);
    }
    return 0;
}

#ifdef BUILD_EXE
int main(){return cache_main();}
#endif
