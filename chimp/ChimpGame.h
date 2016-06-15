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
#include <lua.hpp>
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
    IntBox midWindow, backWindow, foreWindow, worldBox;
    unsigned int windowWidth, windowHeight;
    float scroll_factor_back, scroll_factor_fore;
    lua_State* luast;
    
    static ChimpGame* self;
    static ChimpObject* currentObj;
    
public:
    ChimpGame(SDL_Renderer* const rend, const unsigned int winWidth, const unsigned int winHeight,
              ChimpCharacter* plyr = nullptr);
    ~ChimpGame() { if(player) delete player; }
    
    ChimpCharacter*& getPlayer() { return player; }
    ChimpObject& getObj(Layer lay, size_t in);
    ChimpObject& getObjBack(Layer lay);
    bool setWorldBox(const int l, const int r, const int t, const int b);
    int getWorldLeft() const { return worldBox.l; }
    int getWorldRight() const { return worldBox.r; }
    int getWorldTop() const { return worldBox.t; }
    int getWorldBottom() const { return worldBox.b; }
    int getMidWindowLeft() const { return midWindow.l; }
    int getMidWindowRight() const { return midWindow.r; }
    int getMidWindowTop() const { return midWindow.t; }
    int getMidWindowBottom() const { return midWindow.b; }
    SDL_Renderer* getRenderer() const { return renderer; }
    bool setRenderer(SDL_Renderer* const rend);
    unsigned int getWindowWidth() const { return windowWidth; }
    void setWindowWidth(const unsigned int winWidth) { windowWidth = winWidth; }
    unsigned int getWindowHeight() { return windowHeight; }
    void setWindowHeight(const unsigned int winHeight) { windowHeight = winHeight; }
    float getScrollFactor(const Layer lay) const;
    bool setScrollFactor(const Layer lay, const float factor);
    const IntBox& getMidWindow() const { return midWindow; }
    const IntBox& getBackWindow() const { return backWindow; }
    const IntBox& getForeWindow() const { return foreWindow; }
    inline lua_State* getLuaState() const { return luast; }
    
    inline static ChimpGame* getGame() { return self; }
    inline static ChimpObject* getCurrentObject() { return currentObj; }
    inline static void setCurrentObject(ChimpObject* const obj) { currentObj = obj; }
    
    void pushObj(const Layer layr, const ChimpTile& til, const int x = 0, const int y = 0, const int tilesX = 1,
                 const int tilesY = 1);
    void pushMob(const Layer layr, const ChimpTile& til, const int x = 0, const int y = 0, const int tilesX = 1,
                 const int tilesY = 1);
    void pushChar(const Layer lay, const ChimpTile& til, const int x = 0, const int y = 0, const int tilesX = 1,
                  const int tilesY = 1, const int maxH = HEALTH, const Faction frnds = FACTION_VOID,
                  const Faction enms = FACTION_VOID);
    void pushChar(const Layer lay, const TileVec& tilRn, const TileVec& tilJmp, TileVec& tilIdl, const int x = 0,
                  const int y = 0, const int tilesX = 1, const int tilesY = 1, const int maxH = 100,
                  const Faction frnds = FACTION_VOID, const Faction enms = FACTION_VOID);
    
    void translateWindowX(const int x);
    void translateWindowY(const int y);
    
    void initialize();
    void update(const Uint32 time);
    void render();
    void reset();
    
private:
    /*void updateBack();
    void updateMid();
    void updateFore();
    static int updateThreadBack(void* game);
    static int updateThreadMid(void* game);
    static int updateThreadFore(void* game);*/
};

} // namespace chimp

#endif // CHIMPGAME_H

























