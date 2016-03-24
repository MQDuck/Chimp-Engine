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

#include "ChimpObject.h"

ChimpObject::ChimpObject(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX,
                         const int positionY) : texture(tex), textureRect(texRect), renderer(rend)
{
    positionRect.w = textureRect.w;
    positionRect.h = textureRect.h;
    positionRect.x = positionX - (positionRect.w >> 1);
    positionRect.y = SCREEN_HEIGHT - positionY - positionRect.h;
}









