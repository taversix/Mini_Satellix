#define CONFIG_PLUGINS ".\\config\\plugins.lua"
#define PLUGINS_DIR ".\\plugins\\"

#ifndef GLOBAL_H
#define GLOBAL_H

#include "luas.h"
#include "dict.h"
#include "bin.h"

extern Dict *global;
extern Bin *bif_bin;
extern Bin *sh_bin;
extern char *bif_words;
typedef struct
{
    int   success;
    char *output;
    char *err;
    void *addition
} Res;

void Init_Global();
void Init_Bins();

#endif