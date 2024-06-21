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
# include <libgen.h>
# include <sys/wait.h>
# include <ctype.h>
# include <time.h>


char *symbolic_link_file(char *path){
    static char symbolic_Link_File[1024];
    ssize_t size = readlink(path, symbolic_Link_File, sizeof(symbolic_Link_File)-1);

    if(size != -1){
        symbolic_Link_File[size] = '\0';
        return symbolic_Link_File;
    }
    return NULL;

}

void Directories_and_Files(char *file_path, int level){
    struct dirent *d;
    DIR *directory = opendir(file_path);

    // If directory doesn't exits
    if (directory == NULL){
        printf("This directory might not exist, error....!\n");
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
        if(DT_REG == d->d_type){
            printf("%s\n", d->d_name);
        }
        if(DT_LNK == d->d_type){
            printf("%s -> %s\n", d->d_name, symbolic_link_file(child_path));
        }

    }
}


int main(int argc, char *argv[]){


    int opt;
    int max_file_size;
    char *file_type = NULL;
    int deep;

    while((opt = getopt(argc, argv, "Ss:f::")) != -1){
        switch(opt){
            case 'S':
                printf("S");
                break;
            case 's':
                printf("s");
                max_file_size = atoi(optarg);
                break;
            case 'f':
                printf("f");
                file_type = optarg;
                deep = atoi(argv[optind++]);
                break;
        }
    }

    char *filePath;

    if (argc <= optind){
        filePath = ".";
    }
    else{
        filePath = argv[1];
    }

    Directories_and_Files(filePath, 0);

    return 0;
}
