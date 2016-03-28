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

#include <memory>
#include <vector>
#include "ChimpObject.h"
#include "ChimpTile.h"

class ChimpMobile : public ChimpObject
{
protected:
    bool runningRight, runningLeft, doubleJumped, sprinting, jumper, screenBoundLeft, screenBoundRight, screenBoundTop,
         screenBoundBottom;
    ChimpObject* platform; // pointer to object this mobile is standing on, nullptr if none

    float accelerationY, velocityX, velocityY;
    float run_impulse, run_accel, jump_impulse, double_jump_fraction, jump_accel, stop_factor, sprint_factor,
          resistance_x, resistance_y;
    
public:
    ChimpMobile(const ChimpTile& til, SDL_Renderer* rend, const int positionX,
                const int positionY);
    ChimpMobile(const ChimpTile& til, SDL_Renderer* rend, const int positionX,
                const int positionY, const int tilX, const int tilY);

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
        
    bool isJumper() const { return jumper; }
    void setJumper(bool b) { jumper = b; }
    float getAccelerationY() const { return accelerationY; }
    void setAccelerationY(const float accel) { accelerationY = accel; }
    float getVelocityX() const { return velocityX; }
    void setVelocityX(const float velocity) { velocityX = velocity; }
    float getVelocityY() const { return velocityY; }
    void setVelocityY(const float velocity) { velocityY = velocity; }
    float getRunImpulse() const { return run_impulse; }
    void setRunImpulse(const float impulse);
    float getRunAccel() const { return run_accel; }
    void setRunAccel(const float accel) { run_accel = accel; }
    float getJumpImpulse() const { return jump_impulse; }
    void setJumpImpulse(const float impulse) { jump_impulse = impulse; }
    float getDoubleJumpFraction() const { return double_jump_fraction; }
    void setDoubleJumpFraction(const float fraction) { double_jump_fraction = fraction; }
    float getJumpAccel() const { return jump_accel; }
    void setJumpAccel(const float accel) { jump_accel = accel; }
    float getStopFactor() const { return stop_factor; }
    void setStopFactor(const float factor) { stop_factor = factor; }
    float getSprintFactor() const { return sprint_factor; }
    void setSprintFactor(const float factor) { sprint_factor = factor; }
    float getResistanceX() const { return resistance_x; }
    void setResistanceX(const float resistance) { resistance_x = resistance; }
    float getResistanceY() const { return resistance_y; }
    void setResistanceY(const float resistance);
    bool getScreenBoundLeft() const { return screenBoundLeft; }
    void setScreenBoundLeft(bool b) { screenBoundLeft = b; }
    bool getScreenBoundRight() const { return screenBoundRight; }
    void setScreenBoundRight(bool b) { screenBoundRight = b; }
    bool getScreenBoundTop() const { return screenBoundTop; }
    void setScreenBoundTop(bool b) { screenBoundTop = b; }
    bool getScreenBoundBottom() const { return screenBoundBottom; }
    void setScreenBoundBottom(bool b) { screenBoundBottom = b; }

    virtual void update(std::vector<std::unique_ptr<ChimpObject>>& objects);
};

#endif // CHIMPMOBILE_H



























