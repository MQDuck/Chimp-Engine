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

namespace chimp
{

class ChimpCharacter : public ChimpMobile
{
protected:
    int maxHealth, health;
    bool vulnerable;
    
public:
    ChimpCharacter(const ChimpTile& til, SDL_Renderer* rend, const int pX, const int pY, const int tilesX = 1,
                   const int tilesY = 1, Faction frnds = FACTION_VOID, Faction enms = FACTION_VOID,
                   const int maxH = 100);
    
    void makeInvulnerable() { vulnerable = false; }
    void makeVulnerable() { vulnerable = true; }
    //unsigned int makeVulnerable(unsigned int interval, void* param) { vulnerable = true; }
    
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    static Uint32 vulnerableTimer(Uint32 interval, void* character)
    {
        ((ChimpCharacter*)character)->makeVulnerable();
        return 0;
    }
    #pragma GCC diagnostic pop
    
    int getHealth() const { return health; }
    void setHealth(const int heal) { health = heal; }
    inline int getFriends() const { return friends; }
    inline int getEnemies() const { return enemies; }
    
    void update(ObjectVector& objects, const IntBox& screen, const IntBox& world);
    void render(const IntBox& screen);
};

} // namespace chimp

#endif // CHIMPCHARACTER_H
