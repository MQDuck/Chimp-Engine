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

namespace chimp
{

ChimpMobile::ChimpMobile(const ChimpTile& til, SDL_Renderer* rend, const int positionX, const int positionY)
    : ChimpMobile(til, rend, positionX, positionY, 1, 1) {}

ChimpMobile::ChimpMobile(const ChimpTile& til, SDL_Renderer* rend,
                         const int positionX, const int positionY, const int tileX, const int tileY)
    : ChimpObject(til, rend, positionX, positionY, tileX, tileY)
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
    flip = SDL_FLIP_NONE;
}

void ChimpMobile::runLeft()
{
    //cout << "running left" << endl;
    if( approxZeroF(velocityX) )
        velocityX -= run_impulse - velocityX * resistance_x;
    runningLeft = true;
    runningRight = false;
    flip = SDL_FLIP_HORIZONTAL;
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
    
    if( !runningLeft && !runningRight && approxZeroF(velocityX) )
        velocityX = 0;
    
    /*if(velocityY > 0)
        accelerationY = GRAVITY;*/
    
    if( platform && collisionBottom() > platform->collisionTop() )
        posY -= collisionBottom() - platform->collisionTop();
    
    // (falling OR moved off previous plaform) AND not at bottom of screen
    if(   (velocityY > 0 || ( platform && !touchesAtBottom(*platform)) )
       && !approxZeroF(SCREEN_HEIGHT - posY - height) )
    {
        accelerationY = GRAVITY;
        platform = nullptr;
        for(std::unique_ptr<ChimpObject>& obj : objects)
        {
            if( touchesAtBottom(*obj) )
            {
                accelerationY = 0;
                velocityY = 0;
                posY = (*obj).collisionTop() - height + tile.collisionRect.h;
                doubleJumped = false;
                platform = &*obj;
                break;
            }
        }
    }
    velocityY += accelerationY - velocityY * resistance_y;
    
    posX += velocityX;
    posY += velocityY;
    if(platform)
    {
        posX += platform->getVelocityX();
        posY = platform->collisionTop() - height + tile.collisionRect.h;
    }
    
    if(screenBoundLeft && collisionLeft() < 0)
    {
        velocityX = 0;
        posX = -tile.collisionRect.x;
    }
    else if(screenBoundRight && collisionRight() > SCREEN_WIDTH)
    {
        velocityX = 0;
        posX = SCREEN_WIDTH - width + tile.collisionRect.w;
    }
    else if(screenBoundTop && collisionTop() < 0)
    {
        velocityY = 0;
        posY = -tile.collisionRect.y;
    }
    else if(screenBoundBottom && collisionBottom() > SCREEN_HEIGHT)
    {
        velocityY = 0;
        posY = SCREEN_HEIGHT - height + tile.collisionRect.h;
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
    approx_zero_y = GRAVITY / resistance_y * APPROX_ZERO_Y_FACTOR; // i.e. half terminal Y velocity
}

} // namespace chimp






















