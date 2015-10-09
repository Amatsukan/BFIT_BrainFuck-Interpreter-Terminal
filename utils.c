#include <stdio.h>

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
    printf("BrainFuck Operators:\n");
    printf("    '>' = increment the data pointer (to point to the next cell to the right).\n");
    printf("    '<' = decrement the data pointer (to point to the next cell to the left).\n");
    printf("    '+' = increment (increase by one) the byte at the data pointer.\n");
    printf("    '-' = decrement (decrease by one) the byte at the data pointer.\n");
    printf("    '.' = output the byte at the data pointer.\n");
    printf("    ',' = accept one byte of input, storing its value in the byte at the data pointer.\n");
    printf("    '[' = if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.\n");
    printf("    ']' = if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.\n");
    printf("\n\nBFIT was created by: Amatsukan\n");
    printf("/*\n\n* ----------------------------------------------------------------------------\n");
    printf("* \"THE BEER-WARE LICENSE\" (Revision 42):\n");
    printf("* <phk@FreeBSD.ORG> wrote this file. As long as you retain this notice you\n");
    printf("* can do whatever you want with this stuff. If we meet some day, and you think\n");
    printf("* this stuff is worth it, you can buy me a beer in return Luiz Carlos{Amatsukan}\n");
    printf("* ----------------------------------------------------------------------------*/\n\n");



    printf("-[------->+<]>+++.++[-->+++<]>.------------.-[--->+<]>++.++[---->+<]>+.---[->++<]>.++[--->++<]>+.\n\n\n");
}

void DEBUGr(const char * msg){
    if(DEBUG){
        printf("\n%s\n",msg);
    }
}
