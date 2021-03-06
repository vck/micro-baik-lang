#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include "baik_header.h"
#include <emscripten.h>

void EMSCRIPTEN_KEEPALIVE repl_baik(char str[]){
    int str_size = strlen(str) + 2;
    pg.source = (char *)malloc(str_size);

    for(int i=0; i < str_size; i++){
        if(i == (str_size - 1)){
            pg.source[i] = '\0' ;
        }
        else if (i == (str_size - 2)){
            pg.source[i] = '\n' ;
        }
        else{
            pg.source[i] = str[i];
        }
    }

    pg.pt      = 0;
    pg.back_pt = 0;
    memset( &lex, 0, sizeof(BAIK_LEX) );
    ReadSource();

    pg.pt      = 0;
    pg.back_pt = 0;
    do {
    Interpreter();
    }while( lex.type != _EOF );
    BaikGarbageCollection();
}