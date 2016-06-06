#include "ChimpLuaInterface.h"

namespace chimp
{
namespace lua
{

#define gamePtr(param) static_cast<ChimpGame*>(lua_touserdata(state, param))
#define objPtr(param) static_cast<ChimpObject*>(lua_touserdata(state, param))

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

int getWorldLeft(lua_State* const state)
{
    if(lua_gettop(state) == 1)
    {
        lua_pushnumber(state, gamePtr(1)->getWorldLeft());
        return 1;
    }
    return 0;
}

int getWorldRight(lua_State* const state) { return 0; }
int getWorldTop(lua_State* const state) { return 0; }
int getWorldBottom(lua_State* const state) { return 0; }
int getWindowWidth(lua_State* const state) { return 0; }
int getWindowHeight(lua_State* const state) { return 0; }
int getX(lua_State* const state) { return 0; }
int getY(lua_State* const state) { return 0; }
int getInitialX(lua_State* const state) { return 0; }
int getInitialY(lua_State* const state) { return 0; }
int getCenterX(lua_State* const state) { return 0; }
int getCenterY(lua_State* const state) { return 0; }
int getTilesX(lua_State* const state) { return 0; }
int getTilesY(lua_State* const state) { return 0; }
int getWidth(lua_State* const state) { return 0; }
int getHeight(lua_State* const state) { return 0; }
int getTexTectW(lua_State* const state) { return 0; }
int getTexTectH(lua_State* const state) { return 0; }
int collisionLeft(lua_State* const state) { return 0; }
int collisionRight(lua_State* const state) { return 0; }
int collisionTop(lua_State* const state) { return 0; }
int collisionBottom(lua_State* const state) { return 0; }
int getDamageLeft(lua_State* const state) { return 0; }
int getDamageRight(lua_State* const state) { return 0; }
int getDamageTop(lua_State* const state) { return 0; }
int getDamageBottom(lua_State* const state) { return 0; }
int getFriends(lua_State* const state) { return 0; }
int getEnemies(lua_State* const state) { return 0; }
int isActive(lua_State* const state) { return 0; }
int onScreen(lua_State* const state) { return 0; }
int activate(lua_State* const state) { return 0; }
int deactivate(lua_State* const state) { return 0; }
int touches(lua_State* const state) { return 0; }
int touchesAtBottom(lua_State* const state) { return 0; }
int reset(lua_State* const state) { return 0; }
int getAccelerationY(lua_State* const state) { return 0; }
int setAccelerationY(lua_State* const state) { return 0; }
int getVelocityX(lua_State* const state) { return 0; }
int setVelocityX(lua_State* const state) { return 0; }
int getVelocityY(lua_State* const state) { return 0; }
int setVelocityY(lua_State* const state) { return 0; }
int runRight(lua_State* const state) { return 0; }
int stopRunningRight(lua_State* const state) { return 0; }
int stopRunningLeft(lua_State* const state) { return 0; }
int stopRunning(lua_State* const state) { return 0; }
int getRunImpulse(lua_State* const state) { return 0; }
int setRunImpulse(lua_State* const state) { return 0; }
int getJumpImpulse(lua_State* const state) { return 0; }
int setJumpImpulse(lua_State* const state) { return 0; }
int getMultiJumpImpulse(lua_State* const state) { return 0; }
int setMultiJumpImpulse(lua_State* const state) { return 0; }
int getJumpAccel(lua_State* const state) { return 0; }
int setJumpAccel(lua_State* const state) { return 0; }
int getStopFactor(lua_State* const state) { return 0; }
int setStopFactor(lua_State* const state) { return 0; }
int getSprintFactor(lua_State* const state) { return 0; }
int setSprintFactor(lua_State* const state) { return 0; }
int getResistanceX(lua_State* const state) { return 0; }
int setResistanceX(lua_State* const state) { return 0; }
int getResistanceY(lua_State* const state) { return 0; }
int setResistanceY(lua_State* const state) { return 0; }
int getHealth(lua_State* const state) { return 0; }
int setHealth(lua_State* const state) { return 0; }
int getMaxHealth(lua_State* const state) { return 0; }
int setMaxHealth(lua_State* const state) { return 0; }
int getBoundLeft(lua_State* const state) { return 0; }
int setBoundLeft(lua_State* const state) { return 0; }
int getBoundRight(lua_State* const state) { return 0; }
int setBoundRight(lua_State* const state) { return 0; }
int getBoundTop(lua_State* const state) { return 0; }
int setBoundTop(lua_State* const state) { return 0; }
int getBoundBottom(lua_State* const state) { return 0; }
int setBoundBottom(lua_State* const state) { return 0; }
int getRespawn(lua_State* const state) { return 0; }
int setRespawn(lua_State* const state) { return 0; }
int getMaxJumps(lua_State* const state) { return 0; }
int setMaxJumps(lua_State* const state) { return 0; }

int hasPlatform(lua_State* const state)
{
    if(lua_gettop(state) != 1)
        return 0;
    ChimpObject* const obj = (ChimpObject*)lua_touserdata(state, 1);
    lua_pushboolean(state, obj->hasPlatform());
    return 1;
}

void expose(lua_State* const state)
{
    lua_register(state, "getWorldLeft", getWorldLeft);
    lua_register(state, "getWorldRight", getWorldRight);
    lua_register(state, "getWorldTop", getWorldTop);
    lua_register(state, "getWorldBottom", getWorldBottom);
    lua_register(state, "getWindowWidth", getWindowWidth);
    lua_register(state, "getWindowHeight", getWindowHeight);
    lua_register(state, "getX", getX);
    lua_register(state, "getY", getY);
    lua_register(state, "getInitialX", getInitialX);
    lua_register(state, "getInitialY", getInitialY);
    lua_register(state, "getCenterX", getCenterX);
    lua_register(state, "getCenterY", getCenterY);
    lua_register(state, "getTilesX", getTilesX);
    lua_register(state, "getTilesY", getTilesY);
    lua_register(state, "getWidth", getWidth);
    lua_register(state, "getHeight", getHeight);
    lua_register(state, "getTexTectW", getTexTectW);
    lua_register(state, "getTexTectH", getTexTectH);
    lua_register(state, "collisionLeft", collisionLeft);
    lua_register(state, "collisionRight", collisionRight);
    lua_register(state, "collisionTop", collisionTop);
    lua_register(state, "collisionBottom", collisionBottom);
    lua_register(state, "getDamageLeft", getDamageLeft);
    lua_register(state, "getDamageRight", getDamageRight);
    lua_register(state, "getDamageTop", getDamageTop);
    lua_register(state, "getDamageBottom", getDamageBottom);
    lua_register(state, "getFriends", getFriends);
    lua_register(state, "getEnemies", getEnemies);
    lua_register(state, "isActive", isActive);
    lua_register(state, "onScreen", onScreen);
    lua_register(state, "activate", activate);
    lua_register(state, "deactivate", deactivate);
    lua_register(state, "touches", touches);
    lua_register(state, "touchesAtBottom", touchesAtBottom);
    lua_register(state, "reset", reset);
    lua_register(state, "getAccelerationY", getAccelerationY);
    lua_register(state, "setAccelerationY", setAccelerationY);
    lua_register(state, "getVelocityX", getVelocityX);
    lua_register(state, "setVelocityX", setVelocityX);
    lua_register(state, "getVelocityY", getVelocityY);
    lua_register(state, "setVelocityY", setVelocityY);
    lua_register(state, "runRight", runRight);
    lua_register(state, "stopRunningRight", stopRunningRight);
    lua_register(state, "stopRunningLeft", stopRunningLeft);
    lua_register(state, "stopRunning", stopRunning);
    lua_register(state, "getRunImpulse", getRunImpulse);
    lua_register(state, "setRunImpulse", setRunImpulse);
    lua_register(state, "getJumpImpulse", getJumpImpulse);
    lua_register(state, "setJumpImpulse", setJumpImpulse);
    lua_register(state, "getMultiJumpImpulse", getMultiJumpImpulse);
    lua_register(state, "setMultiJumpImpulse", setMultiJumpImpulse);
    lua_register(state, "getJumpAccel", getJumpAccel);
    lua_register(state, "setJumpAccel", setJumpAccel);
    lua_register(state, "getStopFactor", getStopFactor);
    lua_register(state, "setStopFactor", setStopFactor);
    lua_register(state, "getSprintFactor", getSprintFactor);
    lua_register(state, "setSprintFactor", setSprintFactor);
    lua_register(state, "getResistanceX", getResistanceX);
    lua_register(state, "setResistanceX", setResistanceX);
    lua_register(state, "getResistanceY", getResistanceY);
    lua_register(state, "setResistanceY", setResistanceY);
    lua_register(state, "getHealth", getHealth);
    lua_register(state, "setHealth", setHealth);
    lua_register(state, "getMaxHealth", getMaxHealth);
    lua_register(state, "setMaxHealth", setMaxHealth);
    lua_register(state, "getBoundLeft", getBoundLeft);
    lua_register(state, "setBoundLeft", setBoundLeft);
    lua_register(state, "getBoundRight", getBoundRight);
    lua_register(state, "setBoundRight", setBoundRight);
    lua_register(state, "setBoundRight", setBoundRight);
    lua_register(state, "setBoundTop", setBoundTop);
    lua_register(state, "getBoundBottom", getBoundBottom);
    lua_register(state, "setBoundBottom", setBoundBottom);
    lua_register(state, "getRespawn", getRespawn);
    lua_register(state, "setRespawn", setRespawn);
    lua_register(state, "getMaxJumps", getMaxJumps);
    lua_register(state, "setMaxJumps", setMaxJumps);
}

#pragma GCC diagnostic pop

#undef gamePtr
#undef objPtr

} // namespace lua
} // namespace chimp
