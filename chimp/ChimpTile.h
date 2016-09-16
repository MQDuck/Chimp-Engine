#ifndef CHIMPTILE_H
#define CHIMPTILE_H

#include "ChimpStructs.h"

#include<SDL2/SDL.h>

namespace chimp
{

struct ChimpTile
{
    SDL_Texture* texture;
    SDL_Rect textureRect, drawRect;
    IntBox collisionBox;
    
    ChimpTile(SDL_Texture* tex, const SDL_Rect& texRect, SDL_Rect& drRect, const IntBox& colRect)
        : texture(tex), textureRect(texRect), drawRect(drRect), collisionBox(colRect) {}
    ChimpTile() {}
};

} // namespace chimp

#endif // CHIMPTILE_H
