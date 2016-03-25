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
    running = false;
    doubleJumped = false;
    standing = false;
}

void ChimpMobile::runRight()
{
    //cout << "running right" << endl;
    if( approxZero(velocityX) )
        velocityX += RUN_IMPULSE - velocityX * RESISTANCE_X;
    velocityX += RUN_ACCEL - velocityX * RESISTANCE_X;
    running = true;
}

void ChimpMobile::runLeft()
{
    //cout << "running left" << endl;
    if( approxZero(velocityX) )
        velocityX -= RUN_IMPULSE - velocityX * RESISTANCE_X;
    velocityX += -RUN_ACCEL - velocityX * RESISTANCE_X;
    running = true;
}

void ChimpMobile::stopRunningRight()
{
    if(velocityX > 0)
        running = false;
}

void ChimpMobile::stopRunningLeft()
{
    if(velocityX < 0)
        running = false;
}
void ChimpMobile::stopRunning()
{
    running = false;
}

void ChimpMobile::jump()
{
    if(!doubleJumped)
    {
        if(!standing)
        {
            doubleJumped = true;
            velocityY = DOUBLE_JUMP_IMPULSE;
        }
        else
        {
            velocityY = JUMP_IMPULSE;
            standing = false;
        }
        accelerationY = JUMP_ACCEL + GRAVITY;
    }
}

void ChimpMobile::stopJumping()
{
    if(velocityY < 0)
        accelerationY = GRAVITY;
}

void ChimpMobile::render(std::vector<ChimpObject>* objects)
{
    positionRect.x += round(velocityX); // Rounding might not be necessary
    if(!running)
        velocityX *= STOP_FACTOR;
    
    if(positionRect.y > SCREEN_HEIGHT - positionRect.h)
    {
        accelerationY = 0;
        velocityY = 0;
        positionRect.y = SCREEN_HEIGHT - textureRect.h;
        doubleJumped = false;
        standing = true;
    }
    else
    {
        if(velocityY > 0)
            accelerationY = GRAVITY;
        if( !approxZero(SCREEN_HEIGHT - positionRect.y - height) && (accelerationY == GRAVITY || approxZero(velocityY)) )
        {
            accelerationY = GRAVITY;
            standing = false;
            for(ChimpObject& obj : *objects)
            {
                if(   positionRect.y + height > obj.getPosRectY() - APPROX_ZERO
                   && positionRect.y + height < obj.getPosRectY() + obj.getHeight() + APPROX_ZERO
                   && (      positionRect.x > obj.getPosRectX()
                          && positionRect.x < obj.getPosRectX() + obj.getWidth()
                       ||    positionRect.x + width > obj.getPosRectX()
                          && positionRect.x + width < obj.getPosRectX() + obj.getWidth()) )
                {
                    accelerationY = 0;
                    velocityY = 0;
                    positionRect.y = obj.getPosRectY() - positionRect.h;
                    doubleJumped = false;
                    standing = true;
                    break;
                }
            }
        }
        velocityY += accelerationY - velocityY * RESISTANCE_Y;
        positionRect.y += round(velocityY); // Rounding might not be necessary
    }
    
    ChimpObject::render();
}























