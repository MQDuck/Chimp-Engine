#include "ChimpLuaInterface.h"
#include "ChimpGame.h"
#include "ChimpObject.h"

namespace chimp
{

#ifdef __cplusplus
extern "C"
#endif
{
int getWorldLeft(lua_State* const state);
int getWorldRight(lua_State* const state);
int getWorldTop(lua_State* const state);
int getWorldBottom(lua_State* const state);
int getWindowWidth(lua_State* const state);
int getWindowHeight(lua_State* const state);

int getX(lua_State* const state);
int getY(lua_State* const state);
int getInitialX(lua_State* const state);
int getInitialY(lua_State* const state);
int getCenterX(lua_State* const state);
int getCenterY(lua_State* const state);
int getTilesX(lua_State* const state);
int getTilesY(lua_State* const state);
int getWidth(lua_State* const state);
int getHeight(lua_State* const state);
int getTexRectW(lua_State* const state);
int getTexRectH(lua_State* const state);
int collisionLeft(lua_State* const state);
int collisionRight(lua_State* const state);
int collisionTop(lua_State* const state);
int collisionBottom(lua_State* const state);
int getDamageLeft(lua_State* const state);
int getDamageRight(lua_State* const state);
int getDamageTop(lua_State* const state);
int getDamageBottom(lua_State* const state);
int getFriends(lua_State* const state);
//void addFriend(lua_State* const state);
int getEnemies(lua_State* const state);
//void addEnemy(lua_State* const state);
int isActive(lua_State* const state);
int onScreen(lua_State* const state);
int activate(lua_State* const state);
int deactivate(lua_State* const state);
//int touches(lua_State* const state);
//int touchesAtBottom(lua_State* const state);
int reset(lua_State* const state);
int getAccelerationY(lua_State* const state);
int setAccelerationY(lua_State* const state);
int getVelocityX(lua_State* const state);
int setVelocityX(lua_State* const state);
int getVelocityY(lua_State* const state);
int setVelocityY(lua_State* const state);
int runLeft(lua_State* const state);
int runRight(lua_State* const state);
int stopRunningRight(lua_State* const state);
int stopRunningLeft(lua_State* const state);
int stopRunning(lua_State* const state);
int getRunImpulse(lua_State* const state);
int setRunImpulse(lua_State* const state);
int getJumpImpulse(lua_State* const state);
int setJumpImpulse(lua_State* const state);
int getMultiJumpImpulse(lua_State* const state);
int setMultiJumpImpulse(lua_State* const state);
int getJumpAccel(lua_State* const state);
int setJumpAccel(lua_State* const state);
int getStopFactor(lua_State* const state);
int setStopFactor(lua_State* const state);
int getSprintFactor(lua_State* const state);
int setSprintFactor(lua_State* const state);
int getResistanceX(lua_State* const state);
int setResistanceX(lua_State* const state);
int getResistanceY(lua_State* const state);
int setResistanceY(lua_State* const state);
int getHealth(lua_State* const state);
int setHealth(lua_State* const state);
int getMaxHealth(lua_State* const state);
int setMaxHealth(lua_State* const state);
int getBoundLeft(lua_State* const state);
int setBoundLeft(lua_State* const state);
int getBoundRight(lua_State* const state);
int setBoundRight(lua_State* const state);
int getBoundTop(lua_State* const state);
int setBoundTop(lua_State* const state);
int getBoundBottom(lua_State* const state);
int setBoundBottom(lua_State* const state);
int getRespawn(lua_State* const state);
int setRespawn(lua_State* const state);
int getMaxJumps(lua_State* const state);
int setMaxJumps(lua_State* const state);
int hasPlatform(lua_State* const state);
} // extern "C"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

int getWorldLeft(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getGame()->getWorldLeft());
    return 1;
}

int getWorldRight(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getGame()->getWorldRight());
    return 1;
}

int getWorldTop(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getGame()->getWorldTop());
    return 1;
}

int getWorldBottom(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getGame()->getWorldBottom());
    return 1;
}

int getWindowWidth(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getGame()->getWindowWidth());
    return 1;
}

int getWindowHeight(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getGame()->getWindowHeight());
    return 1;
}

int getX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getX());
    return 1;
}

int getY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getY());
    return 1;
}

int getInitialX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getInitialX());
    return 1;
}

int getInitialY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getInitialY());
    return 1;
}

int getCenterX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getCenterX());
    return 1;
}

int getCenterY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getCenterY());
    return 1;
}

int getTilesX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getTilesX());
    return 1;
}

int getTilesY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getTilesY());
    return 1;
}

int getWidth(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getWidth());
    return 1;
}

int getHeight(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getHeight());
    return 1;
}

int getTexRectW(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getTexRectW());
    return 1;
}

int getTexRectH(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getTexRectH());
    return 1;
}

int collisionLeft(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->collisionLeft());
    return 1;
}

int collisionRight(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->collisionRight());
    return 1;
}

int collisionTop(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->collisionTop());
    return 1;
}

int collisionBottom(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->collisionBottom());
    return 1;
}

int getDamageLeft(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getCurrentObject()->getDamageLeft());
    return 1;
}

int getDamageRight(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getCurrentObject()->getDamageRight());
    return 1;
}

int getDamageTop(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getCurrentObject()->getDamageTop());
    return 1;
}

int getDamageBottom(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getCurrentObject()->getDamageBottom());
    return 1;
}

int getFriends(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getFriends());
    return 1;
}

int getEnemies(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getEnemies());
    return 1;
}

int isActive(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getCurrentObject()->isActive());
    return 1;
}

int onScreen(lua_State* const state)
{
    /*if(lua_gettop(state) == 2)
    {
        lua_pushboolean( state, ChimpGame::getCurrentObject()->onScreen() );
        return 1;
    }*/
    return 0;
}

int activate(lua_State* const state)
{
    ChimpGame::getCurrentObject()->activate();
    return 0;
}

int deactivate(lua_State* const state)
{
    ChimpGame::getCurrentObject()->deactivate();
    return 0;
}

int reset(lua_State* const state)
{
    ChimpGame::getCurrentObject()->reset();
    return 0;
}

int getAccelerationY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getAccelerationY());
    return 1;
}

int setAccelerationY(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setAccelerationY(lua_tonumber(state, 1));
    return 0;
}

int getVelocityX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getVelocityX());
    return 1;
}

int setVelocityX(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setVelocityX(lua_tonumber(state, 1));
    return 0;
}

int getVelocityY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getVelocityY());
    return 1;
}

int setVelocityY(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setVelocityY(lua_tonumber(state, 1));
    return 0;
}

int runLeft(lua_State* const state)
{
    ChimpGame::getCurrentObject()->runLeft();
    return 0;
}

int stopRunningLeft(lua_State* const state)
{
    ChimpGame::getCurrentObject()->stopRunningLeft();
    return 0;
}

int runRight(lua_State* const state)
{
    ChimpGame::getCurrentObject()->runRight();
    return 0;
}

int stopRunningRight(lua_State* const state)
{
    ChimpGame::getCurrentObject()->stopRunningRight();
    return 0;
}

int stopRunning(lua_State* const state)
{
    ChimpGame::getCurrentObject()->stopRunning();
    return 0;
}

int getRunImpulse(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getRunImpulse());
    return 1;
}

int setRunImpulse(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setRunImpulse(lua_tonumber(state, 1));
    return 0;
}

int getJumpImpulse(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getJumpImpulse());
    return 1;
}

int setJumpImpulse(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setJumpImpulse(lua_tonumber(state, 1));
    return 0;
}

int getMultiJumpImpulse(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getMultiJumpImpulse());
    return 1;
}

int setMultiJumpImpulse(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setMultiJumpImpulse(lua_tonumber(state, 1));
    return 0;
}

int getJumpAccel(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getJumpAccel());
    return 1;
}

int setJumpAccel(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setJumpAccel(lua_tonumber(state, 1));
    return 0;
}

int getStopFactor(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getStopFactor());
    return 1;
}

int setStopFactor(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setStopFactor(lua_tonumber(state, 1));
    return 0;
}

int getSprintFactor(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getSprintFactor());
    return 1;
}

int setSprintFactor(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setSprintFactor(lua_tonumber(state, 1));
    return 0;
}

int getResistanceX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getResistanceX());
    return 1;
}

int setResistanceX(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setResistanceX(lua_tonumber(state, 1));
    return 0;
}

int getResistanceY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getResistanceY());
    return 1;
}

int setResistanceY(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setResistanceY(lua_tonumber(state, 1));
    return 0;
}

int getHealth(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getHealth());
    return 1;
}

int setHealth(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setHealth(lua_tonumber(state, 1));
    return 0;
}

int getMaxHealth(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getMaxHealth());
    return 1;
}

int setMaxHealth(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setMaxHealth(lua_tonumber(state, 1));
    return 0;
}

int getBoundLeft(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getCurrentObject()->getBoundLeft());
    return 1;
}

int setBoundLeft(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setBoundLeft(lua_toboolean(state, 1));
    return 0;
}

int getBoundRight(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getCurrentObject()->getBoundRight());
    return 1;
}

int setBoundRight(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setBoundRight(lua_toboolean(state, 1));
    return 0;
}

int getBoundTop(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getCurrentObject()->getBoundTop());
    return 1;
}

int setBoundTop(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setBoundTop(lua_toboolean(state, 1));
    return 0;
}

int getBoundBottom(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getCurrentObject()->getBoundBottom());
    return 1;
}

int setBoundBottom(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setBoundBottom(lua_toboolean(state, 1));
    return 0;
}

int getRespawn(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getCurrentObject()->getRespawn());
    return 1;
}

int setRespawn(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setRespawn(lua_toboolean(state, 1));
    return 0;
}

int getMaxJumps(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getMaxJumps());
    return 1;
}

int setMaxJumps(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getCurrentObject()->setMaxJumps(lua_tonumber(state, 1));
    return 0;
}

int jump(lua_State* const state)
{
    ChimpGame::getCurrentObject()->jump();
    return 0;
}

int stopJumping(lua_State* const state)
{
    ChimpGame::getCurrentObject()->stopJumping();
    return 0;
}

int sprint(lua_State* const state)
{
    ChimpGame::getCurrentObject()->sprint();
    return 0;
}

int stopSprinting(lua_State* const state)
{
    ChimpGame::getCurrentObject()->stopSprinting();
    return 0;
}

int hasPlatform(lua_State* const state)
{
    if(lua_gettop(state) != 1)
        return 0;
    lua_pushboolean(state, ChimpGame::getCurrentObject()->hasPlatform());
    return 1;
}

#pragma GCC diagnostic pop

void setupLua(lua_State* const state)
{
    luaL_openlibs(state);
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
    lua_register(state, "getTexTectW", getTexRectW);
    lua_register(state, "getTexTectH", getTexRectH);
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
    lua_register(state, "jump", jump);
    lua_register(state, "stopJumping", stopJumping);
    lua_register(state, "sprint", sprint);
    lua_register(state, "stopSprinting", stopSprinting);
}

#undef gamePtr
#undef objPtr

} // namespace chimp
