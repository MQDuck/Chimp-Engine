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

ChimpMobile::ChimpMobile(SDL_Texture* tex, SDL_Rect& texRect, SDL_Rect& collRect, SDL_Renderer* rend, const int positionX, const int positionY)
    : ChimpMobile(tex, texRect, collRect, rend, positionX, positionY, 1, 1) {}

ChimpMobile::ChimpMobile(SDL_Texture* tex, SDL_Rect& texRect, SDL_Rect& collRect, SDL_Renderer* rend,
                         const int positionX, const int positionY, const int tileX, const int tileY)
    : ChimpObject(tex, texRect, collRect, rend, positionX, positionY, tileX, tileY)
{
    accelerationY = GRAVITY;
    velocityX = 0;
    velocityY = GRAVITY;
    runningRight = false;
    runningLeft = false;
    doubleJumped = false;
    sprinting = false;
    jumper = false;
    screenBoundLeft = false;
    screenBoundRight = false;
    screenBoundTop = false;
    screenBoundBottom = false;
    platform = nullptr;
    
    setRunImpulse(RUN_IMPULSE);
    run_accel = RUN_ACCEL;
    jump_impulse = JUMP_IMPULSE;
    double_jump_fraction = DOUBLE_JUMP_FRACTION;
    jump_accel = JUMP_ACCEL;
    stop_factor = STOP_FACTOR;
    sprint_factor = SPRINT_FACTOR;
    resistance_x = RESISTANCE_X;
    setResistanceY(RESISTANCE_Y);
}

void ChimpMobile::runRight()
{
    //cout << "running right" << endl;
    if( approxZeroF(velocityX) )
        velocityX += run_impulse - velocityX * resistance_x;
    runningRight = true;
    runningLeft = false;
}

void ChimpMobile::runLeft()
{
    //cout << "running left" << endl;
    if( approxZeroF(velocityX) )
        velocityX -= run_impulse - velocityX * resistance_x;
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
    if(sprinting && velocityX > -approx_zero_float)
        velocityX += run_accel*sprint_factor - velocityX*resistance_x;
    else
        velocityX += run_accel - velocityX*resistance_x;
}

void ChimpMobile::accelerateLeft()
{
    if(sprinting && velocityX < approx_zero_float)
        velocityX += -run_accel*sprint_factor - velocityX*resistance_x;
    else
        velocityX += -run_accel - velocityX * resistance_x;
}

void ChimpMobile::jump()
{
    if(!doubleJumped)
    {
        if(platform == nullptr)
        {
            doubleJumped = true;
            velocityY = jump_impulse * double_jump_fraction;
        }
        else
        {
            velocityY = jump_impulse;
            platform = nullptr;
        }
        accelerationY = jump_accel + GRAVITY;
    }
}

void ChimpMobile::stopJumping()
{
    if(!platform)
        accelerationY = GRAVITY;
}

void ChimpMobile::sprint() { sprinting = true; }
void ChimpMobile::stopSprinting() { sprinting = false; }

void ChimpMobile::update(std::vector<std::unique_ptr<ChimpObject>>& objects)
{
    if(runningRight)
        accelerateRight();
    else if(runningLeft)
        accelerateLeft();
    else
        velocityX *= stop_factor;    
    
    if(jumper && platform)
        jump();
    
    /*if(velocityY > 0)
        accelerationY = GRAVITY;*/
    
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
                positionRect.y = (*obj).getCollisionTop() - height + collisionRect.h;
                doubleJumped = false;
                platform = &*obj;
                break;
            }
        }
    }
    velocityY += accelerationY - velocityY * resistance_y;
    
    positionRect.x += round(velocityX); // Rounding might not be necessary    
    positionRect.y += round(velocityY); // Rounding might not be necessary
    if(platform)
    {
        positionRect.x += round( platform->getVelocityX() ); // Rounding might not be necessary
        //positionRect.y = platform->getPosRectY() - height;
        positionRect.y = platform->getCollisionTop() - height + collisionRect.h;
    }
    
    if(screenBoundLeft && getCollisionLeft() < 0)
    {
        velocityX = 0;
        positionRect.x = -collisionRect.x;
    }
    else if(screenBoundRight && getCollisionRight() > SCREEN_WIDTH)
    {
        velocityX = 0;
        positionRect.x = SCREEN_WIDTH - width + collisionRect.w;
    }
    else if(screenBoundTop && getCollisionTop() < 0)
    {
        velocityY = 0;
        positionRect.y = -collisionRect.y;
    }
    else if(screenBoundBottom && getCollisionBottom() > SCREEN_HEIGHT)
    {
        velocityY = 0;
        positionRect.y = SCREEN_HEIGHT - height + collisionRect.h;
    }
}

void ChimpMobile::setRunImpulse(const float impulse)
{
    run_impulse = impulse;
    approx_zero_float = run_impulse / 4.0;
}

void ChimpMobile::setResistanceY(const float resistance)
{
    resistance_y = resistance;
    approx_zero_y = int( ceil(GRAVITY / resistance_y * APPROX_ZERO_Y_FACTOR) ); // i.e. half terminal Y velocity
}






















