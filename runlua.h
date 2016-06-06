#ifndef RUNLUA_H
#define RUNLUA_H

#include <lua.hpp>
#include "chimp/ChimpGame.h"
#include "chimp/ChimpObject.h"

void printLuaError(lua_State* state);
void executeLua(const char* filename, lua_State* luast, chimp::ChimpGame* game, chimp::ChimpObject* obj);


#endif // RUNLUA_H
