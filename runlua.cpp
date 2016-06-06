#include "runlua.h"
#include <lua.hpp>

void printLuaError(lua_State* state) {
  // The error message is on top of the stack.
  // Fetch it, print it and then pop it off the stack.
  const char* message = lua_tostring(state, -1);
  puts(message);
  lua_pop(state, 1);
}

void executeLua(const char* const filename, lua_State* const luast, chimp::ChimpGame* const game,
                chimp::ChimpObject* const obj)
{
    // Make standard libraries available in the Lua object
    luaL_openlibs(luast);
    
    int result;
    
    // Load the program; this supports both source code and bytecode files.
    result = luaL_loadfile(luast, filename);
    
    if(result)
    {
        printLuaError(luast);
        return;
    }
    
    // Finally, execute the program by calling into it.
    // Change the arguments if you're not running vanilla Lua code.
    
    lua_newtable(luast);
    
    lua_pushnumber(luast, 1);
    lua_pushlightuserdata(luast, game);
    lua_rawset(luast, -3);
    
    lua_pushnumber(luast, 2);
    lua_pushlightuserdata(luast, obj);
    lua_rawset(luast, -3);
    
    lua_pushliteral(luast, "n");
    lua_pushnumber(luast, 2);
    lua_rawset(luast, -3);
    
    lua_setglobal(luast, "arg");
    
    result = lua_pcall(luast, 0, LUA_MULTRET, 0);

    if(result)
    {
        printLuaError(luast);
        return;
    }
}
