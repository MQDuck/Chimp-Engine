#include "runlua.h"
#include <lua.hpp>

void runLua(const std::string& filename, lua_State* const state)
{
    if(luaL_loadfile(state, filename.c_str()) != 0)
    {
        std::cout << lua_tostring(state, -1) << std::endl;
        lua_pop(state, 1);
        return;
    }
    
    if(lua_pcall(state, 0, LUA_MULTRET, 0) != 0)
    {
        std::cout << lua_tostring(state, -1) << std::endl;
        lua_pop(state, 1);
        return;
    }
}
