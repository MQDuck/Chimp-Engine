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
    ChimpCharacter player;
    ObjectVector background, middle, foreground;
    IntBox screen, worldBox;
    
public:
    ChimpGame(SDL_Renderer* rend, const ChimpCharacter& plyr);
    
    ChimpCharacter& getPlayer() { return player; }
    ChimpObject& getObj(Layer lay, size_t in);
    ChimpObject& getObjBack(Layer lay);
    bool setWorldBox(const int l, const int r, const int t, const int b);
    int getWorldLeft() const { return worldBox.l; }
    int getWorldRight() const { return worldBox.r; }
    int getWorldTop() const { return worldBox.t; }
    int getWorldBottom() const { return worldBox.b; }
    
    void pushObj(Layer lay, ChimpTile& til, const int x, const int y, const int tilesX = 1, const int tilesY = 1);
    void pushMob(Layer lay, ChimpTile& til, const int x, const int y, const int tilesX = 1, const int tilesY = 1);
    void pushChar(Layer lay, ChimpTile& til, const int x, const int y, const int tilesX = 1, const int tilesY = 1,
                  const int maxH = 100, const Faction frnds = FACTION_VOID, const Faction emns = FACTION_VOID);
    
    inline void translateScreenX(const int x);
    inline void translateScreenY(const int y);
    
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

























