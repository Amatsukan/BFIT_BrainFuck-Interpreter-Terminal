#include <readline/readline.h>
#include <readline/history.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>

#include "utils.c"

#define stahp return;
#define MAX 2000
#define MIN 0

struct BUFFER
{
    uint * mem;

    uint pos;

    uint * pointer;
};

struct BUFFER buf;

void mvleft(){
    if(buf.pos == MIN){
        buf.pos = MAX;
        buf.pointer = &(buf.mem[MAX]);
    } else{
        buf.pos--;
        --(buf.pointer);
    }
    DEBUGr("move left");
}
void mvright(){
    if(buf.pos == MAX){
        buf.pos = MIN;
        buf.pointer = &(buf.mem[MIN]);
    } else{
        buf.pos++;
        ++(buf.pointer);
    }

    DEBUGr("move rigth");
}
void print(int printChar){
    if(printChar){
        printf("%c",((buf.pointer)[0]));
    }else
        printf("%u",(buf.pointer)[0]);

    char * dbgmsg;
    strcat(dbgmsg, "print value in ");
    strcat(dbgmsg, "Char\0Int"+(printChar*5));
    DEBUGr(dbgmsg);
}

void set(int setChar){
    int set = getchar();

    (buf.pointer)[0] = (set == '\0' || set == 13 || set == 10) ? getchar() : set;

    char * dbgmsg;
    strcat(dbgmsg,"set value in  ");
    strcat(dbgmsg,"Char\0Int"+(setChar*5));
    DEBUGr(dbgmsg);
}

void sub1(){
    if(*(buf.pointer)== 0){
        *(buf.pointer)=255;
    }else
    (*(buf.pointer))--;

    DEBUGr("sub action");
}
void add1(){
    if(*(buf.pointer)== 255){
        *(buf.pointer)=0;
    }else
    (*(buf.pointer))++;

    DEBUGr("add action");
}

void quit(){
    printf("\nBye!!\n");
    free(buf.mem);
    exit( EXIT_SUCCESS );
}

void zero(){
    int i;
    for(i=MIN; i<=MAX; i++) buf.mem[i] = 0  ;
}

void init(){
    setlocale(LC_ALL, "");
    buf.mem = (uint *) malloc(sizeof(uint)*MAX);
    buf.pos = MAX/2;
    buf.pointer  = &(buf.mem[buf.pos]);
    read_history( ".hys" );
    zero();
}

// void AZero(){
//     if(AZERO){
//         zero();
//         DEBUGr("AZERO");
//     }
// }

void loop(char *); // foward declaration

int execR(char * comm){

    int innerChars = 0;

    while(comm[0]!= '\0'){

        if(comm[0] == '>'){
            mvright();
        }else if(comm[0] == '<')
        {
            mvleft();
        }else if(comm[0] == '.')
        {
            print(0);
        }else if(comm[0] == ',')
        {
            set(0);
        }else if(comm[0] == '+')
        {
            add1();
        }else if(comm[0] == '-')
        {
            sub1();
        }else if(comm[0] == '0')
        {
            zero();
        }else if(comm[0]=='[')
        {
            char * prt = comm;
            while(prt[++innerChars]!=']');

            char subbuff[innerChars];
            memcpy( subbuff, &comm[1], innerChars);
            subbuff[innerChars-1] = '\0';
            loop(subbuff);
            innerChars = 0;
            comm += strlen(subbuff);

        }else if(comm[0] == ':'){
            print(1);
        }else if(comm[0] == ';'){
            set(1);
        }else if(comm[0] == '#'){
            //swap the actual buffer
        }

        comm++;
    }
    comm++;
    return 0;
}

void loop(char * inner){
    uint * statement = &(buf.pointer[0]);
    DEBUGr("loop init");

    while(!(statement[0] <= 0))
    {
        if(*statement == 0) break;
        execR(inner);
    }

    DEBUGr("loop finish");
}
