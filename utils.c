#include <stdio.h>
#include "colors.h"

#define uint unsigned int
#define t_uint(x) (unsigned int)(x)

#define PWD getcwd( NULL, 1024 )


int DEBUG = 0; //if 1 = turn on DEBUG mode

void Help(){
    printf("\n\n\nB.F.I.T. = BrainFuck Interpreter Terminal\n");
    printf("WARNING: When you use brainfuck operators, this terminal discard all characters non BF symbols\n");
    printf("Terminal commands:\n\tprint: switch print mode to int or char\n");
    printf("\tdebug: turn debug mode ON/OFF\n");
    printf("\thelp: show those informations\n");
    printf("\textend: turn B.F.I.T. in B.F++.I.T.\n");
    printf("BrainFuck Operators:\n");
    printf("    '>' = increment the data pointer (to point to the next cell to the right).\n");
    printf("    '<' = decrement the data pointer (to point to the next cell to the left).\n");
    printf("    '+' = increment (increase by one) the byte at the data pointer.\n");
    printf("    '-' = decrement (decrease by one) the byte at the data pointer.\n");
    printf("    '.' = output the byte at the data pointer (print as char).\n");
    printf("    ',' = accept one byte of input, storing its value in the byte at the data pointer (set as char).\n");
    printf("    '[' = if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.\n");
    printf("    ']' = if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.\n");
    printf("BrainFuck ++ Operators:\n");
    printf("    ':' = output the byte at the data pointer (print as integer).\n");
    printf("    ';' = accept one byte of input, storing its value in the byte at the data pointer (set as integer).\n");
    printf("    '#?'= swap the tape.\n");
    printf("        case ? is u or U, the up tape turns the current tape\n");
    printf("        case ? is d or D, the down tape turns the current tape\n");
    printf("        BF++ haves 5 tapes.\n");
    printf("    '0' = turn all slots of the actual tape to 0\n");
    printf("    'Z' or 'z' = turn all slots of all tapes to 0\n");
    printf("    'Jxy' or 'jxy' = jump to an specific slot in the actual tape\n");
    printf("        case x is p or P, actualstot <- actualstot + y\n");
    printf("        case x is n or N, actualstot <- actualstot - y\n");
    printf("             y shall be a single character , its value is the numeric value it converted to integer\n");
    printf("\n\nBFIT was created by: Amatsukan\n");
    printf("/*\n\n* ----------------------------------------------------------------------------\n");
    printf("* \"THE BEER-WARE LICENSE\" (Revision 42):\n");
    printf("* <luiz.ferreira@khomp.com> wrote this file. As long as you retain this notice you\n");
    printf("* can do whatever you want with this stuff. If we meet some day, and you think\n");
    printf("* this stuff is worth it, you can buy me a beer in return Luiz Carlos{Amatsukan}\n");
    printf("* ----------------------------------------------------------------------------*/\n\n");



    printf("-[------->+<]>+++.++[-->+++<]>.------------.-[--->+<]>++.++[---->+<]>+.---[->++<]>.++[--->++<]>+.\n\n\n");
}

void DEBUGr(const char * msg){
    if(DEBUG){
        printf("%s%s%s\n", CYN, msg, NRM);
    }
}

void ERRORr(const char * msg){
    printf("\n %s%s%s%s", BOLD ,RED, msg, NRM);
}

void WARNNINGr(const char * msg){
    printf("\n %s %s %s", YEL, msg, NRM);
}

void msg(const char * msg){
    printf("\n %s %s", msg, NRM);
}

