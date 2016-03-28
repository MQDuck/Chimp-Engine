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

#ifndef CHIMPCHARACTER_H
#define CHIMPCHARACTER_H


#include "ChimpObject.h"
#include "ChimpMobile.h"

class ChimpCharacter : public ChimpMobile
{
protected:
    int maxHealth, health, friends, enemies;
    
public:
    ChimpCharacter(const ChimpTile& tex, SDL_Renderer* rend,
                   const int positionX, const int positionY, const int tilX, const int tilY, int maxH, int frnds,
                   int enms);
    
    int getHealth() const { return health; }
    void setHealth(const int heal) { health = heal; }
    
    void update(std::vector<std::unique_ptr<ChimpObject>>& objects);
};

#endif // CHIMPCHARACTER_H
