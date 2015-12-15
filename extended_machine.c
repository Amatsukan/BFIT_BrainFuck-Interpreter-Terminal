#include "utils.c"
#include "definitions.h"

void printEX(int printChar){
    if(printChar){
        printf("%c",((buf[aTape].pointer)[0]));
    }else
        printf("%u",(buf[aTape].pointer)[0]);

    char * dbgmsg = (char *)calloc(24, sizeof(char));
    strcat(dbgmsg, "print value in ");
    strcat(dbgmsg, &"Int\0Char"[(printChar*4)]);
    DEBUGr(dbgmsg);
}

void setEX(int setChar){
    if(setChar){
        int set = getchar();
        (buf[aTape].pointer)[0] = (set == '\0' || set == 13 || set == 10) ? getchar() : set;
    }else{
        scanf("%d",((buf[aTape].pointer)));
    }

    char * dbgmsg = (char *)calloc(22, sizeof(char));
    strcat(dbgmsg,"set value in ");
    strcat(dbgmsg,&"Int\0Char"[(setChar*4)]);
    DEBUGr(dbgmsg);
}

void zeroT(int tape){
    for(int i=MIN; i<=MAX; i++) buf[tape].mem[i] = 0  ;
    char dbg[9];
    sprintf(dbg, "zeroT #%d", tape);
    DEBUGr(dbg);
}

void zero(){
    for(int i=MIN; i<=MAX; i++) buf[aTape].mem[i] = 0  ;
    char dbg[9];
    sprintf(dbg, "zero #%d", aTape);
    DEBUGr(dbg);
}

void jump(int mod){
    if(buf[aTape].pos == MIN && mod < 0){
        buf[aTape].pos = MAX-mod+1;
        buf[aTape].pointer = &(buf[aTape].mem[MAX-mod+1]);
    } else if(buf[aTape].pos == MAX && mod > 0){
        buf[aTape].pos = MIN+mod-1;
        buf[aTape].pointer = &(buf[aTape].mem[MIN+mod-1]);
    }else{
        buf[aTape].pos += mod;
        (buf[aTape].pointer) += mod;
    }

}

void instSet(int mod, int value){

}

void instPrint(int mod){

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


int conditionalSet_errors(int err_code){
    if(err_code == 0) return 0;
    if(err_code == -1){
        char * prt_msg = (char *)calloc(115, sizeof(char));
        sprintf(prt_msg,"Invalid syntax : need & in final expression for conditionalSet.\n&(TYPECAST)(actual VALUE), (TYPECAST)(new VALUE)&");
        ERRORr(prt_msg);
        return err_code;
    }
    if(err_code == -2){
        char * prt_msg = (char *)calloc(105, sizeof(char));
        sprintf(prt_msg,"Invalid syntax : error in read conditionalSet syntax.\n&(TYPECAST)(actual VALUE), (TYPECAST)(new VALUE)&");
        ERRORr(prt_msg);
        return err_code;
    }
    if(err_code == -3){
        char * prt_msg = (char *)calloc(146, sizeof(char));
        sprintf(prt_msg,"Invalid syntax : expression without first typecast, \nC or c to char cast, I or i to int cast.\n&(TYPECAST)(actual VALUE), (TYPECAST)(new VALUE)&");
        ERRORr(prt_msg);
        return err_code;
    }
    if(err_code == -4){
        char * prt_msg = (char *)calloc(148, sizeof(char));
        sprintf(prt_msg,"Invalid syntax : expression without seccond typecast, \nC or c to char cast, I or i to int cast.\n&(TYPECAST)(actual VALUE), (TYPECAST)(new VALUE)&");
        ERRORr(prt_msg);
        return err_code;
    }

    return 0;
}

int  checkTypeCast(char c, int err_code){
    if(tolower(c) == 'i') return 0;
    if(tolower(c) == 'c') return 0;

    return conditionalSet_errors(err_code);
}

int conditionalSet(char * comm){
    //syntax: &(CONDITIONAL),(ACTION)&
    //(CONDITIONAL) -> (TYPECAST)(actual VALUE)
    //(ACTION) -> (TYPECAST)(new VALUE)

    //syntax = &(TYPECAST)(actual VALUE), (TYPECAST)(new VALUE)&
    //(TYPECAST) -> c|C|i|I
    //([new or actual]VALUE) -> a|b|C...(ascii chars or numbers)

    //ex: &cA,i9& if (char)'A', put (int)9

    /*
    comm table:

    position    |   semantics
    0           |   first "&"
    1           |   first type cast
    2           |   actual value in actual slot
    3           |   spacer ","
    4           |   seccond type cast
    5           |   value to swap with actual value
    6           |   last "&"
    */

    int level = 3;

    if(checkTypeCast(comm[1],-3)) level = 1;
    if(comm[2] == '\0'){
        level = 2;
        conditionalSet_errors(-2);
    }

    if(comm[3] == ',')
        level = 3;
    else{
        conditionalSet_errors(-2);
        return 3;
    }

    if(checkTypeCast(comm[4],-4)) level = 4;
    if(comm[5] == '\0'){
        level = 5;
        conditionalSet_errors(-3);
    }

    int finalE = 0;
    for(int i=1; i<=6; i++){
        if(comm[i] == '&'){
            finalE = i;
            level = 6;
            break;
        }
    }

    if(level != 3 || level != 6) return level;
    if(finalE != 6){
        conditionalSet_errors(-1);
        return finalE;
    }


    int isTrue = 0;

    if(tolower(comm[1]) == 'c'){
        if(((char)buf[aTape].pointer[0] == (char)comm[2])){
            isTrue = 1;
        }
    }else if(tolower(comm[1]) == 'i'){
        if((int)buf[aTape].pointer[0] == (int)comm[2]){
            isTrue = 1;
        }
    }

    if(isTrue){
        if(tolower(comm[4]) == 'c'){
            buf[aTape].pointer[0] = (char)comm[5];
        }else if(tolower(comm[4]) == 'i'){
            buf[aTape].pointer[0] = (int)comm[5];
        }
    }

    return level;
}

void changeTape(char * comm){

    if(tolower(comm[0]) == 'u'){//up tape
        swap(up);
    }
    else if(tolower(comm[0]) == 'd'){//down tape
        swap(down);
    }else{
        char * prt_msg = (char *)calloc(21, sizeof(char));
        sprintf(prt_msg,"Invalid syntax = %s\n", --comm);
        ERRORr(prt_msg);
    }
}

void extended_commands(char * comm){

    if(comm[0] == ':'){//print value as int
        printEX(0);
    }else if(comm[0] == ';'){//set value as int
        setEX(0);
    }else if(comm[0] == '#'){//change tape to:
        comm++;
        changeTape(comm);
    }else if(comm[0] == '0')//clean actual tape
    {
        zero();
    }else if(comm[0] == 'Z')//clean all tapes
    {
        int i;
        for (i = 0; i < nTapes; ++i)
            zeroT(i);
    }else if (comm[0] == '(')
    {
        /* instant set */
    }
    else if (comm[0] == '{')
    {
        /* Instant print */
    }else if (comm[0] == 'J' || comm[0] == 'j')//jump to specific position in tape
    {
        comm++;
        if (comm[0] == 'n' || comm[0] == 'N') //negative jump
        {
            jump((-1) * (int)comm[1]);
        }else if(comm[0] == 'p' || comm[0] == 'P') //positive jump
        {
            jump((int)comm[1]);
        }
//use: jn4 to jump 4 slots back, and jp8 to jump 8 slot

    }else if (comm[0] == 'S' )//print actual slot
    {
        printf("actual slot: %d\n", buf[aTape].pos);
    }
    else if(comm[0] == '&')//conditional set
    {
        comm = comm + conditionalSet(comm);
    }

}
