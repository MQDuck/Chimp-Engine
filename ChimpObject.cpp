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

#include <cmath>
#include "ChimpObject.h"

namespace chimp
{

/**
 * @brief ChimpObject::ChimpObject()
 * @param til Object's ChimpTile
 * @param rend SDL renderer that should be drawn to
 * @param pX Object's initial x-position
 * @param pY Object's initial y-position
 * @param tilesX How many times the ChimpTile should be tiled to the right.
 * @param tilesY How many times the ChimpTile should be tiled down.
 * @param frnds Factions to which the Object belongs.
 * @param enms Factions which the Object can deal damage to.
 */
ChimpObject::ChimpObject(SDL_Renderer* const rend, const ChimpTile& til, const int pX, const int pY, const int tilesX,
                         const int tilesY, Faction frnds, Faction enms)
    : tile(til), renderer(rend), friends(frnds), enemies(enms)
{
    setTilesX(tilesX);
    setTilesY(tilesY);
    coord.x = pX;
    coord.y = SCREEN_HEIGHT - pY - height;
    //coord.y = pY;
    center.x = (tile.collisionBox.l + width - tile.collisionBox.r) / 2.0;
    center.y = (tile.collisionBox.r + height - tile.collisionBox.b) / 2.0;
    damageBox.l = true;
    damageBox.r = true;
    damageBox.t = true;
    damageBox.b = true;
    
    approx_zero_float = RUN_IMPULSE / 4.0;
    approx_zero_y = int( ceil(GRAVITY / RESISTANCE_Y * APPROX_ZERO_Y_FACTOR) );
    flip = SDL_FLIP_NONE;
    active = false;
}

/**
 * @brief ChimpObject::initialize()
 * 
 * Should be run once for each object after it's added to the game. For Objects added at the start of the game, this
 * should be called only after all Objects are added.
 * 
 * @param screen Current window for this Object's game layer.
 */
void ChimpObject::initialize(const IntBox& screen)
{
    if(onScreen(screen))
        activate();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
/**
 * @brief ChimpObject::update()
 * 
 * This method should be called once every frame. Objects 
 * 
 * @param objects Vector for the game layer in which this Object resides.
 * @param screen Current window for this Object's game layer.
 * @param world Game world boundaries object.
 */
void ChimpObject::update(const ObjectVector& objects, const IntBox& screen, const IntBox& world, const Uint32 time)
{
    if(active)
    {
        if(   coord.x+width < screen.l - INACTIVE_ZONE
           || coord.x > screen.r + INACTIVE_ZONE
           || coord.y > screen.b + INACTIVE_ZONE
           || coord.y+height < screen.t - INACTIVE_ZONE)
            deactivate();
    }
    else
    {
        if(   coord.x <= screen.r + ACTIVE_ZONE
           && coord.y+height >= screen.t - ACTIVE_ZONE
           && coord.x+width >= screen.l - ACTIVE_ZONE
           && coord.y <= screen.b + ACTIVE_ZONE
           && !onScreen(screen) )
            activate();
    }
}
#pragma GCC diagnostic pop

/**
 * @brief ChimpObject::render()
 * 
 * Draws this Object to the screen.
 * 
 * @param screen Current window for this Object's game layer.
 */
void ChimpObject::render(const IntBox& screen)
{
    if(!active)
        return;
    // It remains to be seen if not rounding ever makes a perceivable difference. Perhaps while standing on an edge?
    for(int x = 0; x < width; x += tile.drawRect.w)
        for(int y = 0; y < height; y += tile.drawRect.h)
        {
            tile.drawRect.x = std::round(coord.x + x - screen.l);
            tile.drawRect.y = std::round(coord.y + y - screen.t);
            SDL_RenderCopyEx(renderer, tile.texture, &tile.textureRect, &tile.drawRect, 0, NULL, flip);
        }
}

bool ChimpObject::setFriends(const int facs)
{
    if(validateFactions(facs))
    {
        friends = facs;
        return true;
    }
    return false;
}

bool ChimpObject::setEnemies(const int facs)
{
    if(validateFactions(facs))
    {
        enemies = facs;
        return true;
    }
    return false;
}

/**
 * @brief ChimpObject::onScreen()
 * 
 * @param screen Current window for this Object's game layer.
 * @return true if this Object is at least partially inside the passed screen boundaries
 */
bool ChimpObject::onScreen(const IntBox& screen) const
{
    return coord.x <= screen.r && coord.y+height >= screen.t && coord.x+width >= screen.l && coord.y <= screen.b;
}

} // namespace chimp







































