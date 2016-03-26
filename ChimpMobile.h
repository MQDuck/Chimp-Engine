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

#ifndef CHIMPMOBILE_H
#define CHIMPMOBILE_H

#include <vector>
#include "ChimpObject.h"

class ChimpMobile : public ChimpObject
{
private:
    float accelerationY, velocityX, velocityY;
    bool runningRight, runningLeft, doubleJumped, sprinting;
    int standing;
    
public:
    ChimpMobile(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX, const int positionY);
    ChimpMobile(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX, const int positionY,
                const int tilX, const int tilY);

    void runRight();
    void runLeft();
    void stopRunningRight();
    void stopRunningLeft();
    void stopRunning();
    void accelerateRight();
    void accelerateLeft();
    void jump();
    void stopJumping();
    void sprint();
    void stopSprinting();

    void update(std::vector<ChimpObject>* objects);
};

#endif // CHIMPMOBILE_H
