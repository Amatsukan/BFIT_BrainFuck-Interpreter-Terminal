#include <signal.h>

#include "machine.c"



int execR(char *);


void quit();
void sigCatcher(int);
void command(char *);
const char* get_comm(char * line);
const char* get_args(char * line);
void print(int printChar);
void Help();


int main(int argv, char ** args)
{
    init();
    int s;
    for (s=1; s<35; s++){
        signal(s, sigCatcher);
    }

    char* input, shell_prompt[100];

    rl_bind_key('\t', rl_complete);

    while(42) {

        if(EXTENDED)
            snprintf( shell_prompt, sizeof( shell_prompt ), "\n%s%s(%s:[%s])~>{%s ",BOLD,GRN, getenv( "USER" ), "B.F++.I.T.", BLK  );
        else
            snprintf( shell_prompt, sizeof( shell_prompt ), "\n%s%s(%s:[%s])~>{%s %s ",BOLD,WHT, getenv( "USER" ), "B.F.I.T.", NRM, WHT );

        input = readline( shell_prompt );

        if ( !input )
            break;

        char * comm = (char *)calloc(strlen(input), sizeof(char));

        strcat(comm ,get_comm(input));
        strcat(comm ,get_args(input));

        command(comm);

        free(comm);

        add_history( input );

        free( input );
    }
    return 0;
}


void sigCatcher(int sinal)
{
    write_history ( ".hys" );

    if( sinal == SIGINT ){
        quit();
    }
    if( sinal == SIGTERM ){

    }
}

const char* get_comm(char * line){
    char* comm;
    int i;
    for(i=0; line[i] != 32 && line[i] != '\0' ; i++ );

    comm = ( char* ) malloc( sizeof( char )*++i );

    for(int j=0; j<i; j++ ){
        comm[j]=line[j];
    }
    return comm;
}

const char* get_args(char * line){
    char* comm;
    int i;
    for(i=0; line[i] != 32 && line[i] != '\0' ; i++ );
    int j;
    for(int j=i; line[j] != '\0' ; j++ );

    if(line[i]=='\0') return "";

    comm = ( char* ) malloc( sizeof( char )*( (++j)-(++i) ) );

    int m;
    for(m=0; line[i]!='\0'; i++, m++){
        comm[m]=line[i];
    }
    comm[++m] = '\0';
    return comm;
}

void command(char * comm/*, const char * args*/){

    if( !strcmp( comm, "exit" ) ){
        quit();
    }

    if( !strcmp( comm, "help" ) ){
        Help();
        stahp
    }

    if( !strcmp( comm, "debug" ) ){
        DEBUG = !(DEBUG);
        printf("\nDEBUG MODE: %s\n",&("OFF\0ON")[(4*DEBUG)]);
        stahp
    }

    if( !strcmp( comm, "extend" ) ){
        EXTENDED = !(EXTENDED);
        printf("\nextended brainfuck: %s\n",&("OFF\0ON")[(4*EXTENDED)]);
        stahp
    }

    execR(comm);
    stahp
}
