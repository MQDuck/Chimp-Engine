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

#include "ChimpMobile.h"

ChimpMobile::ChimpMobile(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX, const int positionY)
    : ChimpMobile(tex, texRect, rend, positionX, positionY, 1, 1) {}

ChimpMobile::ChimpMobile(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX,
                         const int positionY, const int tileX, const int tileY)
    : ChimpObject(tex, texRect, rend, positionX, positionY, tileX, tileY)
{
    //accelerationX = 0;
    accelerationY = 0;
    velocityX = 0;
    velocityY = GRAVITY;
    runningRight = false;
    runningLeft = false;
    doubleJumped = false;
    sprinting = false;
    platform = nullptr;
}

void ChimpMobile::runRight()
{
    //cout << "running right" << endl;
    if( approxZeroF(velocityX) )
        velocityX += RUN_IMPULSE - velocityX * RESISTANCE_X;
    runningRight = true;
    runningLeft = false;
}

void ChimpMobile::runLeft()
{
    //cout << "running left" << endl;
    if( approxZeroF(velocityX) )
        velocityX -= RUN_IMPULSE - velocityX * RESISTANCE_X;
    runningLeft = true;
    runningRight = false;
}

void ChimpMobile::stopRunningRight() { runningRight = false; }
void ChimpMobile::stopRunningLeft() { runningLeft = false; }
void ChimpMobile::stopRunning()
{
    runningRight = false;
    runningLeft = false;
}

void ChimpMobile::accelerateRight()
{
    if(sprinting && velocityX > -APPROX_ZERO_FLOAT)
        velocityX += RUN_ACCEL*SPRINT_FACTOR - velocityX*RESISTANCE_X;
    else
        velocityX += RUN_ACCEL - velocityX*RESISTANCE_X;
}

void ChimpMobile::accelerateLeft()
{
    if(sprinting && velocityX < APPROX_ZERO_FLOAT)
        velocityX += -RUN_ACCEL*SPRINT_FACTOR - velocityX*RESISTANCE_X;
    else
        velocityX += -RUN_ACCEL - velocityX * RESISTANCE_X;
}

void ChimpMobile::jump()
{
    if(!doubleJumped)
    {
        if(platform == nullptr)
        {
            doubleJumped = true;
            velocityY = DOUBLE_JUMP_VELOCITY;
        }
        else
        {
            velocityY = JUMP_IMPULSE;
            platform = nullptr;
        }
        accelerationY = JUMP_ACCEL + GRAVITY;
    }
}

void ChimpMobile::stopJumping()
{
    if(velocityY < 0)
        accelerationY = GRAVITY;
}

void ChimpMobile::sprint() { sprinting = true; }
void ChimpMobile::stopSprinting() { sprinting = false; }

void ChimpMobile::update(std::vector<std::unique_ptr<ChimpObject> >& objects)
{
    if(runningRight)
        accelerateRight();
    else if(runningLeft)
        accelerateLeft();
    else
        velocityX *= STOP_FACTOR;
    positionRect.x += round(velocityX); // Rounding might not be necessary
    
    if(positionRect.y > SCREEN_HEIGHT - positionRect.h)
    {
        accelerationY = 0;
        velocityY = 0;
        positionRect.y = SCREEN_HEIGHT - textureRect.h;
        doubleJumped = false;
    }
    else
    {
        if(velocityY > 0)
            accelerationY = GRAVITY;
        
        // (falling OR moved off previous plaform) AND not at bottom of screen
        if(   (velocityY > 0 || ( platform && !touchesAtBottom(*platform)) )
           && !approxZeroF(SCREEN_HEIGHT - positionRect.y - height) )
        {
            accelerationY = GRAVITY;
            platform = nullptr;
            for(std::unique_ptr<ChimpObject>& obj : objects)
            {
                if( touchesAtBottom(*obj) )
                {
                    accelerationY = 0;
                    velocityY = 0;
                    positionRect.y = (*obj).getPosRectY() - positionRect.h;
                    doubleJumped = false;
                    platform = &*obj;
                    break;
                }
            }
        }
        velocityY += accelerationY - velocityY * RESISTANCE_Y;
        positionRect.y += round(velocityY); // Rounding might not be necessary
    }
}






















