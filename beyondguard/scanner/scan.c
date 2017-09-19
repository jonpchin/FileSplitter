#include "scan.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <database/connect.h>
#include <util/file.h>
#include <util/md5.h>
#include <util/stack.h>

// scans directory to see if any files match MD5 in databases
int scanDirectory(char *searchDir){
    DIR *midir;
    struct dirent* info_archivo;
    struct stat fileStat;
    char fullpath[256];

    if ((midir=opendir(searchDir)) == NULL)
    {
        perror("Error in opendir");
        return 1;
    }
    while ((info_archivo = readdir(midir)) != 0)
    {
        strcpy (fullpath, searchDir);
        strcat (fullpath, "/");
        if(strcmp(info_archivo->d_name, ".") == 0  || strcmp(info_archivo->d_name, "..") == 0){
            //skip current directory and moving up a directory
            continue;
        }
        strcat (fullpath, info_archivo->d_name);
        if(isDirectory(fullpath)){
            scanDirectory(fullpath);
        }else if (!stat(fullpath, &fileStat) && isFile(fullpath)){

            char md5string[33];
            char *md5 = getMD5(fullpath, md5string);
            if(md5 != NULL){
                int result = isMD5InDB(md5);
                if(result == 1){
                    printf("%s located at %s is possibly a virus!\n", info_archivo->d_name, fullpath);
                }//else{
                //    printf("%s is not a virus.\n", info_archivo->d_name);
                //}
            }
        }
    }
    closedir(midir);
    return 0;
}

int scanDirectoryUsingStack(char *searchDir){

    Stack s;
    stackInit(&s);
    stackPush(&s, searchDir);

    while(stackIsEmpty(&s) != 1){

        char *top = stackTop(&s);

        printf("top is %s\n", top);
        stackPop(&s);
        if(isDirectory(top) != 0){
            printf("this is directory %s\n", top);
            DIR *dir;
            struct dirent *entry;

            if ((dir = opendir(top)) != NULL) {

                while ((entry = readdir (dir)) != NULL) {

                    if(strcmp(entry->d_name, ".") == 0  || strcmp(entry->d_name, "..") == 0){
                        //skip current directory and moving up a directory
                        continue;
                    }
                    char* fullpath = calloc(strlen(top) + strlen(entry->d_name) + 1, sizeof(char));
                    strcat(fullpath, top);
                    strcat(fullpath, entry->d_name);
                    /* .. */

                    printf("full path is %s\n", fullpath);
                    stackPush(&s, fullpath);
                    //memset(temp, 0, 256);
                }


            }
            closedir(dir);
        }else if(isFile(top)){

            char md5string[33];
            char temp[512];
            strcpy(temp, top);
            char *md5 = getMD5(top, md5string);
            if(md5 != NULL){
                int result = isMD5InDB(md5);
                if(result == 1){
                    printf("%s is possibly a virus!\n", temp);
                }//else{
                 //   printf("%s is not a virus.\n", temp);
                //}
            }
        }
    }
    stackDestroy(&s);
    return 0;
}
