#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#define MAXLINE 200
#define MAXARG 20

extern char **environ;
void env(void){
    int i;
    for(i=0;environ[i]!=NULL;i++){
        printf("%s\n",environ[i]);
    }
}
void exitsh(int status){
    _exit(status);
}
void execute(char *arg[]){
    pid_t pid;
    int status;
    pid=fork();
    if(pid>0){
        wait(&status);
    } else if (pid==0) {
        execvp(arg[0],arg);
        printf("Komanda nav atrasta\n");
        exitsh(0);
    } else {
        printf("Kluda fork() sistemas izsaukuma\n");
    }
}

void help() {
    printf("ToyShell help\n\n");
    printf("\tenv\t\tshows environment variable\n");
    printf("\texit\t\texits toyshell\n");
    printf("\t[command]\t\tsome basic UNIX commands can be run\n");
    printf("\tcd [dir]\t\tbasic change directory, function implemented\n");
}

void changeDir(char * dir, char * currentDir) {
    chdir(dir);
    getcwd(currentDir, sizeof(currentDir) * MAXLINE);
}

void addEnv(char * args[]) {
    if (strcmp(args[0], "setenv") != 0) {
        printf("Incorrect environment settings\n");
        exitsh(0);
    }
    
    if (args[1] == NULL || args[2] == NULL) {
        printf("No envrionment values passed");
        exitsh(0);
    }
    
    char * env_string = malloc(strlen(args[1]) + strlen(args[2]) + 2);
    char ss[2] = "=";
    strcpy(env_string, args[1]);
    strcat(env_string, ss);
    strcat(env_string, args[2]);
    
    putenv(env_string);
}
int main (void){
	char cmd[MAXLINE];
    char *cmdp;
    char *av[MAXARG];
    char currentDir[MAXLINE] = "";
    char cwd[MAXLINE];
    getcwd(cwd, sizeof(cwd));
    char dirChanged = 0;
    
    int i;
    while(1){
         printf("$toyshell");
         // Show additional path only if differs from starting path
         if (dirChanged == 1) {
            printf(" %s", currentDir);
         }
         printf("$> ");
         
         fgets(cmd,sizeof(cmd),stdin);
         if(strcmp(cmd,"env\n")==0){
            env();
         } else if(strcmp(cmd,"help\n")==0){
            help();
         } else if(strcmp(cmd,"exit\n")==0){
            exitsh(0);
         } else {
            cmdp=cmd;
            for(i=0;i<MAXARG;i++){
               av[i]=strtok(cmdp," \t\n");
               cmdp=NULL;
            }
            
            // Implemented cd function as alternative command
            if (strcmp(av[0], "cd") == 0) {
                changeDir(av[1], currentDir);
                if (strcmp(cwd, currentDir) == 0) {
                    dirChanged = 0;
                } else {
                    dirChanged = 1;
                }
            } else if (strcmp(av[0], "setenv") == 0) {
                addEnv(av);
            } else {
                execute(av);
            }
        }
    }
    
    return(0);
}
