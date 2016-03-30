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

ChimpCharacter::ChimpCharacter(const ChimpTile& til, SDL_Renderer* rend, const int pX, const int pY, const int tilesX, \
                               const int tilesY, Faction frnds, Faction enms, const int maxH)
    : ChimpMobile(til, rend, pX, pY, tilesX, tilesY, frnds, enms), maxHealth(maxH)
{
    health = maxHealth;
    vulnerable = true;
}

void ChimpCharacter::update(std::vector<std::unique_ptr<ChimpObject>>& objects)
{
    if(vulnerable)
        for(std::unique_ptr<ChimpObject>& obj : objects)
        {
            if(platform == &*obj)
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
    
    ChimpMobile::update(objects);
    
    if(coord.y > SCREEN_HEIGHT + height)
        health = 0;
}

void ChimpCharacter::render()
{
    if(!vulnerable)
    {
        SDL_SetTextureColorMod(tile.texture, 255, 0, 0);
        ChimpMobile::render();
        SDL_SetTextureColorMod(tile.texture, 255, 255, 255);
    }
    else
        ChimpMobile::render();
}

} // namespace chimp
























