#ifndef PLUGIN_H
#define PLUGIN_H

#include "luas.h"
#include "api.h"
#include "global.h"

extern struct {
    lua_State **list;
    int         count;
} Plugins;

void Init_Plugins();
void Broadcast(char *event, char *arg);
void Destory_Plugins();

#endif