/* 工具文件 字典 */
#include "include/include.h"
#define PRIVATE  
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

Value null = { 'x' };

Dict *dict_create(int len)
{
    Pair *i = calloc(len, sizeof(Pair));
    Dict *dic = calloc(1, sizeof(Dict));
    dic->length = 0;
    dic->items = i;
    return dic;
}

Pair *__pair_search(Dict *dic, const char* key)
{
    if(!dic || !key) return NULL;
    for(int i=0; i<dic->length; i++)
    {
        Pair *p = &(dic->items[i]);
        if(!p->key) continue;;
        if(strcmp(p->key, key) == 0)
            return p;
    }
    return NULL;
}

int value_valid(Value v)
{
    if(v.type == 'x') return 0;
    else return 1;
}

Value value_create(char t, ...)
{
    Value v;
    v.type = t;
    va_list ap;
    va_start(ap, t);
    switch (t)
    {
    case 's':
        v.valuestring = va_arg(ap, char *);
        break;
    case 'n':
        v.valuenumber = va_arg(ap, double);
        break;
    case 'b':
        v.valuebool = va_arg(ap, int);
        break;
    default:
        v = null;
        break;
    }
    return v;
}

int dict_remove(Dict *dic, const char *key)
{
    for(int i=0; i<dic->length; i++)
    {
        Pair *p = &(dic->items)[i];
        if(!p->key) return 0;
        if(strcmp(p->key, key) == 0)
        {
            dic->length--;
            for(int j=i; j<dic->length; j++)
            {
                (dic->items)[j] = (dic->items)[j+1];
            }
            memset(&dic->items[dic->length], 0, sizeof(Pair));
            return 1;
        }
    }
    return 0;
}

int dict_set(Dict *dic, const char *key, Value val)
{
    Pair *p = __pair_search(dic, key);
    if(p && p->key)
    {
        p->v = val;
        return 1;
    }
    else
    {
        Pair *tmp = realloc(dic->items, (dic->length+1) * sizeof(Pair));
        if(!tmp) return 0;

        dic->items = tmp;
        dic->items[dic->length].key = key;
        dic->items[dic->length].v = val;
        dic->length++;
        return 1;
    }
}

Value dict_get(Dict *dic, const char *key)
{
    Pair *p = __pair_search(dic, key);
    if(!p || !p->key) return null;
    return p->v;
}

void dict_clean(Dict *dic)
{
    if(!dic) return;
    for(int i=0; i<dic->length; i++)
    {
        if(dic->items[i].v.type == 's')
        {
            free(dic->items[i].v.valuestring);
            dic->items[i].v.valuestring = NULL;
        }
    }
    free(dic->items);
    free(dic);
}