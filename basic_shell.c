#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "conio.h"

int cont = 1;


void quit();
void sigCatcher(int sinal);
void init();
char* get_comm(const char * line);
char* get_arg(const char * line);
int compare(const char * c1, const char * c2);
int command(const char * comm, const char * args);


int main()
{
    init();
    int s;
    for (s=1; s<35; s++){
        signal(s, sigCatcher);
    }

    char* input, shell_prompt[100];

    // Configure readline to auto-complete paths when the tab key is hit.
    rl_bind_key('\t', rl_complete);

    while(cont) {
        // Create prompt string from user name and current working directory.
        snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", getenv("USER"), getcwd(NULL, 1024));

        // Display prompt and read input (NB: input must be freed after use)...
        input = readline(shell_prompt);

        // Check for EOF.
        if (!input)
            break;



//        if(!command(get_comm(input),get_arg(input))){
//            print("\nInvalid Command\n");
//        }

        // Add input to history.
        add_history(input);

        free(input);
    }
    return 0;
}

void quit(){
    printf("\nBye!!");
    exit(EXIT_SUCCESS);
}

void sigCatcher(int sinal)
{
    write_history (".hys");

    if(sinal == SIGINT){
        quit();
    }
    if(sinal == SIGTERM){
        cont=1;
    }
}

void init(){
    read_history(".hys");
}

char* get_comm(const char * line){
    char* comm;

    int i;
    for(i=0; line[i] != 32 && line[i] != '\0' ; i++ );

    comm = (char*) malloc(sizeof(char)*++i);

    int j;
    for(j=0; j<i; j++ ){
        comm[j]=line[j];
    }
    return comm;
}

char* get_arg(const char * line){
    char* comm;

    int i;
    for(i=0; line[i] != 32 && line[i] != '\0' ; i++ );
    int j;
    for(j=i; line[j] != '\0' ; j++ );

    if(line[i]=='\0') return "";

    comm = (char*) malloc(sizeof(char)*((++j)-(++i)));
    int m;
    for(m=0; line[i]!='\0'; i++, m++){
        comm[m]=line[i];
    }
    comm[++m] = '\0';
    return comm;
}