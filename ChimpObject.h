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

#ifndef CHIMPOBJECT_H
#define CHIMPOBJECT_H

#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>
#include "SDLUtils.h"
#include "cleanup.h"
#include "ChimpConstants.h"

using std::cout;
using std::endl;

class ChimpObject
{
protected:
    SDL_Texture* texture;
    SDL_Rect textureRect;
    SDL_Renderer* renderer;
    SDL_Rect positionRect;
    const int width, height;
    float approx_zero_float, approx_zero_y;
    
public:
    ChimpObject(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX, const int positionY);
    ChimpObject(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX, const int positionY,
                const int tilesX, const int tilesY);
    
    inline int getX() { return positionRect.x + (positionRect.w >> 1); }
    inline int getY() { return SCREEN_HEIGHT - positionRect.y - positionRect.h; }
    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
    inline int getPosRectX() { return positionRect.x; }
    inline int getPosRectY() { return positionRect.y; }
    inline int getPosRectW() { return positionRect.w; }
    inline int getPosRectH() { return positionRect.h; }
    
    bool touches(const ChimpObject& other);
    bool touchesAtBottom(const ChimpObject& other);
    
    void render();
    
    float getApproxZeroFloat() { return approx_zero_float; }
    float getApproxZeroY() { return approx_zero_y; }
    
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    virtual bool isJumper() { return false; }
    virtual void setJumper(bool b) {}
    virtual float getAccelerationY() { return 0; }
    virtual void setAccelerationY(const float accel) {}
    virtual float getVelocityX() { return 0; }
    virtual void setVelocityX(const float velocity) {}
    virtual float getVelocityY() { return 0; }
    virtual void setVelocityY(const float velocity) {}
    virtual void update(std::vector<std::unique_ptr<ChimpObject>>& objects) {}
    virtual void runRight() {}
    virtual void runLeft() {}
    virtual float getRunImpulse() { return 0; }
    virtual void setRunImpulse(const float impulse) {}
    virtual float getRunAccel() { return 0; }
    virtual void setRunAccel(const float accel) {}
    virtual float getJumpImpulse() { return 0; }
    virtual void setJumpImpulse(const float impulse) {}
    virtual float getDoubleJumpFraction() { return 0; }
    virtual void setDoubleJumpFraction(const float fraction) {}
    virtual float getJumpAccel() { return 0; }
    virtual void setJumpAccel(const float accel) {}
    virtual float getStopFactor() { return 0; }
    virtual void setStopFactor(const float factor) {}
    virtual float getSprintFactor() { return 0; }
    virtual void setSprintFactor(const float factor) {}
    virtual float getResistanceX() { return 0; }
    virtual void setResistanceX(const float resistance) {}
    virtual float getResistanceY() { return 0; }
    virtual void setResistanceY(const float resistance) {}
    #pragma GCC diagnostic pop
    
protected:
    inline bool approxZeroF(const float f) { return f > -approx_zero_float && f < approx_zero_float; }
    inline bool approxZeroI(const int i) { return i > -approx_zero_y && i < approx_zero_y; }
};

#endif // CHIMPOBJECT_H















