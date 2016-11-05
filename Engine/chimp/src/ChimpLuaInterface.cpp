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
int jump(lua_State* const state);
int stopJumping(lua_State* const state);
int sprint(lua_State* const state);
int stopSprinting(lua_State* const state);
int hasPlatform(lua_State* const state);

int playerGetX(lua_State* const state);
int playerGetY(lua_State* const state);
int playerGetInitialX(lua_State* const state);
int playerGetInitialY(lua_State* const state);
int playerGetCenterX(lua_State* const state);
int playerGetCenterY(lua_State* const state);
int playerGetTilesX(lua_State* const state);
int playerGetTilesY(lua_State* const state);
int playerGetWidth(lua_State* const state);
int playerGetHeight(lua_State* const state);
int playerGetTexRectW(lua_State* const state);
int playerGetTexRectH(lua_State* const state);
int playerCollisionLeft(lua_State* const state);
int playerCollisionRight(lua_State* const state);
int playerCollisionTop(lua_State* const state);
int playerCollisionBottom(lua_State* const state);
int playerGetDamageLeft(lua_State* const state);
int playerGetDamageRight(lua_State* const state);
int playerGetDamageTop(lua_State* const state);
int playerGetDamageBottom(lua_State* const state);
int playerGetFriends(lua_State* const state);
int playerGetEnemies(lua_State* const state);
int playerIsActive(lua_State* const state);
int playerOnScreen(lua_State* const state);
int playerActivate(lua_State* const state);
int playerDeactivate(lua_State* const state);
int playerReset(lua_State* const state);
int playerGetAccelerationY(lua_State* const state);
int playerSetAccelerationY(lua_State* const state);
int playerGetVelocityX(lua_State* const state);
int playerSetVelocityX(lua_State* const state);
int playerGetVelocityY(lua_State* const state);
int playerSetVelocityY(lua_State* const state);
int playerRunLeft(lua_State* const state);
int playerRunRight(lua_State* const state);
int playerStopRunningRight(lua_State* const state);
int playerStopRunningLeft(lua_State* const state);
int playerStopRunning(lua_State* const state);
int playerGetRunImpulse(lua_State* const state);
int playerSetRunImpulse(lua_State* const state);
int playerGetJumpImpulse(lua_State* const state);
int playerSetJumpImpulse(lua_State* const state);
int playerGetMultiJumpImpulse(lua_State* const state);
int playerSetMultiJumpImpulse(lua_State* const state);
int playerGetJumpAccel(lua_State* const state);
int playerSetJumpAccel(lua_State* const state);
int playerGetStopFactor(lua_State* const state);
int playerSetStopFactor(lua_State* const state);
int playerGetSprintFactor(lua_State* const state);
int playerSetSprintFactor(lua_State* const state);
int playerGetResistanceX(lua_State* const state);
int playerSetResistanceX(lua_State* const state);
int playerGetResistanceY(lua_State* const state);
int playerSetResistanceY(lua_State* const state);
int playerGetHealth(lua_State* const state);
int playerSetHealth(lua_State* const state);
int playerGetMaxHealth(lua_State* const state);
int playerSetMaxHealth(lua_State* const state);
int playerGetBoundLeft(lua_State* const state);
int playerSetBoundLeft(lua_State* const state);
int playerGetBoundRight(lua_State* const state);
int playerSetBoundRight(lua_State* const state);
int playerGetBoundTop(lua_State* const state);
int playerSetBoundTop(lua_State* const state);
int playerGetBoundBottom(lua_State* const state);
int playerSetBoundBottom(lua_State* const state);
int playerGetRespawn(lua_State* const state);
int playerSetRespawn(lua_State* const state);
int playerGetMaxJumps(lua_State* const state);
int playerSetMaxJumps(lua_State* const state);
int playerJump(lua_State* const state);
int playerStopJumping(lua_State* const state);
int playerSprint(lua_State* const state);
int playerStopSprinting(lua_State* const state);
int playerHasPlatform(lua_State* const state);
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
    lua_pushnumber(state, ChimpGame::getGame()->getViewWidth());
    return 1;
}

int getWindowHeight(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getGame()->getViewHeight());
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
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getCollisionLeft());
    return 1;
}

int collisionRight(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getCollisionRight());
    return 1;
}

int collisionTop(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getCollisionTop());
    return 1;
}

int collisionBottom(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getCurrentObject()->getCollisionBottom());
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
    ChimpGame::getCurrentObject()->jump(*ChimpGame::getGame());
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


int playerGetX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getX());
    return 1;
}

int playerGetY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getY());
    return 1;
}

int playerGetInitialX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getInitialX());
    return 1;
}

int playerGetInitialY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getInitialY());
    return 1;
}

int playerGetCenterX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getCenterX());
    return 1;
}

int playerGetCenterY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getCenterY());
    return 1;
}

int playerGetTilesX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getTilesX());
    return 1;
}

int playerGetTilesY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getTilesY());
    return 1;
}

int playerGetWidth(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getWidth());
    return 1;
}

int playerGetHeight(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getHeight());
    return 1;
}

int playerGetTexRectW(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getTexRectW());
    return 1;
}

int playerGetTexRectH(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getTexRectH());
    return 1;
}

int playerCollisionLeft(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getCollisionLeft());
    return 1;
}

int playerCollisionRight(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getCollisionRight());
    return 1;
}

int playerCollisionTop(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getCollisionTop());
    return 1;
}

int playerCollisionBottom(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getCollisionBottom());
    return 1;
}

int playerGetDamageLeft(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getPlayer()->getDamageLeft());
    return 1;
}

int playerGetDamageRight(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getPlayer()->getDamageRight());
    return 1;
}

int playerGetDamageTop(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getPlayer()->getDamageTop());
    return 1;
}

int playerGetDamageBottom(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getPlayer()->getDamageBottom());
    return 1;
}

int playerGetFriends(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getFriends());
    return 1;
}

int playerGetEnemies(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getEnemies());
    return 1;
}

int playerIsActive(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getPlayer()->isActive());
    return 1;
}

int playerOnScreen(lua_State* const state)
{
    /*if(lua_gettop(state) == 2)
    {
        lua_pushboolean( state, ChimpGame::getPlayer()->onScreen() );
        return 1;
    }*/
    return 0;
}

int playerActivate(lua_State* const state)
{
    ChimpGame::getPlayer()->activate();
    return 0;
}

int playerDeactivate(lua_State* const state)
{
    ChimpGame::getPlayer()->deactivate();
    return 0;
}

int playerReset(lua_State* const state)
{
    ChimpGame::getPlayer()->reset();
    return 0;
}

int playerGetAccelerationY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getAccelerationY());
    return 1;
}

int playerSetAccelerationY(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setAccelerationY(lua_tonumber(state, 1));
    return 0;
}

int playerGetVelocityX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getVelocityX());
    return 1;
}

int playerSetVelocityX(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setVelocityX(lua_tonumber(state, 1));
    return 0;
}

int playerGetVelocityY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getVelocityY());
    return 1;
}

int playerSetVelocityY(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setVelocityY(lua_tonumber(state, 1));
    return 0;
}

int playerRunLeft(lua_State* const state)
{
    ChimpGame::getPlayer()->runLeft();
    return 0;
}

int playerStopRunningLeft(lua_State* const state)
{
    ChimpGame::getPlayer()->stopRunningLeft();
    return 0;
}

int playerRunRight(lua_State* const state)
{
    ChimpGame::getPlayer()->runRight();
    return 0;
}

int playerStopRunningRight(lua_State* const state)
{
    ChimpGame::getPlayer()->stopRunningRight();
    return 0;
}

int playerStopRunning(lua_State* const state)
{
    ChimpGame::getPlayer()->stopRunning();
    return 0;
}

int playerGetRunImpulse(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getRunImpulse());
    return 1;
}

int playerSetRunImpulse(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setRunImpulse(lua_tonumber(state, 1));
    return 0;
}

int playerGetJumpImpulse(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getJumpImpulse());
    return 1;
}

int playerSetJumpImpulse(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setJumpImpulse(lua_tonumber(state, 1));
    return 0;
}

int playerGetMultiJumpImpulse(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getMultiJumpImpulse());
    return 1;
}

int playerSetMultiJumpImpulse(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setMultiJumpImpulse(lua_tonumber(state, 1));
    return 0;
}

int playerGetJumpAccel(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getJumpAccel());
    return 1;
}

int playerSetJumpAccel(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setJumpAccel(lua_tonumber(state, 1));
    return 0;
}

int playerGetStopFactor(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getStopFactor());
    return 1;
}

int playerSetStopFactor(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setStopFactor(lua_tonumber(state, 1));
    return 0;
}

int playerGetSprintFactor(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getSprintFactor());
    return 1;
}

int playerSetSprintFactor(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setSprintFactor(lua_tonumber(state, 1));
    return 0;
}

int playerGetResistanceX(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getResistanceX());
    return 1;
}

int playerSetResistanceX(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setResistanceX(lua_tonumber(state, 1));
    return 0;
}

int playerGetResistanceY(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getResistanceY());
    return 1;
}

int playerSetResistanceY(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setResistanceY(lua_tonumber(state, 1));
    return 0;
}

int playerGetHealth(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getHealth());
    return 1;
}

int playerSetHealth(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setHealth(lua_tonumber(state, 1));
    return 0;
}

int playerGetMaxHealth(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getMaxHealth());
    return 1;
}

int playerSetMaxHealth(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setMaxHealth(lua_tonumber(state, 1));
    return 0;
}

int playerGetBoundLeft(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getPlayer()->getBoundLeft());
    return 1;
}

int playerSetBoundLeft(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setBoundLeft(lua_toboolean(state, 1));
    return 0;
}

int playerGetBoundRight(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getPlayer()->getBoundRight());
    return 1;
}

int playerSetBoundRight(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setBoundRight(lua_toboolean(state, 1));
    return 0;
}

int playerGetBoundTop(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getPlayer()->getBoundTop());
    return 1;
}

int playerSetBoundTop(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setBoundTop(lua_toboolean(state, 1));
    return 0;
}

int playerGetBoundBottom(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getPlayer()->getBoundBottom());
    return 1;
}

int playerSetBoundBottom(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setBoundBottom(lua_toboolean(state, 1));
    return 0;
}

int playerGetRespawn(lua_State* const state)
{
    lua_pushboolean(state, ChimpGame::getPlayer()->getRespawn());
    return 1;
}

int playerSetRespawn(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setRespawn(lua_toboolean(state, 1));
    return 0;
}

int playerGetMaxJumps(lua_State* const state)
{
    lua_pushnumber(state, ChimpGame::getPlayer()->getMaxJumps());
    return 1;
}

int playerSetMaxJumps(lua_State* const state)
{
    if(lua_gettop(state) == 1)
        ChimpGame::getPlayer()->setMaxJumps(lua_tonumber(state, 1));
    return 0;
}

int playerJump(lua_State* const state)
{
    ChimpGame::getPlayer()->jump(*ChimpGame::getGame());
    return 0;
}

int playerStopJumping(lua_State* const state)
{
    ChimpGame::getPlayer()->stopJumping();
    return 0;
}

int playerSprint(lua_State* const state)
{
    ChimpGame::getPlayer()->sprint();
    return 0;
}

int playerStopSprinting(lua_State* const state)
{
    ChimpGame::getPlayer()->stopSprinting();
    return 0;
}

int playerHasPlatform(lua_State* const state)
{
    if(lua_gettop(state) != 1)
        return 0;
    lua_pushboolean(state, ChimpGame::getPlayer()->hasPlatform());
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
    lua_register(state, "runLeft", runLeft);
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
    lua_register(state, "playerGetCenterX", playerGetCenterX);
    lua_register(state, "playerGetWidth", playerGetWidth);
}

#undef gamePtr
#undef objPtr

} // namespace chimp
