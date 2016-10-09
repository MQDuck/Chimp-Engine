/*
    Copyright 2016 Jeffrey Thomas Piercy
  
    This file is part of Chimp Out!.

    Chimp Out! is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Chimp Out! is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Chimp Out!.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "chimp/ChimpMobile.h"
#include "chimp/ChimpGame.h"
#include "sys/stat.h"

#include <iostream>

namespace chimp
{

/**
 * @brief ChimpMobile::ChimpMobile()
 * @param til Mobile's ChimpTile
 * @param rend SDL renderer that should be drawn to
 * @param pX Object's initial x-position
 * @param pY Object's initial y-position
 * @param tilesX How many times the ChimpTile should be tiled to the right.
 * @param tilesY How many times the ChimpTile should be tiled down.
 * @param frnds Factions to which the Object belongs.
 * @param enms Factions which the Object can deal damage to.
 */
ChimpMobile::ChimpMobile(SDL_Renderer* const rend, const ChimpTile& til, const int pX, const int pY, const int tilesX,
                         const int tilesY, Faction frnds, Faction enms)
    : ChimpObject(rend, til, pX, pY, tilesX, tilesY, frnds, enms)
{
    coordInitial.x = coord.x;
    coordInitial.y = coord.y;
    velocityX = 0;
    //velocityY = accelerationY;
    velocityY = 0;
    runningRight = false;
    runningLeft = false;
    sprinting = false;
    boundBox.l = false;
    boundBox.r = false;
    boundBox.t = false;
    boundBox.b = false;
    platform = nullptr;
    respawn = true;
    jumping = false;
    numJumps = 0;
    
    setMaxJumps(MAX_JUMPS);
    setRunImpulse(RUN_IMPULSE);
    setRunAccel(RUN_ACCEL);
    setAccelerationY(GRAVITY);
    setJumpImpulse(JUMP_IMPULSE);
    setMultiJumpImpulse(MULTI_JUMP_IMPULSE);
    setJumpAccel(JUMP_ACCEL);
    setStopFactor(STOP_FACTOR);
    setSprintFactor(SPRINT_FACTOR);
    setResistanceX(RESISTANCE_X);
    setResistanceY(RESISTANCE_Y);
}

/**
 * @brief ChimpMobile::initialize()
 * 
 * Should be run once for each object after it's added to the game. For Objects added at the start of the game, this
 * should be called only after all Objects are added.
 * 
 * [...]
 */
void ChimpMobile::initialize(const ChimpGame& game)
{
    coord = coordInitial;
    ChimpObject::initialize(game);
    runScript(scriptInit, game.getLuaState());
}

/**
 * @brief ChimpMobile::runRight()
 * 
 * Called when a Mobile begins moving right.
 */
void ChimpMobile::runRight()
{
    if( approxZeroF(velocityX) )
        velocityX += run_impulse - velocityX * resistance_x;
    runningRight = true;
    runningLeft = false;
    flip = SDL_FLIP_NONE;
}

/**
 * @brief ChimpMobile::runLeft()
 * 
 * Called when a Mobile begins moving right.
 */
void ChimpMobile::runLeft()
{
    if( approxZeroF(velocityX) )
        velocityX -= run_impulse - velocityX * resistance_x;
    runningLeft = true;
    runningRight = false;
    flip = SDL_FLIP_HORIZONTAL;
}

void ChimpMobile::stopRunningRight() { runningRight = false; }
void ChimpMobile::stopRunningLeft() { runningLeft = false; }
void ChimpMobile::stopRunning()
{
    runningRight = false;
    runningLeft = false;
}

/**
 * @brief ChimpMobile::jump()
 * 
 * Called when a Mobile tries to jump. Mobiles can double jump. If the Mobile is not standing on a platform and has
 * already double jumped, this method does nothing.
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void ChimpMobile::jump(ChimpGame& game)
{
    if(numJumps < maxJumps)
    {
        if(numJumps == 0)
            velocityY = jump_impulse;
        else
            velocityY = multi_jump_impulse;
        accelerationY = jump_accel + GRAVITY;
        platform = nullptr;
        jumping = true;
        ++numJumps;
    }
}
#pragma GCC diagnostic pop

/**
 * @brief ChimpMobile::stopJumping
 * 
 * Called automatically when a jumpbing Mobile's velocity reaches zero. Designed to also be called when the player lets
 * go of the jump button while their Character is jumping.
 */
void ChimpMobile::stopJumping()
{
    if(!platform) //necessary?
        accelerationY = GRAVITY;
    jumping = false;
}

/**
 * @brief ChimpMobile::sprint()
 * 
 * Designed to be called when the player holds the run button.
 */
void ChimpMobile::sprint() { sprinting = true; }

/**
 * @brief ChimpMobile::stopSprinting()
 * 
 * Designed to be called when the player releases the run button.
 */
void ChimpMobile::stopSprinting() { sprinting = false; }

/**
 * @brief ChimpMobile::reset()
 * 
 * Resets Mobile to original position.
 */
void ChimpMobile::reset()
{
    coord = coordInitial;
    platform = nullptr;
    velocityX = 0;
    velocityY = 0;
    ChimpObject::deactivate();
}

/**
 * @brief ChimpMobile::update()
 * 
 * Calls ChimpObject::update(). Updates Mobile's position and platform.
 * 
 * [...]
 */
void ChimpMobile::update(const ObjectVector& objects, ChimpGame& game, const Uint32 time)
{
    ChimpObject::update(objects, game, time);
    
    if(!active)
        return;
    
    runScript(scriptBehavior, game.getLuaState());
    
    if(platform)
    {
        coord.x += platform->getVelocityX() * time;
        coord.y = platform->collisionTop() - height + tile.collisionBox.b;
    }
    if( !jumping && (!platform || !touchesAtBottom(*platform)) )
    {
        if(platform)
            numJumps = 1;
        platform = nullptr;
        for(const ObjectPointer& obj : objects)
            if(   obj->isActive()
                  && platform != &*obj //necessary?
                  && ( !(friends & obj->getEnemies()) || !obj->getDamageTop() )
                  && touchesAtBottom(*obj) )
            {
                platform = &*obj;
                numJumps = 0;
                break;
            }
    }
    
    coord.x += velocityX * time;
    coord.y += velocityY * time;
    
    if(boundBox.l && collisionLeft() < game.getWorldLeft())
    {
        velocityX = 0;
        coord.x = game.getWorldLeft() - tile.collisionBox.l;
    }
    else if(boundBox.r && collisionRight() > game.getWorldRight())
    {
        velocityX = 0;
        coord.x = game.getWorldRight() - width + tile.collisionBox.r;
    }
    else if(boundBox.t && collisionTop() < game.getWorldTop())
    {
        velocityY = 0;
        coord.y = game.getWorldTop() - tile.collisionBox.r;
    }
    else if(boundBox.b && collisionBottom() > game.getWorldBottom())
    {
        velocityY = 0;
        coord.y = game.getWorldBottom() - height + tile.collisionBox.b;
    }
}

void ChimpMobile::accelerate()
{
    if(runningRight)
    {
        if(sprinting && velocityX > -approx_zero_float)
            velocityX += run_accel*sprint_factor - velocityX*resistance_x;
        else
            velocityX += run_accel - velocityX*resistance_x;
    }
    else if(runningLeft)
    {
        if(sprinting && velocityX < approx_zero_float)
            velocityX += -run_accel*sprint_factor - velocityX*resistance_x;
        else
            velocityX += -run_accel - velocityX * resistance_x;
    }
    else
        velocityX *= stop_factor;
    
    if(velocityY > 0)
        stopJumping();
    if(platform)
        velocityY = 0;
    else
        velocityY += accelerationY - velocityY * resistance_y;
}

/**
 * @brief ChimpMobile::deactivate()
 * 
 * calls ChimpObject::deactivate(). This Mobile is returned to their initial position.
 */
void ChimpMobile::deactivate()
{
    ChimpObject::deactivate();
    if(respawn)
        reset();
}

bool ChimpMobile::setMaxJumps(const int max)
{
    if(max < 0)
        return false;
    maxJumps = max;
    return true;
}

bool ChimpMobile::setScriptBehavior(const std::string& script)
{
    struct stat buffer;
    if(   stat(script.c_str(), &buffer) == 0
       && ( script.substr(script.size()-4, 4) == ".lua" || script.substr(script.size()-5, 5) == ".luac" ))
    {
        scriptBehavior = script;
        return true;
    }
    return false;
}

bool ChimpMobile::setScriptInit(const std::string& script)
{
    struct stat buffer;
    if(   stat(script.c_str(), &buffer) == 0
       && ( script.substr(script.size()-4, 4) == ".lua" || script.substr(script.size()-5, 5) == ".luac" ))
    {
        scriptInit = script;
        return true;
    }
    return false;
}

/**
 * @brief ChimpMobile::setRunImpulse()
 * 
 * Sets ChimpMobile::run_impulse and uses it to set approx_zero_float.
 * 
 * @param impulse Value for run_impulse.
 */
void ChimpMobile::setRunAccel(const float accel)
{
    run_accel = accel;
    approx_zero_float = run_accel / 4.0;
}

/**
 * @brief ChimpMobile::setResistanceY
 * 
 * Sets resistance_y and uses it to set approx_zero_y.
 * 
 * @param resistance Value for resistance_y
 */
void ChimpMobile::setResistanceY(const float resistance)
{
    resistance_y = resistance;
    approx_zero_y = GRAVITY * MS_PER_ACCEL / resistance_y * APPROX_ZERO_Y_FACTOR;
}

void ChimpMobile::runScript(std::string& script, lua_State* const luast)
{
    if(script.empty())
        return;   
    
    ChimpGame::setCurrentObject(this); 
    
    if(luaL_loadfile(luast, script.c_str()) != LUA_OK)
    {
        std::cerr << lua_tostring(luast, -1) << std::endl;
        lua_pop(luast, 1);
        return;
    }
    
    //if(lua_pcall(luast, 0, LUA_MULTRET, 0) != LUA_OK)
    if(lua_pcall(luast, 0, 0, 0) != LUA_OK)
    {
        std::cerr << lua_tostring(luast, -1) << std::endl;
        lua_pop(luast, 1);
        return;
    }
}

} // namespace chimp






















