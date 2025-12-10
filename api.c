/* 负责API注册 */
#include "include/luas.h"
#include "include/dict.h"
#include "include/global.h"
#include "include/builtin.h"
/*======================================================*/
/*【API相关】*/
//【写完新 api 别忘了注册 API 库！！！】
// API:从全局状态表里获取值
void api_get(lua_State *L)
{
    const char *key = luaL_checkstring(L, -1);
    Value v = dict_get(global, key);
    lua_pop(L, 1);
    switch (v.type)
    {
    case 's':
        lua_pushstring(L, v.valuestring);
        break;
    case 'n':
        lua_pushnumber(L, v.valuenumber);
        break;
    case 'b':
        lua_pushboolean(L, v.valuebool);
        break;
    default:
        lua_pushstring(L, "[TYPE_ERR]");
        break;
    }
}

void api_print(lua_State *L)
{
    const char *text = luaL_checkstring(L, -1);
    //print(text);
    //应该交给handler
}

// API:打印


// 注册API库
static const luaL_Reg api[] = {
    { "print", print },
    { "get", get },
    { NULL, NULL }
};
// 回调函数
int luaopen_api(lua_State *L)
{
    luaL_newlib(L, api);
    return 1;
}