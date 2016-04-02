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

#include <cmath>
#include "ChimpCharacter.h"

namespace chimp
{

ChimpCharacter::ChimpCharacter(const TileVec& tilRn, const TileVec& tilJmp, SDL_Renderer* rend, const int pX,
                               const int pY, const int tilesX, const int tilesY, Faction frnds, Faction enms,
                               const int maxH)
    : ChimpMobile(tilRn[0], rend, pX, pY, tilesX, tilesY, frnds, enms), tilesRun(tilRn), tilesJump(tilJmp),
      maxHealth(maxH)
{
    health = maxHealth;
    vulnerable = true;
}

void ChimpCharacter::runRight()
{
    if(!runningRight)
    {
        moveStart.x = coord.x;
        tileIndex = 0;
    }
    ChimpMobile::runRight();
}

void ChimpCharacter::runLeft()
{
    if(!runningLeft)
    {
        moveStart.x = coord.x;
        tileIndex = 0;
    }
    ChimpMobile::runLeft();
}

void ChimpCharacter::jump()
{
    if(platform)
    {
        tile = tilesJump[0];
        moveStart.x = coord.x;
        tileIndex = 0;
    }
    ChimpMobile::jump();
}

void ChimpCharacter::update(ObjectVector& objects, const IntBox& screen, const IntBox& world)
{    
    if(active && vulnerable)
        for(std::unique_ptr<ChimpObject>& obj : objects)
        {
            //if(platform == &*obj)
            if( !(*obj).getDamageTop() && (platform == &*obj || touchesAtBottom(*obj)) )
                continue;
            if( touches(*obj) && ( friends & (*obj).getEnemies()) )
            {
                float x = getCenterX() - (*obj).getCenterX();
                float y = getCenterY() - (*obj).getCenterY();
                float invMag = 1.0 / std::sqrt(x*x + y*y);
                
                velocityX = DAMAGE_VELOCITY * x * invMag;
                velocityY = DAMAGE_VELOCITY * y * invMag;
                
                health -= DAMAGE;
                
                makeInvulnerable();
                SDL_AddTimer(500, vulnerableTimer, this);
            }
        }
    
    ChimpMobile::update(objects, screen, world);
    
    if(coord.y > SCREEN_HEIGHT + height)
        health = 0;
}

void ChimpCharacter::render(const IntBox& screen)
{
    if(!platform)
    {
        /*size_t in = std::abs((int)(coord.y-moveStart.y) / 100) % tilesJump.size();
        if(tileIndex != in)
        {
            tile = tilesJump[in];
            tileIndex = in;
        }*/
        if( (int)(coord.y-moveStart.y) / 100 )
        {
            tileIndex = (tileIndex+1) % tilesJump.size();
            tile = tilesJump[tileIndex];
            moveStart.y = coord.y;
        }
    }
    else if(runningLeft || runningRight)
    {
        size_t in = std::abs((int)(coord.x-moveStart.x) / 50) % tilesRun.size();
        if(tileIndex != in)
        {
            tile = tilesRun[in];
            tileIndex = in;
        }
    }
    
    if(!vulnerable)
    {
        SDL_SetTextureColorMod(tile.texture, 255, 0, 0);
        ChimpMobile::render(screen);
        SDL_SetTextureColorMod(tile.texture, 255, 255, 255);
    }
    else
        ChimpMobile::render(screen);
}

} // namespace chimp
























