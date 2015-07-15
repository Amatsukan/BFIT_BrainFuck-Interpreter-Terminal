#ifndef __NCURSES_H
#include <curses.h>
#endif

#define BLACK       0
#define RED         1
#define GREEN       2
#define BROWN       3
#define BLUE        4
#define MAGENTA     5
#define CYAN        6
#define LIGHTGRAY   7
#define DARKGRAY    8
#define LIGHTRED    9
#define LIGHTGREEN  10
#define YELLOW      11
#define LIGHTBLUE   12
#define PINK        13
#define LIGHTCYAN   14
#define WHITE       15

#define DEFAULT_PAIR 57

int initconio(void);
int endconio(void);
int clrscr(void);
int textcolor(short color);
int textbackground(short color);
int gotoxy(int x, int y);
int wherex(void);
int wherey(void);

short cur_pair;
int cur_bold;

int initconio(void)
{
    int f, b;
    short p;
    initscr();
    start_color();
    p = 1;
    for(f = 0; f < 8; f++)
        for(b = 0; b < 8; b++, p++)
            init_pair(p, f%8, b%8);
    cur_pair = DEFAULT_PAIR;
    cur_bold = 0;
    bkgd(COLOR_PAIR(cur_pair));
    color_set(cur_pair, NULL);
    attr_off(A_BOLD, NULL);
    return 0;
}

int endconio(void)
{
    endwin();
    return 0;
}

int clrscr(void)
{
    bkgd(COLOR_PAIR(cur_pair));
    if(cur_bold == 1)
        attr_on(A_BOLD, NULL);
    else
        attr_off(A_BOLD, NULL);
    clear();
    return 0;
}

int textcolor(short color)
{
    short f, b, x, y;
    short p;
    pair_content(cur_pair, &f, &b);
    p = 1;
    for(x = 0; x < 8; x++)
        for(y = 0; y < 8; y++, p++)
            if((x == (color%8))&&(y == b))
                cur_pair = p;
    color_set(cur_pair, NULL);
    if(color >= 8)
    {
        cur_bold = 1;
        attr_on(A_BOLD, NULL);
    }
    else
    {
        cur_bold = 0;
        attr_off(A_BOLD, NULL);
    }
    return 0;
}

int textbackground(short color)
{
    short f, b, x, y;
    short p;
    pair_content(cur_pair, &f, &b);
    p = 1;
    for(x = 0; x < 8; x++)
        for(y = 0; y < 8; y++, p++)
            if((x == f)&&(y == (color%8)))
                cur_pair = p;
    color_set(cur_pair, NULL);
    return 0;
}

int gotoxy(int x, int y)
{
    move(x - 1, y - 1);
    return 0;
}

int wherex(void)
{
    int x, y;
    getyx(stdscr, x, y);
    return x + 1;
}

int wherey(void)
{
    int x, y;
    getyx(stdscr, x, y);
    return y + 1;
}