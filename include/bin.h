#ifndef BIN_H
#define BIN_H
#include "include/include.h"

typedef struct {
    void  *ptr;
    void (*method)(void *)
} thing;

typedef struct {
    int     count;
    thing  *things;
} Bin;

Bin *bin_create();
void bin_drop(Bin *b, void *p);
void bin_drops(Bin *b, void *p, void (*meth)(void *));
void bin_empty(Bin *b);

#endif