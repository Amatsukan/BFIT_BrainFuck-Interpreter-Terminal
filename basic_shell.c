#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX 2000
#define MIN 0

#define progName "BrainFuck"
#define PWD getcwd( NULL, 1024 )

int cont = 1;
int DEBUG = false;

struct BUFFER
{
    char * mem;

    int pos;

    char * pointer;
};

struct BUFFER buf;

init(){
    buf.mem = (char *) malloc(sizeof(char)*MAX);
    buf.pos = MAX/2;
    buf.pointer  = &(buf.mem[buf.pos]);
    read_history( ".hys" );
    int i;
    for(i=MIN; i<=MAX; i++) buf.mem[i] = '0';
}

void left();
void right();
void print();
void set();
void add();
void sub();
void loop();
int execR(char *);


void quit();
void sigCatcher(int);
char* get_comm(const char *);
char* get_arg(const char *);
int command(const char */* const char */);

int main(char ** args)
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
        snprintf( shell_prompt, sizeof( shell_prompt ), "%s:%s $ ", getenv( "USER" ), progName );

        // Display prompt and read input (NB: input must be freed after use)...
        input = readline( shell_prompt );

        // Check for EOF.
        if ( !input )
            break;


//        command(get_comm(input), get_arg(input));
        if( command( get_comm( input ) ) ){
            printf("Invalid Command\n");
        }

        // Add input to history.
        add_history( input );

        free( input );
    }
    return 0;
}

void left(){
    if(buf.pos == MIN){
        buf.pos = MAX;
        buf.pointer = &(buf.mem[MAX]);
    } else{
        buf.pos--;
        --(buf.pointer);
    }
}
void right(){
    if(buf.pos == MAX){
        buf.pos = MIN;
        buf.pointer = &(buf.mem[MIN]);
    } else{
        buf.pos++;
        ++(buf.pointer);
    }
}
void print(){
    printf("%c\n",(buf.pointer)[0]);
}

void set(){
    char set = getchar();
    (buf.pointer)[0] = (set == '\0' || set == 13 || set == 10) ? getchar() : set ;
}
void sub(){
    (*(buf.pointer))--;
    if(DEBUG){
        print("sub\n");
    }
}
void add(){
    (*(buf.pointer))++;
    if(DEBUG){
        print("add\n");
    }
}
void loop(char * inner){
    char statement = *(buf.pointer);
    printf("\n%c, inner:%c\n",statement, inner);
    while(statement != '0')
        execR(inner);
}

void quit(){
    printf("Bye!!");
    exit( EXIT_SUCCESS );
}

void sigCatcher(int sinal)
{
    write_history ( ".hys" );

    if( sinal == SIGINT ){
        quit();
    }
    if( sinal == SIGTERM ){
        cont=1;
    }
}

char* get_comm(const char * line){
    char* comm;

    int i;
    for(i=0; line[i] != 32 && line[i] != '\0' ; i++ );

    comm = ( char* ) malloc( sizeof( char )*++i );

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

    comm = ( char* ) malloc( sizeof( char )*( (++j)-(++i) ) );
    int m;
    for(m=0; line[i]!='\0'; i++, m++){
        comm[m]=line[i];
    }
    comm[++m] = '\0';
    return comm;
}

int command(const char * comm/*, const char * args*/){
    
    if( !strcmp( comm, "exit" ) ){
        quit();
        return 1;
    }
   
    execR(comm);
   
    return 0;
}

int execR(char * comm){
    
    int innerChars = 0;
    
    while(comm[0]!= '\0'){
        
        if(comm[0] == '>'){
            right();
        }else if(comm[0] == '<')
        {
            left();
        }else if(comm[0] == '.')
        {
            print();
        }else if(comm[0] == ',')
        {
            set();
        }else if(comm[0] == '+')
        {
            add();
        }else if(comm[0] == '-')
        {
            sub();
        }else if(comm[0]=='[')
        {
            char * prt = comm;
            while(prt[++innerChars]!=']');
            
            char subbuff[innerChars];
            memcpy( subbuff, &comm[1], innerChars);
            subbuff[innerChars-1] = '\0';
            loop(subbuff);
            innerChars = 0;
            
        }else if(comm[0]==']') continue;
        
        comm++;
    }
    comm++;
    return 0;
}
