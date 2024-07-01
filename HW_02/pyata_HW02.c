/*
Name : Poojitha Yata
BlazerId : payata
Project : HW_02
filename : pyata_HW02.c
github : https://github.com/poojithayata/CS532/tree/main/HW_02
Compile command : make or gcc -o a pyata_HW02.c
execute command : ./a
execute command : ./a ../HW_02
execute command : ./a projects/project1
execute command : ./a -S
execute command : ./a -s 2024
execute command : ./a -f proj 4
execute command : ./a -t f
execute command : ./a -S -s 5024 -f proj 4
execute command : ./a -S -t d
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

typedef void MY_FUNCTION(char *filePath, int level, bool option_S,long int option_s_max_file_size, char *option_f_stringPattern, int option_f_max_depth, bool option_t, int option_tf);


char *symbolic_link_file(char *path){
    static char symbolic_Link_File[1024];
    ssize_t size = readlink(path, symbolic_Link_File, sizeof(symbolic_Link_File)-1);

    if(size != -1){
        symbolic_Link_File[size] = '\0';
        return symbolic_Link_File;
    }
    return NULL;

}

void file_permissions(mode_t mode){
    if((mode & S_IRUSR)){
        printf("r");
    }
    else{
        printf("_");
    }

    if(mode & S_IWUSR){
        printf("w");
    }
    else{
        printf("_");
    }

    if(mode & S_IXUSR){
        printf("x");
    }
    else{
        printf("_");
    }

    if(mode & S_IRGRP){
        printf("r");
    }
    else{
        printf("_");
    }

    if(mode & S_IWGRP){
        printf("w");
    }
    else{
        printf("_");
    }

    if (mode & S_IXGRP){
        printf("x");
    }
    else{
        printf("_");
    }
    
    if(mode & S_IROTH){
        printf("r");
    }
    else{
        printf("_");
    }
    

    if (mode & S_IWOTH)
    {
        printf("w");
    }
    else{
        printf("_");
    }

    if(mode & S_IXOTH){
        printf("x");
    }
    else{
        printf("_");
    }
}

void print_option_S(char *file_name, struct stat *status, bool option_S){
    if (option_S){
        if(S_ISDIR(status->st_mode)){
            printf("(0)");
        }
        else{
            printf("(%ld, ", (long)status->st_size);
            file_permissions(status->st_mode);
            char time[30];
            strncpy(time, ctime(&status->st_atime), sizeof(time));
            time[strlen(time) - 1] = '\0'; 
            printf(", %s)", time);
        }
    }
}



void Directories_and_Files(char *file_path, int level, bool option_S,long int option_s_max_file_size, char *option_f_stringPattern, int option_f_max_depth, bool option_t, int option_tf){

    /*
    printf("Option S = %d\n", option_S);
    if (option_S){
        printf("Option S\n");
    }
    else{
        printf("Not option S\n");
    }  
    */
    
    // /*

    struct dirent *d;
    DIR *directory = opendir(file_path);

    // If directory doesn't exist
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

        if(level < option_f_max_depth){

            char child_path[5024];
            struct stat status;

            snprintf(child_path, sizeof(child_path), "%s/%s", file_path, d->d_name);

            if (lstat(child_path, &status) == -1) {
                printf("Error...!\n");
                continue;
            }

            for(int i=0; i<level+1; i++){
                printf("   ");
            }

            if(S_ISDIR(status.st_mode)){
                // printf("%ld, ", (long)status.st_size);
                if((option_s_max_file_size >= status.st_size) && ((option_t == 0) || (option_t == 1 && option_tf == 0)) ){        
                    printf("%s ",d->d_name);
                    print_option_S(d->d_name, &status, option_S);
                }
                printf("\n");
                Directories_and_Files(child_path, level+1, option_S, option_s_max_file_size, option_f_stringPattern, option_f_max_depth, option_t, option_tf);
            }
            if((DT_REG == d->d_type) && (option_s_max_file_size >= status.st_size) && ((option_f_stringPattern == NULL) || (strstr(d->d_name, option_f_stringPattern) != NULL)) && ((option_t == 0) || (option_t == 1 && option_tf == 1)) ){    
                printf("%s ", d->d_name);
                print_option_S(d->d_name, &status, option_S);
                printf("\n");    
            }
            if((DT_LNK == d->d_type) && (option_s_max_file_size >= status.st_size) && ((option_f_stringPattern == NULL) || (strstr(d->d_name, option_f_stringPattern) != NULL)) && ((option_t == 0) || (option_t == 1 && option_tf == 1)) ){
                printf("%s {%s} ", d->d_name, symbolic_link_file(child_path));
                print_option_S(d->d_name, &status, option_S);
                printf("\n");
            }
                    
                
        }
        
    }

    // */
}

void pointerAsFunction(char *filePath, int level, bool option_S,long int option_s_max_file_size, char *option_f_stringPattern, int option_f_max_depth, bool option_t, int option_tf, MY_FUNCTION *pointer_function){
    pointer_function(filePath, 0, option_S, option_s_max_file_size, option_f_stringPattern, option_f_max_depth, option_t, option_tf);
}

int main(int argc, char *argv[]){

    bool option_S = false;
    bool option_s = false;
    long int option_s_max_file_size = 999999999;
    char *option_f_stringPattern = NULL;
    int option_f_max_depth = 99999999;
    bool option_t = false;
    int option_tf = 0, option_td = 0;

    int options;
    while((options = getopt(argc, argv, "Ss:f:t:")) != -1){
        switch(options){
            case 'S' :
                // S to print size, permissions, and last access time 
                // printf("Option S\n");
                option_S = true;
                break;
            case 's':
                // printf("Option s\n");
                // -s fileSize
                option_s = true;
                option_s_max_file_size = atoi(optarg);
                break;
            case 'f':
                // printf("Option f\n");
                // -f string pattern depth
                option_f_stringPattern = optarg;
                if (optind < argc){
                    option_f_max_depth = atoi(argv[optind]);
                    optind++;
                }
                break;
            case 't':
                // printf("Option t\n");
                option_t = true;
                if(strcmp(optarg, "f") == 0){
                    option_tf = 1;
                }
                else if(strcmp(optarg, "d") == 0){
                    option_tf = 0;
                }
                break;
        }
    }


    char *filePath;

    if(optind < argc){
        filePath = argv[optind];
    }
    else{
        filePath = ".";
    }

    printf("%s\n", filePath);
    // printf("S = %d s = %d %d f = %s %d t = %d %d\n", option_S, option_s, option_s_max_size, option_f_stringPattern, option_f_max_depth, option_tf, option_td);
    pointerAsFunction(filePath, 0, option_S, option_s_max_file_size, option_f_stringPattern, option_f_max_depth, option_t, option_tf, Directories_and_Files );
    // Directories_and_Files(filePath, 0, option_S, option_s_max_file_size, option_f_stringPattern, option_f_max_depth, option_t, option_tf);

    return 0;
}
