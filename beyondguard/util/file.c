#include "file.h"

#include <sys/stat.h>


int isFile(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int isDirectory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0){
        return 0;
    }

   return S_ISDIR(statbuf.st_mode);
}
