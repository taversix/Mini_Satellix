#ifndef DICT_H
#define DICT_H
#include "include.h"
typedef struct
{
    char    type;        // s as char, n as number, b as bool, x as null
    double  valuenumber;
    int     valuebool;
    char   *valuestring;
} Value;

typedef struct
{
    const char   *key;
    Value         v;
} Pair;

typedef struct 
{
    int     length;
    Pair   *items;
} Dict;

extern Value null;

Dict *dict_create(int len);
int dict_remove(Dict *dic, const char *key);
int dict_set(Dict *dic, const char *key, Value val);
int value_valid(Value v);
Value value_create(char t, ...);
Value dict_get(Dict *dic, const char *key);
void dict_clean(Dict *dic);

#endif