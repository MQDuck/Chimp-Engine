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

#include <SDL/SDL_thread.h>

namespace chimp
{

enum Layer { BACK, MID, FORE };

class ChimpGame
{
private:
    SDL_Renderer* renderer;
    ChimpCharacter* player;
    ObjectVector background, middle, foreground;
    IntBox midWindow, backWindow, foreWindow, worldBox;
    unsigned int windowWidth, windowHeight;
    
public:
    ChimpGame(SDL_Renderer* rend, unsigned int winWidth, unsigned int winHeight, ChimpCharacter* plyr = nullptr);
    ~ChimpGame() { if(player) delete player; }
    
    ChimpCharacter*& getPlayer() { return player; }
    ChimpObject& getObj(Layer lay, size_t in);
    ChimpObject& getObjBack(Layer lay);
    bool setWorldBox(const int l, const int r, const int t, const int b);
    int getWorldLeft() const { return worldBox.l; }
    int getWorldRight() const { return worldBox.r; }
    int getWorldTop() const { return worldBox.t; }
    int getWorldBottom() const { return worldBox.b; }
    SDL_Renderer* getRenderer() const { return renderer; }
    bool setRenderer(SDL_Renderer* rend);
    unsigned int getWindowWidth() const { return windowWidth; }
    void setWindowWidth(const unsigned int winWidth) { windowWidth = winWidth; }
    unsigned int getWindowHeight() { return windowHeight; }
    void setWindowHeight(const unsigned int winHeight) { windowHeight = winHeight; }
    
    void pushObj(const Layer layr, const ChimpTile& til, const int x, const int y, const int tilesX = 1,
                 const int tilesY = 1);
    void pushMob(const Layer layr, const ChimpTile& til, const int x, const int y, const int tilesX = 1,
                 const int tilesY = 1);
    void pushChar(const Layer lay, const ChimpTile& til, const int x, const int y, const int tilesX = 1,
                  const int tilesY = 1, const int maxH = DEFAULT_HEALTH, const Faction frnds = FACTION_VOID,
                  const Faction enms = FACTION_VOID);
    void pushChar(const Layer lay, const TileVec& tilRn, const TileVec& tilJmp, TileVec& tilIdl, const int x,
                  const int y, const int tilesX = 1, const int tilesY = 1, const int maxH = 100,
                  const Faction frnds = FACTION_VOID, const Faction enms = FACTION_VOID);
    
    inline void translateWindowX(const int x);
    inline void translateWindowY(const int y);
    
    void initialize();
    void update();
    void render();
    void reset();
    
private:
    void updateBack();
    void updateMid();
    void updateFore();
    /*static int updateThreadBack(void* game);
    static int updateThreadMid(void* game);
    static int updateThreadFore(void* game);*/
};

inline void ChimpGame::translateWindowX(const int x)
{
    if(x == 0)
        return;
    
    midWindow.l += x;
    midWindow.r += x;
    
    if(midWindow.l < worldBox.l)
    {
        midWindow.r += worldBox.l - midWindow.l;
        midWindow.l = worldBox.l;
    }
    else if(midWindow.r > worldBox.r)
    {
        midWindow.l += worldBox.r - midWindow.r;
        midWindow.r = worldBox.r;
    }
    
    backWindow.l = midWindow.l * SCROLL_BACK_FACTOR;
    backWindow.r = midWindow.r * SCROLL_BACK_FACTOR;
    foreWindow.l = midWindow.l * SCROLL_FORE_FACTOR;
    foreWindow.r = midWindow.r * SCROLL_FORE_FACTOR;
}

inline void ChimpGame::translateWindowY(const int y)
{
    if(y == 0)
        return;
    
    midWindow.t += y;
    midWindow.b += y;
    
    if(midWindow.t < worldBox.t)
    {
        midWindow.b += worldBox.t - midWindow.t;
        midWindow.t = worldBox.t;
    }
    else if(midWindow.b > worldBox.b)
    {
        midWindow.t += worldBox.b - midWindow.b;
        midWindow.b = worldBox.b;
    }
    
    backWindow.t = midWindow.t * SCROLL_BACK_FACTOR;
    backWindow.b = midWindow.b * SCROLL_BACK_FACTOR;
    foreWindow.t = midWindow.t * SCROLL_FORE_FACTOR;
    foreWindow.b = midWindow.b * SCROLL_FORE_FACTOR;
}

} // namespace chimp

#endif // CHIMPGAME_H

























