#ifndef CHIMPGAME_H
#define CHIMPGAME_H

#include <SDL2/SDL.h>
#include <vector>
#include "ChimpConstants.h"
#include "ChimpDefines.h"
#include "ChimpTile.h"
#include "ChimpObject.h"
#include "ChimpMobile.h"
#include "ChimpCharacter.h"
#include "cleanup.h"
#include "SDLUtils.h"

namespace chimp
{

enum Layer { BACK, MID, FORE };

typedef std::vector<std::unique_ptr<ChimpObject>> ObjectVector;

class ChimpGame
{
private:
    SDL_Renderer* renderer;
    ChimpCharacter player;
    ObjectVector background, middle, foreground;
    
public:
    ChimpGame(SDL_Renderer* rend, const ChimpCharacter& plyr);
    
    ChimpCharacter& getPlayer() { return player; }
    ChimpObject& getObj(Layer lay, size_t in);
    ChimpObject& getObjBack(Layer lay);
    void pushObj(Layer lay, ChimpTile& til, const int x, const int y, const int tilesX = 1, const int tilesY = 1);
    void pushMob(Layer lay, ChimpTile& til, const int x, const int y, const int tilesX = 1, const int tilesY = 1);
    void pushChar(Layer lay, ChimpTile& til, const int x, const int y, const int tilesX = 1, const int tilesY = 1,
                  const int maxH = 100, const Faction frnds = FACTION_VOID, const Faction emns = FACTION_VOID);
    
    void render();
};

} // namespace chimp

#endif // CHIMPGAME_H
