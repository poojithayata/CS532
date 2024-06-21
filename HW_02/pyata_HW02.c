/*
filename : pyata_Lab01.c (Implemented pointer for smallerThanIndex())
github : https://github.com/poojithayata/CS532/tree/main/HW_02
Compile command : gcc -o a pyata_HW02.c
execute command : ./a
*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
#include <libgen.h>

void Directories_and_Files(char *file_path, int level){
    struct dirent *d;
    DIR *directory = opendir(file_path);

    // If directory doesn't exits
    if (directory == NULL){
        printf("This directory might not exist, error....!");
        return;
    }

    while((d = readdir(directory)) != NULL){
        if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0){
            continue;
        }
        // if(strcmp(d->d_name, '..') == 0){
        //     continue;
        // }
        char child_path[5024];
        struct stat status;

        snprintf(child_path, sizeof(child_path), "%s/%s", file_path, d->d_name);

        if (lstat(child_path, &status) == -1) {
            printf("Error...!\n");
            continue;
        }

        for(int i=0; i<level; i++){
            printf("   ");
        }

        if(S_ISDIR(status.st_mode)){
            printf("%s\n",d->d_name);
            Directories_and_Files(child_path, level+1);
        }
        if(S_ISLNK(status.st_mode)){
            printf("%s->\n", d->d_name);
        }
        if(S_ISREG(status.st_mode)){
            printf("%s\n", d->d_name);
        }

    }
}


int main(int argc, char *argv[]){

    char *filePath;

    if (argc == 1){
        filePath = ".";
    }
    else{
        filePath = argv[1];
    }

    Directories_and_Files(filePath, 0);

    return 0;
}
