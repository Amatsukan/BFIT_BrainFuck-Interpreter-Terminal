#include "extended_machine.c"
#include <stdlib.h>

void init(){
    setlocale(LC_ALL, "");

    buf = (struct BUFFER*) calloc(nTapes, sizeof(struct BUFFER));

    for (int i = 0; i < nTapes; ++i)
    {
        buf[i].mem = (uint*) malloc(sizeof(uint)*MAX);
        buf[i].pos = MAX/2;
        buf[i].pointer  = &(buf[i].mem[buf[i].pos]);
        zeroT(i);
    }
    read_history( ".hys" );
}

void quit(){
    printf("\nBye!!\n");
    for (int i = 0; i < nTapes; ++i)
    {
        free(buf[i].mem);
    }
    free(buf);
    exit( EXIT_SUCCESS );
}


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

    if(EXTENDED)
        printEX(printChar);
    else
        printf("%c",((buf[aTape].pointer)[0]));

}

void set(int setChar){

    if(EXTENDED)
        setEX(setChar);
    else{
        int set = getchar();
        (buf[aTape].pointer)[0] = (set == '\0' || set == 13 || set == 10) ? getchar() : set;
    }
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

void loop(char*);

int execR(char * comm){

    int innerChars = 0;

    while(comm[0]!= '\0'){ //END OF COMMAND '\0'

        if(comm[0] == '>'){ //move rigth
            mvright();
        }else if(comm[0] == '<')//move left
        {
            mvleft();
        }else if(comm[0] == '.')//print value as CHAR type
        {
            print(1);
        }else if(comm[0] == ',')//set value as CHAR type
        {
            set(1);
        }else if(comm[0] == '+')//actual_value++
        {
            add1();
        }else if(comm[0] == '-')//actual_value--
        {
            sub1();
        }else if(comm[0]=='[')//begin of loop'block
        {
            char * prt = comm;
            while(prt[++innerChars]!=']');

            char subbuff[innerChars];
            memcpy( subbuff, &comm[1], innerChars);
            subbuff[innerChars-1] = '\0';
            loop(subbuff);
            innerChars = 0;
            comm += strlen(subbuff);

        }else if(EXTENDED){//B.F++.I.T.
            extended_commands(comm);
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
