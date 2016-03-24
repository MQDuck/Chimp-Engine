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
#include "SDLUtils.h"
#include "cleanup.h"
#include "ChimpConstants.h"

using std::cout;
using std::endl;

class ChimpObject
{
private:
    SDL_Texture* texture;
    SDL_Rect textureRect;
    SDL_Renderer* renderer;
    SDL_Rect positionRect;
    
public:
    ChimpObject(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX, const int positionY);
    
    inline int getX() { return positionRect.x + (positionRect.w >> 1); }
    inline int getY() { return SCREEN_HEIGHT - positionRect.y - positionRect.h; }
    
    inline void render() { SDL_RenderCopy(renderer, texture, &textureRect, &positionRect); cout << "here i am" << endl; }
};

#endif // CHIMPOBJECT_H
