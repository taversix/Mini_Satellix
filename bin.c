/* 工具文件 垃圾回收 */
#include "include/include.h"

typedef struct {
    void  *ptr;
    void (*method)(void *)
} Thing;

typedef struct {
    int     count;
    Thing  *things;
} Bin;

Bin *bin_create()
{
    Bin *b = calloc(1, sizeof(Bin));
    if(!b) return NULL;
    b->count = 0;
    b->things = NULL;
    return b;
}

void bin_drop(Bin *b, void *p)
{
    Thing item = { p, NULL };
    
    Thing *tmp = realloc(b->things, (b->count+1) * sizeof(Thing));
    if(!tmp) return;
    // realloc 失败直接返回不管，没办法，也不能当场释放

    b->things = tmp;
    b->things[b->count] = item;
    b->count++;
}

void bin_drops(Bin *b, void *p, void (*meth)(void *))
{
    Thing item = { p, meth };
    
    Thing *tmp = realloc(b->things, b->count+1);
    if(!tmp) return;

    b->things = tmp;
    b->things[b->count] = item;
    b->count++;
}

void bin_empty(Bin *b)
{
    if(!b) return;
    for(int i=0; i<b->count; i++)
    {
        if(!b->things[i].ptr) continue;
        if(!b->things[i].method)
            free(b->things[i].ptr);
        else
            b->things[i].method(b->things[i].ptr);
    }
    free(b->things);
    
    b->things = NULL;
    b->count = 0;
}