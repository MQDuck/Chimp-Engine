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

#include "ChimpObject.h"
#include "ChimpGame.h"

#include <cmath>

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
    center.x = (tile.collisionBox.l + width - tile.collisionBox.r) / 2.0;
    center.y = (tile.collisionBox.r + height - tile.collisionBox.b) / 2.0;
    damageBox.l = true;
    damageBox.r = true;
    damageBox.t = true;
    damageBox.b = true;
    
    approx_zero_float = RUN_IMPULSE / 4.0;
    approx_zero_y = 0;
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void ChimpObject::initialize(const ChimpGame& game)
{
    if( onScreen(game.getMidWindow()) )
        activate();
}
#pragma GCC diagnostic pop

bool ChimpObject::touches(const ChimpObject &other) const
{
    return    collisionLeft()   <= other.collisionRight()
           && collisionRight()  >= other.collisionLeft()
           && collisionTop()    <= other.collisionBottom()
           && collisionBottom() >= other.collisionTop();
}

bool ChimpObject::touchesAtBottom(const ChimpObject& other) const
{
    return    collisionBottom() - approx_zero_y <= other.collisionTop()
           && collisionBottom() + approx_zero_y > other.collisionTop()
           && collisionLeft()  <= other.collisionRight()
           && collisionRight() >= other.collisionLeft();
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
void ChimpObject::update(const ObjectVector& objects, ChimpGame& game, const Uint32 time)
{
    if(active)
    {
        if(   coord.x+width < game.getMidWindowLeft() - game.getInactiveZone()
           || coord.x > game.getMidWindowRight() + game.getInactiveZone()
           || coord.y > game.getMidWindowBottom() + game.getInactiveZone()
           || coord.y+height < game.getMidWindowTop() - game.getInactiveZone())
            deactivate();
    }
    else
    {
        if(   coord.x <= game.getMidWindowRight() + game.getActiveZone()
           && coord.y+height >= game.getMidWindowTop() - game.getActiveZone()
           && coord.x+width >= game.getMidWindowLeft() - game.getActiveZone()
           && coord.y <= game.getMidWindowBottom() + game.getActiveZone()
           && !onScreen(game.getMidWindow()) )
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
    for(int x = 0; x < width; x += tile.drawRect.w)
        for(int y = 0; y < height; y += tile.drawRect.h)
        {
            tile.drawRect.x = coord.x + x - screen.l;
            tile.drawRect.y = coord.y + y - screen.t;
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
bool ChimpObject::onScreen(const IntBox& window) const
{
    return coord.x <= window.r && coord.y+height >= window.t && coord.x+width >= window.l && coord.y <= window.b;
}

} // namespace chimp







































