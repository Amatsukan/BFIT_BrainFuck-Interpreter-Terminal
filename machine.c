#include <readline/readline.h>
#include <readline/history.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>

#include "utils.c"

#define stahp return;

#define nTapes 5
int aTape = 0;

#define MAX 2000
#define MIN 0

int EXTENDED = 0; //if 1, turn B.F.I.T in B.F++.I.T

struct BUFFER
{
    uint * mem;

    uint pos;

    uint * pointer;
};

struct BUFFER* buf;

void mvleft(){
    if(buf[aTape].pos == MIN){
        buf[aTape].pos = MAX;
        buf[aTape].pointer = &(buf[aTape].mem[MAX]);
    } else{
        buf[aTape].pos--;
        --(buf[aTape].pointer);
    }
    DEBUGr("move left");
}
void mvright(){
    if(buf[aTape].pos == MAX){
        buf[aTape].pos = MIN;
        buf[aTape].pointer = &(buf[aTape].mem[MIN]);
    } else{
        buf[aTape].pos++;
        ++(buf[aTape].pointer);
    }

    DEBUGr("move rigth");
}
void print(int printChar){

    if(printChar){
        printf("%c",((buf[aTape].pointer)[0]));
    }else
        printf("%u",(buf[aTape].pointer)[0]);

    char * dbgmsg = (char *)calloc(24, sizeof(char));
    strcat(dbgmsg, "print value in ");
    strcat(dbgmsg, "Int\0Char"+(printChar*4));
    DEBUGr(dbgmsg);
}

void set(int setChar){
    if(setChar){
        int set = getchar();
        (buf[aTape].pointer)[0] = (set == '\0' || set == 13 || set == 10) ? getchar() : set;
    }else{
        scanf("%d",((buf[aTape].pointer)));
    }


    char * dbgmsg = (char *)calloc(23, sizeof(char));
    strcat(dbgmsg,"set value in  ");
    strcat(dbgmsg,"Int\0Char"+(setChar*4));
    DEBUGr(dbgmsg);
}

void sub1(){
    if(*(buf[aTape].pointer)== 0){
        *(buf[aTape].pointer)=255;
    }else
    (*(buf[aTape].pointer))--;

    DEBUGr("sub action");
}
void add1(){
    if(*(buf[aTape].pointer)== 255){
        *(buf[aTape].pointer)=0;
    }else
    (*(buf[aTape].pointer))++;

    DEBUGr("add action");
}

void quit(){
    printf("\nBye!!\n");
    int i;
    for (i = 0; i < nTapes; ++i)
    {
        free(buf[i].mem);
    }
    free(buf);
    exit( EXIT_SUCCESS );
}

void zeroT(int type){
    int i;
    for(i=MIN; i<=MAX; i++) buf[type].mem[i] = 0  ;
    char dbg[9];
    sprintf(dbg, "zeroT #%d", type);
    DEBUGr(dbg);
}

void zero(){
    int i;
    for(i=MIN; i<=MAX; i++) buf[aTape].mem[i] = 0  ;
    char dbg[9];
    sprintf(dbg, "zero #%d", aTape);
    DEBUGr(dbg);
}

enum swp{
    up, down
};

void swap(enum swp op){
    switch(op){
        case up:
            DEBUGr("Swap to up");
            if (aTape == nTapes-1){
                aTape = 0;
            }else{
                aTape++;
            }
            stahp
        case down:
            DEBUGr("Swap to down");
            if (aTape == 0){
                aTape = nTapes-1;
            }else{
                aTape--;
            }
    }
}

void init(){
    setlocale(LC_ALL, "");

    buf = (struct BUFFER*) calloc(nTapes, sizeof(struct BUFFER));
    int i;
    for (i = 0; i < nTapes; ++i)
    {
        buf[i].mem = (uint*) malloc(sizeof(uint)*MAX);
        buf[i].pos = MAX/2;
        buf[i].pointer  = &(buf[i].mem[buf[i].pos]);
        zeroT(i);
    }
    read_history( ".hys" );
}

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
            print(1);
        }else if(comm[0] == ',')
        {
            set(1);
        }else if(comm[0] == '+')
        {
            add1();
        }else if(comm[0] == '-')
        {
            sub1();
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

        }else if(EXTENDED){

            if(comm[0] == ':'){
                print(0);
            }else if(comm[0] == ';'){
                set(0);
            }else if(comm[0] == '#'){
                comm++;
                if(comm[0] == 'u' || comm[1] == 'U'){
                    swap(up);
                }
                else if(comm[0] == 'd' || comm[1] == 'D'){
                    swap(down);
                }

            }else if(comm[0] == '0')
            {
                zero();
            }else if(comm[0] == 'Z')
            {
                int i;
                for (i = 0; i < nTapes; ++i)
                    zeroT(i);
            }
        }

        comm++;
    }
    comm++;
    return 0;
}

void loop(char * inner){
    uint * statement = &(buf[aTape].pointer[0]);
    DEBUGr("loop init");

    while(!(statement[0] <= 0))
    {
        if(*statement == 0) break;
        execR(inner);
    }

    DEBUGr("loop finish");
}
