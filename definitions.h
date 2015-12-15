#ifndef _DEF_
#define _DEF_

#include <readline/readline.h>
#include <readline/history.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>

#define stahp return;

#define nTapes 5
static int aTape = 0;

#define MAX 2000
#define MIN 0

typedef unsigned int uint;

static int EXTENDED = 0; //if 1, turn B.F.I.T in B.F++.I.T

struct BUFFER
{
    uint * mem;

    uint pos;

    uint * pointer;
};

static struct BUFFER* buf;

#endif
