#ifndef LUAS_H
#define LUAS_H
#include "../lua/lua.h"
#include "../lua/lauxlib.h"
#include "../lua/lualib.h"
#define forever for(;;)

int lua_pcall2(lua_State *L, int n, int r, int f);

#endif