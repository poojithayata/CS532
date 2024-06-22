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
# include <stdbool.h>


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
            printf("%s {%s}\n", d->d_name, symbolic_link_file(child_path));
        }

    }
}


int main(int argc, char *argv[]){

    bool option_S = false;
    int option_s_max_size = -1;
    char *option_f_stringPattern = NULL;
    int option_f_max_depth = -1;
    bool option_t = false;
    int option_tf = 0, option_td = 0;

    int options;
    while((options = getopt(argc, argv, "Ss:f::t:")) != -1){
        switch(options){
            case 'S' :
                // printf("Option S\n");
                option_S = true;
                break;
            case 's':
                // printf("Option s\n");
                option_s_max_size = atoi(optarg);
                break;
            case 'f':
                // printf("Option f\n");
                option_f_stringPattern = optarg;
                if (optind < argc){
                    option_f_max_depth = atoi(argv[optind]);
                    optind++;
                }
                break;
            case 't':
                // printf("Option t\n");
                if(strcmp(optarg, "f") == 0){
                    option_tf = 1;
                }
                else if(strcmp(optarg, "d") == 0){
                    option_td = 1;
                }
                break;
        }
    }


    char *filePath;

    if (argc >= optind){
        filePath = ".";
    }
    else{
        filePath = argv[optind];
    }

    printf("filePath = %s\n", filePath);
    printf("S = %d s = %d f = %s %d t = %d %d\n", option_S, option_s_max_size, option_f_stringPattern, option_f_max_depth, option_tf, option_td);
    // Directories_and_Files(filePath, 0);

    return 0;
}
