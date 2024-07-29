/*
Name : Poojitha Yata
BlazerId : payata
Project : Lab_010
filename : pyata_Lab10.c
github : https://github.com/poojithayata/CS532/tree/main/Lab_10
Compile command : gcc -o a pyata_Lab10.c
execute command : ./a
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void log_Function(const char *cmd, time_t s_time, time_t e_time){
    FILE *lf = fopen("output.log", "a");
    if(lf == NULL){
        printf("Failed to open log file.\n");
        exit(-1);
    }

    char s_t_str[26];
    char e_t_str[26];
    
    strncpy(s_t_str, ctime(&s_time), 26);
    strncpy(e_t_str, ctime(&e_time), 26);

    s_t_str[strcspn(s_t_str, "\n")] = 0;
    e_t_str[strcspn(e_t_str, "\n")] = 0;

    fprintf(lf, "%s\t%s\t%s\n", cmd, s_t_str, e_t_str);
    fclose(lf);
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("File not specified properly.\n");
        exit(-1);
    }

    FILE *fp = fopen(argv[1], "r");
    if(fp ==  NULL){
        printf("Error opening the file.\n");
        exit(-1);
    }

    char ln[1024];
    while(fgets(ln, sizeof(ln), fp)){
        ln[strcspn(ln, "\n")] = 0;

        time_t s_Time = time(NULL);

        pid_t pid = fork();

        if(pid == 0){
            char o_fname[1024];
            char e_fname[1024];
            snprintf(o_fname, sizeof(o_fname), "%d.out", getpid());
            snprintf(e_fname, sizeof(e_fname), "%d.err", getpid());
            
            FILE *o_file = freopen(o_fname, "w", stdout);
            FILE *e_file = freopen(e_fname, "w", stderr);
            if (o_file == NULL || e_file == NULL){
                printf("Failed to open output/error files.\n");
                exit(-1);
            }

            // dup2(o_file, STDOUT_FILENO);
            // close(o_file);
            // dup2(e_file, STDERR_FILENO);
            // close(e_file);

            char *args[512];
            char *token = strtok(ln, " ");

            int i = 0;
            while(token != NULL){
                args[i] = token;
                i++;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            execvp(args[0], args);
            perror("execvp"); 
            exit(-1);

        }
        else if (pid > 0){
            int status;
            waitpid(pid, &status, 0);
            time_t e_time = time(NULL);
            log_Function(ln, s_Time, e_time);
        }
        else{
            printf("Failed to fork.\n");
            exit(-1);
        }
    }

    fclose(fp);
    return 0;

}