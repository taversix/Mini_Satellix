/* 负责插件初始化、时间广播 */
#include "include/luas.h"
#include "include/api.h"
#include "include/global.h"
/*======================================================*/
/*【插件相关】*/
// 插件列表结构体
struct {
    lua_State **list;
    int         count;
} Plugins;

// 初始化插件
void Init_Plugins()
{
    lua_State *plugin_table = luaL_newstate();
    // 错误
    if(!plugin_table) return;
    luaL_openlibs(plugin_table);
    luaL_dofile(plugin_table, CONFIG_PLUGINS);

    lua_getglobal(plugin_table, "plugins");
    Plugins.count = (int)lua_rawlen(plugin_table, -1);
    Plugins.list = calloc(Plugins.count, sizeof(lua_State*));

    for(int i=0; i<Plugins.count; i++)
    {
        lua_State *plugin = luaL_newstate();
        luaL_openlibs(plugin);
        lua_rawgeti(plugin_table, -1, i+1);
        const char *name = (char *)luaL_checkstring(plugin_table, -1);
        char filename[64];
        snprintf(filename, sizeof(filename), "%s%s", PLUGINS_DIR, name);

        luaL_requiref(plugin, "api", luaopen_api, 1);
        lua_pop(plugin, 1);
        
        luaL_dofile(plugin, filename);
        Plugins.list[i] = plugin;
        lua_pop(plugin_table, 1);
    }

    lua_close(plugin_table);
}

void Broadcast(char *event, char *arg)
{
    if(Plugins.count < 1) return;
    for(int i=0; i<Plugins.count; i++)
    {
        lua_State *plugin = Plugins.list[i];
        lua_getglobal(plugin, "On");
        lua_pushstring(plugin, event);
        lua_pushstring(plugin, arg);
        lua_pcall2(plugin, 2, 0, 0);
    }
}

void Destory_Plugins()
{
    for(int i=0; i<Plugins.count; i++)
    {
        lua_State *plugin = Plugins.list[i];
        lua_close(plugin);
    }
}