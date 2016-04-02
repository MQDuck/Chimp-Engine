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

ChimpMobile::ChimpMobile(const ChimpTile& til, SDL_Renderer* rend, const int pX, const int pY, const int tilesX,
                         const int tilesY, Faction frnds, Faction enms)
    : ChimpObject(til, rend, pX, pY, tilesX, tilesY, frnds, enms)
{
    accelerationY = GRAVITY;
    velocityX = 0;
    velocityY = GRAVITY;
    runningRight = false;
    runningLeft = false;
    doubleJumped = false;
    sprinting = false;
    jumper = false;
    boundLeft = false;
    boundRight = false;
    boundTop = false;
    boundBottom = false;
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
            //doubleJumped = true;
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

void ChimpMobile::update(ObjectVector& objects, const IntBox& screen, const IntBox& world)
{
    ChimpObject::update(objects, screen, world);
    if(!active)
        return;
    
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
        coord.y -= collisionBottom() - platform->collisionTop();
    
    // (falling OR moved off previous plaform) AND not at bottom of screen
    if(   (velocityY > 0 || ( platform && !touchesAtBottom(*platform)) )
       && !approxZeroF(SCREEN_HEIGHT - coord.y - height) )
    {
        accelerationY = GRAVITY;
        platform = nullptr;
        for(std::unique_ptr<ChimpObject>& obj : objects)
        {
            if( touchesAtBottom(*obj) )
            {
                accelerationY = 0;
                velocityY = 0;
                coord.y = (*obj).collisionTop() - height + tile.collisionBox.b;
                doubleJumped = false;
                platform = &*obj;
                break;
            }
        }
    }
    velocityY += accelerationY - velocityY * resistance_y;
    
    coord.x += velocityX;
    coord.y += velocityY;
    if(platform)
    {
        coord.x += platform->getVelocityX();
        coord.y = platform->collisionTop() - height + tile.collisionBox.b;
    }
    
    if(boundLeft && collisionLeft() < world.l)
    {
        velocityX = 0;
        coord.x = world.l - tile.collisionBox.l;
    }
    else if(boundRight && collisionRight() > world.r)
    {
        velocityX = 0;
        coord.x = world.r - width + tile.collisionBox.r;
    }
    else if(boundTop && collisionTop() < world.t)
    {
        velocityY = 0;
        coord.y = world.t - tile.collisionBox.r;
    }
    else if(boundBottom && collisionBottom() > world.b)
    {
        velocityY = 0;
        coord.y = world.b - height + tile.collisionBox.b;
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






















