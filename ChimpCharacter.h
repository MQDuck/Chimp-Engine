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

#ifndef CHIMPCHARACTER_H
#define CHIMPCHARACTER_H

#include <vector>
#include "ChimpObject.h"
#include "ChimpMobile.h"

namespace chimp
{

typedef std::vector<ChimpTile> TileVec;
    
class ChimpCharacter : public ChimpMobile
{
protected:
    Uint32 idleTime; // 0 means not idleing
    size_t tileIndex;
    bool vulnerable;
    TileVec tilesRun, tilesJump, tilesIdle;
    Coordinate moveStart;
    int maxHealth, health;
    
public:
    ChimpCharacter(SDL_Renderer* rend, const TileVec& tilRn, const TileVec& tilJmp, const TileVec& tilIdl,
                   const int pX = 0, const int pY = 0, const int tilesX = 1, const int tilesY = 1,
                   const Faction frnds = FACTION_VOID, const Faction enms = FACTION_VOID,
                   const int maxH = DEFAULT_HEALTH);
    ~ChimpCharacter() {}
    
    inline void makeInvulnerable() { vulnerable = false; }
    inline void makeVulnerable() { vulnerable = true; }
    inline TileVec& getTilesRun() { return tilesRun; }
    inline void setTilesRun(const TileVec& vec) { tilesRun = vec; }
    inline TileVec& getTilesJump() { return tilesJump; }
    inline void setTilesJump(const TileVec& vec) { tilesJump = vec; }
    inline TileVec& getTilesIdle() { return tilesIdle; }
    inline void setTilesIdle(const TileVec& vec) { tilesIdle = vec; }
    
    void runRight();
    void runLeft();
    void jump();
    void reset();
    
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    static Uint32 vulnerableTimer(Uint32 interval, void* character)
    {
        ((ChimpCharacter*)character)->makeVulnerable();
        return 0;
    }
    #pragma GCC diagnostic pop
    
    int getHealth() const { return health; }
    void setHealth(const int heal) { health = heal; }
    int getMaxHealth() const { return maxHealth; }
    void setMaxHealth(const int heal) { maxHealth = heal; }
    
    void update(const ObjectVector& objects, const IntBox& screen, const IntBox& world, const Uint32 time);
    void render(const IntBox& screen);
};

} // namespace chimp

#endif // CHIMPCHARACTER_H
