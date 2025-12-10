/* 负责简化引入头文件、封装函数 */
#include "../lua/lua.h"
#include "../lua/lauxlib.h"
#include "../lua/lualib.h"

int lua_pcall2(lua_State *L, int n, int r, int f)
{
    int err = lua_pcall(L, n, r, f);
    if(err)
    {
        printf("[Lua ERR]%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        return 0;
    }
    return 1;
}