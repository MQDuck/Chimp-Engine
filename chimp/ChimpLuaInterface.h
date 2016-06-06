#ifndef CHIMPLUAINTERFACE_H
#define CHIMPLUAINTERFACE_H

#include <lua.hpp>
#include "ChimpGame.h"
#include "ChimpObject.h"

namespace chimp
{
namespace lua
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
int getTexTectW(lua_State* const state);
int getTexTectH(lua_State* const state);
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
int touches(lua_State* const state);
int touchesAtBottom(lua_State* const state);
int reset(lua_State* const state);
//xxjumper methodsxx
int getAccelerationY(lua_State* const state);
int setAccelerationY(lua_State* const state);
int getVelocityX(lua_State* const state);
int setVelocityX(lua_State* const state);
int getVelocityY(lua_State* const state);
int setVelocityY(lua_State* const state);
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

void expose(lua_State* const state);

} // namespace lua
} // namespace chimp


#endif // CHIMPLUAINTERFACE_H










