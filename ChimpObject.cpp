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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChimpObject.h"

namespace chimp
{

ChimpObject::ChimpObject(const ChimpTile& til, SDL_Renderer* rend,
                         const int pX, const int pY)
    : ChimpObject(til, rend, pX, pY, 1, 1) {}

ChimpObject::ChimpObject(const ChimpTile& til, SDL_Renderer* rend, const int pX, const int pY, const int tilesX,
                         const int tilesY)
    : tile(til), renderer(rend), width(tile.textureRect.w*tilesX),
      height(tile.textureRect.h*tilesY)
{
    coord.x = pX;
    coord.y = SCREEN_HEIGHT - pY - height;
    center.x = (tile.collisionRect.x + width - tile.collisionRect.w) / 2.0;
    center.y = (tile.collisionRect.y + height - tile.collisionRect.h) / 2.0;
    
    approx_zero_float = RUN_IMPULSE / 4.0;
    approx_zero_y = int( ceil(GRAVITY / RESISTANCE_Y * APPROX_ZERO_Y_FACTOR) );
    flip = SDL_FLIP_NONE;
}

void ChimpObject::render()
{
    SDL_Rect rendRect;
    // It remains to be seen if not rounding ever makes a perceivable difference. Perhaps while standing on an edge?
    rendRect.x = round(coord.x);
    rendRect.y = round(coord.y);
    //rendRect.x = coord.x;
    //rendRect.y = coord.y;
    rendRect.w = tile.textureRect.w;
    rendRect.h = tile.textureRect.h;
    for(int x = 0; x < width; x += tile.textureRect.w)
        for(int y = 0; y < height; y += tile.textureRect.h)
        {
            rendRect.x = coord.x + x;
            rendRect.y = coord.y + y;
            SDL_RenderCopyEx(renderer, tile.texture, &tile.textureRect, &rendRect, 0, NULL, flip);
        }
}

} // namespace chimp







































