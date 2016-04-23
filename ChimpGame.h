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

#ifndef CHIMPGAME_H
#define CHIMPGAME_H

#include <SDL2/SDL.h>
#include <vector>
#include "ChimpConstants.h"
#include "ChimpTile.h"
#include "ChimpObject.h"
#include "ChimpMobile.h"
#include "ChimpCharacter.h"
#include "cleanup.h"
#include "SDLUtils.h"

namespace chimp
{

enum Layer { BACK, MID, FORE };

class ChimpGame
{
private:
    SDL_Renderer* renderer;
    ChimpCharacter* player;
    ObjectVector background, middle, foreground;
    IntBox screen, worldBox;
    
public:
    ChimpGame(SDL_Renderer* rend, ChimpCharacter* plyr = nullptr);
    ~ChimpGame() { if(player) delete player; }
    
    ChimpCharacter*& getPlayer() { return player; }
    ChimpObject& getObj(Layer lay, size_t in);
    ChimpObject& getObjBack(Layer lay);
    bool setWorldBox(const int l, const int r, const int t, const int b);
    int getWorldLeft() const { return worldBox.l; }
    int getWorldRight() const { return worldBox.r; }
    int getWorldTop() const { return worldBox.t; }
    int getWorldBottom() const { return worldBox.b; }
    
    void pushObj(const Layer lay, const ChimpTile& til, const int x, const int y, const int tilesX = 1,
                 const int tilesY = 1);
    void pushMob(const Layer lay, const ChimpTile& til, const int x, const int y, const int tilesX = 1,
                 const int tilesY = 1);
    void pushChar(const Layer lay, const ChimpTile& til, const int x, const int y, const int tilesX = 1,
                  const int tilesY = 1, const int maxH = 100, const Faction frnds = FACTION_VOID,
                  const Faction enms = FACTION_VOID);
    void pushChar(const Layer lay, const TileVec& tilRn, const TileVec& tilJmp, TileVec& tilIdl, const int x,
                  const int y, const int tilesX = 1, const int tilesY = 1, const int maxH = 100,
                  const Faction frnds = FACTION_VOID, const Faction enms = FACTION_VOID);
    
    inline void translateScreenX(const int x);
    inline void translateScreenY(const int y);
    
    void initialize();
    void update();
    void render();
};

inline void ChimpGame::translateScreenX(const int x)
{
    screen.l += x;
    screen.r += x;
    
    if(screen.l < worldBox.l)
    {
        screen.r += worldBox.l - screen.l;
        screen.l = worldBox.l;
    }
    else if(screen.r > worldBox.r)
    {
        screen.l += worldBox.r - screen.r;
        screen.r = worldBox.r;
    }
}

inline void ChimpGame::translateScreenY(const int y)
{
    screen.t += y;
    screen.b += y;
    
    if(screen.t < worldBox.t)
    {
        screen.b += worldBox.t - screen.t;
        screen.t = worldBox.t;
    }
    else if(screen.b > worldBox.b)
    {
        screen.t += worldBox.b - screen.b;
        screen.b = worldBox.b;
    }
}

} // namespace chimp

#endif // CHIMPGAME_H

























