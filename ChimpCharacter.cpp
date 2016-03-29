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

#include "ChimpCharacter.h"

namespace chimp
{

ChimpCharacter::ChimpCharacter(const ChimpTile& til, SDL_Renderer* rend,
                               const int positionX, const int positionY, const int tilX, const int tilY, int maxH,
                               Faction frnds, Faction enms)
    : ChimpMobile(til, rend, positionX, positionY, tilX, tilY), maxHealth(maxH), friends(frnds),
      enemies(enms)
{
    health = maxHealth;
}

void ChimpCharacter::update(std::vector<std::unique_ptr<ChimpObject>>& objects)
{
    for(std::unique_ptr<ChimpObject>& obj : objects)
    {
        if(platform == &*obj)
            continue;
        if( touches(*obj) && ( friends & (*obj).getEnemies()) )
        {
            float x = getCenterX() - (*obj).getCenterX();
            float x2 = x*x;
            float y = getCenterY() - (*obj).getCenterY();
            float y2 = y*y;
            
            velocityX = sqrt(DAMAGE_VELOCITY / (x2+y2)) * x;
            velocityY = sqrt(DAMAGE_VELOCITY / (x2+y2)) * y;
            
            health -= DAMAGE;
        }
    }
    
    ChimpMobile::update(objects);
    
    if(coord.y > SCREEN_HEIGHT + height)
        health = 0;
}

} // namespace chimp
























