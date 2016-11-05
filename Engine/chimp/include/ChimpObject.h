/*
    Copyright 2016 Jeffrey Thomas Piercy
  
    This file is part of Chimp Engine.

    Chimp Engine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Chimp Engine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Chimp Engine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CHIMPOBJECT_H
#define CHIMPOBJECT_H

#include "cleanup.h"
#include "ChimpConstants.h"
#include "ChimpTile.h"
#include "ChimpStructs.h"
#include "ChimpStructs.h"

#if defined (__gnu_linux__) || defined (_WIN32)
#include <SDL2/SDL_mixer.h>
#endif
#if defined (__APPLE__) && defined (__MACH__)
#include <SDL2_mixer/SDL_mixer.h>
#endif

#include <memory>
#include <vector>
#include <lua.hpp>

namespace chimp
{

class ChimpGame;
class ChimpObject;

typedef std::unique_ptr<ChimpObject> ObjectPointer;
typedef std::vector<ObjectPointer> ObjectVector;
enum Faction { FACTION_VOID = 0, FACTION_PLAYER = 1<<0, FACTION_BADDIES = 1<<1 }; // each bit represents one unique faction

class ChimpObject
{    
protected:
    ChimpTile tile;
    SDL_Renderer* const renderer;
    Coordinate coord, center;
    float approx_zero_float, approx_zero_y;
    SDL_RendererFlip flip;
    int friends, enemies;
    bool active;
    int width, height;
    BoolBox damageBox;
    
public:
    ChimpObject(SDL_Renderer* const rend, const ChimpTile& til, const int pX = 0, const int pY = 0,
                const int tilesX = 1, const int tilesY = 1, Faction frnds = FACTION_VOID, Faction enms = FACTION_VOID);
    virtual ~ChimpObject() {}
    
    virtual void initialize(const ChimpGame& game);
    
    inline float getX() const { return coord.x; }
    inline void setX(const float x) { coord.x = x; }
    inline float getY() const { return coord.y; }
    inline void setY(const float y) { coord.y = y; }
    virtual float getInitialX() const { return getX(); }
    virtual void setInitialX(const float x) { setX(x); }
    virtual float getInitialY() const { return getY(); }
    virtual void setInitialY(const float y) { setY(y); }
    inline float getCenterX() const { return coord.x + center.x; }
    inline float getCenterY() const { return coord.y + center.y; }
    inline int getTilesX() const { return width / tile.drawRect.w; }
    inline void setTilesX(const int tilesX) { width = tile.drawRect.w*tilesX; }
    inline int getTilesY() const { return height / tile.drawRect.h; }
    inline void setTilesY(const int tilesY) { height = tile.drawRect.h*tilesY; }
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    inline int getTexRectW() const { return tile.textureRect.w; }
    inline int getTexRectH() const { return tile.textureRect.h; }
    inline float getCollisionLeft() const { return coord.x + tile.collisionBox.l; }
    inline float getCollisionRight() const { return coord.x + width - tile.collisionBox.r; }
    inline float getCollisionTop() const { return coord.y + tile.collisionBox.t; }
    inline float getCollisionBottom() const {return coord.y + height - tile.collisionBox.b; }
    inline bool getDamageLeft() const { return damageBox.l; }
    inline void setDamageLeft(const bool bl) { damageBox.l = bl; }
    inline bool getDamageRight() const { return damageBox.r; }
    inline void setDamageRight(const bool bl) { damageBox.r = bl; }
    inline bool getDamageTop() const { return damageBox.t; }
    inline void setDamageTop(const bool bl) { damageBox.t = bl; }
    inline bool getDamageBottom() const { return damageBox.b; }
    inline void setDamageBottom(const bool bl) { damageBox.b = bl; }
    inline ChimpTile& getChimpTile() { return tile; }
    inline void setChimpTile(const ChimpTile& til) { tile = til; }
    inline int getFriends() const { return friends; }
    inline bool setFriends(const int facs);
    inline void addFriend(const Faction fac) { friends |= fac; }
    inline int getEnemies() const { return enemies; }
    inline bool setEnemies(const int facs);
    inline void addEnemy(const Faction fac) { enemies |= fac; }
    
    inline bool isActive() const { return active; }
    inline bool onScreen(const IntBox& screen) const;
    virtual bool hasPlatform() const { return false; }
    
    virtual void activate() { active = true; }
    virtual void deactivate() { active = false; }
    
    bool touches(const ChimpObject& other) const;
    bool touchesAtBottom(const ChimpObject& other) const;
    
    virtual void update(const ObjectVector& objects, ChimpGame& game, const Uint32 time);
    virtual void accelerate() {}
    virtual void render(const IntBox& screen);
    virtual void reset() {}
    
    inline float getApproxZeroFloat() const { return approx_zero_float; }
    inline float getApproxZeroY() const { return approx_zero_y; }
    
    //ChimpObject& operator=(const ChimpObject& rhs);
    
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    virtual float getAccelerationY() const { return 0.0f; }
    virtual void setAccelerationY(const float accel) {}
    virtual float getVelocityX() const { return 0.0f; }
    virtual void setVelocityX(const float velocity) {}
    virtual float getVelocityY() const { return 0.0f; }
    virtual void setVelocityY(const float velocity) {}
    virtual void runRight() {}
    virtual void runLeft() {}
    virtual void stopRunningRight() {}
    virtual void stopRunningLeft() {}
    virtual void stopRunning() {}
    virtual float getRunImpulse() const { return 0.0f; }
    virtual void setRunImpulse(const float impulse) {}
    virtual float getRunAccel() const { return 0.0f; }
    virtual void setRunAccel(const float accel) {}
    virtual float getJumpImpulse() const { return 0.0f; }
    virtual void setJumpImpulse(const float impulse) {}
    virtual float getMultiJumpImpulse() const { return 0.0f; }
    virtual void setMultiJumpImpulse(const float fraction) {}
    virtual float getJumpAccel() const { return 0.0f; }
    virtual void setJumpAccel(const float accel) {}
    virtual float getStopFactor() const { return 0.0f; }
    virtual void setStopFactor(const float factor) {}
    virtual float getSprintFactor() const { return 0.0f; }
    virtual void setSprintFactor(const float factor) {}
    virtual float getResistanceX() const { return 0.0f; }
    virtual void setResistanceX(const float resistance) {}
    virtual float getResistanceY() const { return 0.0f; }
    virtual void setResistanceY(const float resistance) {}
    virtual int getHealth() const { return 0; }
    virtual void setHealth(const int heal) {}
    virtual int getMaxHealth() const { return 0; }
    virtual bool setMaxHealth(const int heal) { return true; }
    virtual bool getBoundLeft() const { return false; }
    virtual void setBoundLeft(bool b) {}
    virtual bool getBoundRight() const { return false; }
    virtual void setBoundRight(bool b) {}
    virtual bool getBoundTop() const { return false; }
    virtual void setBoundTop(bool b) { }
    virtual bool getBoundBottom() const { return false; }
    virtual void setBoundBottom(bool b) {}
    virtual bool getRespawn() const { return false; }
    virtual void setRespawn(const bool pd) {}
    virtual int getMaxJumps() const { return 0; }
    virtual bool setMaxJumps(const int max) { return true; }
    virtual std::string getScriptBehavior() const { return ""; }
    virtual bool setScriptBehavior(const std::string& behav) { return false; }
    virtual std::string getScriptInit() const { return ""; }
    virtual bool setScriptInit(const std::string& behav) { return false; }
    virtual void jump(ChimpGame& game) {}
    virtual void stopJumping() {}
    virtual void sprint() {}
    virtual void stopSprinting() {}
    virtual float getTerminalVelocityRun() { return 0.0f; }
    virtual float getTerminalVelocityFall() { return 0.0f; }
    virtual void setSoundJump(Mix_Chunk* const sound) {}
    virtual void setSoundMultijump(Mix_Chunk* const sound) {}
    #pragma GCC diagnostic pop
    
protected:
    inline bool approxZeroF(const float f) const { return f > -approx_zero_float && f < approx_zero_float; }
    inline bool validateFactions(const int facs) // false if facs contains a bit not corresponding to any faction
        { return !((facs|FACTION_PLAYER|FACTION_BADDIES) - FACTION_PLAYER - FACTION_BADDIES); }
};

} // namespace chimp

#endif // CHIMPOBJECT_H















