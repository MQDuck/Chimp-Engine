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
#include "ChimpTile.h"

using std::cout;
using std::endl;

class ChimpObject
{
protected:
    //SDL_Texture* texture;
    SDL_Rect /*textureRect,*/ positionRect/*, collisionRect*/;
    ChimpTile texture;
    SDL_Renderer* renderer;
    const int width, height;
    float approx_zero_float, approx_zero_y;
    SDL_RendererFlip flip;
    
public:
    ChimpObject(const ChimpTile& tex, SDL_Renderer* rend, const int positionX,
                const int positionY);
    ChimpObject(const ChimpTile& tex, SDL_Renderer* rend, const int positionX,
                const int positionY, const int tilesX, const int tilesY);
    
    inline int getX() const { return positionRect.x + (positionRect.w >> 1); }
    inline int getY() const { return SCREEN_HEIGHT - positionRect.y - positionRect.h; }
    inline int getWidth() const { return width; }
    inline int getHeight() const { return height; }
    inline int getPosRectX() const { return positionRect.x; }
    inline int getPosRectY() const { return positionRect.y; }
    inline int getPosRectW() const { return positionRect.w; }
    inline int getPosRectH() const { return positionRect.h; }
    inline int collisionLeft() const { return positionRect.x + texture.collisionRect.x; }
    inline int collisionRight() const { return positionRect.x + width - texture.collisionRect.w; }
    inline int collisionTop() const { return positionRect.y + texture.collisionRect.y; }
    inline int collisionBottom() const {return positionRect.y + height - texture.collisionRect.h; }
    /*inline int getCollisionSizeLeft() const { return collisionRect.x; }
    inline int getCollisionSizeRight() const { return collisionRect.w; }
    inline int getCollisionSizeTop() const { return collisionRect.y; }
    inline int getCollisionSizeBottom() const { return collisionRect.h; }*/
    
    bool touches(const ChimpObject& other) const;
    bool touchesAtBottom(const ChimpObject& other) const;
    
    void render();
    
    float getApproxZeroFloat() { return approx_zero_float; }
    float getApproxZeroY() { return approx_zero_y; }
    
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    virtual bool isJumper() const { return false; }
    virtual void setJumper(bool b) {}
    virtual float getAccelerationY() const { return 0; }
    virtual void setAccelerationY(const float accel) {}
    virtual float getVelocityX() const { return 0; }
    virtual void setVelocityX(const float velocity) {}
    virtual float getVelocityY() const { return 0; }
    virtual void setVelocityY(const float velocity) {}
    virtual void update(std::vector<std::unique_ptr<ChimpObject>>& objects) {}
    virtual void runRight() {}
    virtual void runLeft() {}
    virtual float getRunImpulse() const { return 0; }
    virtual void setRunImpulse(const float impulse) {}
    virtual float getRunAccel() const { return 0; }
    virtual void setRunAccel(const float accel) {}
    virtual float getJumpImpulse() const { return 0; }
    virtual void setJumpImpulse(const float impulse) {}
    virtual float getDoubleJumpFraction() const { return 0; }
    virtual void setDoubleJumpFraction(const float fraction) {}
    virtual float getJumpAccel() const { return 0; }
    virtual void setJumpAccel(const float accel) {}
    virtual float getStopFactor() const { return 0; }
    virtual void setStopFactor(const float factor) {}
    virtual float getSprintFactor() const { return 0; }
    virtual void setSprintFactor(const float factor) {}
    virtual float getResistanceX() const { return 0; }
    virtual void setResistanceX(const float resistance) {}
    virtual float getResistanceY() const { return 0; }
    virtual void setResistanceY(const float resistance) {}
    #pragma GCC diagnostic pop
    
protected:
    inline bool approxZeroF(const float f) const { return f > -approx_zero_float && f < approx_zero_float; }
    inline bool approxZeroI(const int i) const { return i > -approx_zero_y && i < approx_zero_y; }
};

#endif // CHIMPOBJECT_H















