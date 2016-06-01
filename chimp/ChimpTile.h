#ifndef CHIMPTILE_H
#define CHIMPTILE_H

#include<SDL2/SDL.h>
#include "ChimpStructs.h"

namespace chimp
{

struct ChimpTile
{
    SDL_Texture* texture;
    SDL_Rect textureRect, drawRect;
    IntBox collisionBox;
    
    ChimpTile(SDL_Texture* tex, const SDL_Rect& texRect, SDL_Rect& drRect, const Box<int>& colRect)
        : texture(tex), textureRect(texRect), drawRect(drRect), collisionBox(colRect) {}
    ChimpTile() {}
};

} // namespace chimp

#endif // CHIMPTILE_H
