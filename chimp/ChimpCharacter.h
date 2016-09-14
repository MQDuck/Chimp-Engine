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

#if defined __gnu_linux__
#include <SDL2/SDL_mixer.h>
#endif
#if defined __APPLE__ && defined __MACH__
#include <SDL2_mixer/SDL_mixer.h>
#endif

#include <vector>
#include "ChimpObject.h"
#include "ChimpMobile.h"

namespace chimp
{

class ChimpGame;

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
    Mix_Chunk* soundJump;
    Mix_Chunk* soundMultijump;
    
public:
    ChimpCharacter(SDL_Renderer* const rend, const TileVec& tilRn, const TileVec& tilJmp, const TileVec& tilIdl,
                   const int pX = 0, const int pY = 0, const int tilesX = 1, const int tilesY = 1,
                   const Faction frnds = FACTION_VOID, const Faction enms = FACTION_VOID,
                   const int maxH = HEALTH);
    ~ChimpCharacter() {}
    
    void initialize(const ChimpGame& game);
    
    inline bool getVulnerable() const { return vulnerable; }
    inline void setVulnerable(const bool vul) { vulnerable = vul; }
    inline TileVec& getTilesIdle() { return tilesIdle; }
    inline bool setTilesIdle(const TileVec& vec);
    inline TileVec& getTilesRun() { return tilesRun; }
    inline bool setTilesRun(const TileVec& vec);
    inline TileVec& getTilesJump() { return tilesJump; }
    inline bool setTilesJump(const TileVec& vec);
    inline void setSoundJump(Mix_Chunk* const sound) { soundJump = sound; }
    inline void setSoundMultijump(Mix_Chunk* const sound) { soundMultijump = sound; }
    
    void runRight();
    void runLeft();
    void jump(ChimpGame& game);
    void reset();
    
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    static Uint32 vulnerableTimer(Uint32 interval, void* character)
    {
        ((ChimpCharacter*)character)->setVulnerable(true);
        return 0;
    }
    #pragma GCC diagnostic pop
    
    int getHealth() const { return health; }
    void setHealth(const int heal) { health = heal; }
    int getMaxHealth() const { return maxHealth; }
    bool setMaxHealth(const int heal);// { maxHealth = heal; }
    
    void update(const ObjectVector& objects, ChimpGame& game, const Uint32 time);
    void render(const IntBox& screen);
    
protected:
    inline void playSound(Mix_Chunk* const sound, const ChimpGame& game) const;
};

} // namespace chimp

#endif // CHIMPCHARACTER_H
