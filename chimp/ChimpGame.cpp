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
    along with Chimp Out!.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChimpGame.h"
#include "ChimpLuaInterface.h"

namespace chimp
{

ChimpGame* ChimpGame::self;
ChimpObject* ChimpGame::currentObj;

ChimpGame::ChimpGame(SDL_Renderer* const rend, const unsigned int winWidth, const unsigned int winHeight,
                     ChimpCharacter* plyr)
    : renderer(rend), player(plyr), windowWidth(winWidth), windowHeight(winHeight)
{
    scroll_factor_back = 1.0;
    scroll_factor_fore = 1.0;
    luast = luaL_newstate();
    setupLua(luast);
    self = this;
}

ChimpObject& ChimpGame::getObj(Layer lay, size_t in)
{
    switch(lay)
    {
    case BACK:
        return *background[in];
    case FORE:
        return *foreground[in];
    case MID:
    default:
        return *middle[in];
    }
}

ChimpObject& ChimpGame::getObjBack(Layer lay)
{
    switch(lay)
    {
    case BACK:
        return *background.back();
    case FORE:
        return *foreground.back();
    case MID:
    default:
        return *middle.back();
    }
}

bool ChimpGame::setWorldBox(const int l, const int r, const int t, const int b)
{
    if(l >= r)
        return false;
    if(t >= b)
        return false;
    
    worldBox.l = l;
    worldBox.r = r;
    worldBox.t = t;
    worldBox.b = b;
    
    return true;
}

bool ChimpGame::setRenderer(SDL_Renderer* const rend)
{
   if(rend)
    {
        renderer = rend;
        return true;
    }
    return false;
}

float ChimpGame::getScrollFactor(const Layer lay) const
{
    switch(lay)
    {
    case BACK:
        return scroll_factor_back;
    case MID:
        return 1.0;
    case FORE:
        return scroll_factor_fore;
    default:
        return 0.0;
    }
}

bool ChimpGame::setScrollFactor(const Layer lay, const float factor)
{
    switch(lay)
    {
    case BACK:
        scroll_factor_back = factor;
        return true;
    case FORE:
        scroll_factor_fore = factor;
        return true;
    default:
        return false;
    }
}

void ChimpGame::pushObj(const Layer layr, const ChimpTile& til, const int x, const int y, const int tilesX,
                        const int tilesY)
{
    switch(layr)
    {
    case BACK:
        background.push_back(ObjectPointer( new ChimpObject(renderer, til, x, y, tilesX, tilesY) ));
        return;
    case MID:
        middle.push_back(ObjectPointer( new ChimpObject(renderer, til, x, y, tilesX, tilesY) ));
        return;
    case FORE:
        foreground.push_back(ObjectPointer( new ChimpObject(renderer, til, x, y, tilesX, tilesY) ));
    }
}

void ChimpGame::pushMob(const Layer layr, const ChimpTile &til, const int x, const int y, const int tilesX,
                        const int tilesY)
{
    switch(layr)
    {
    case BACK:
        background.push_back(std::unique_ptr<ChimpMobile>( new ChimpMobile(renderer, til, x, y, tilesX, tilesY) ));
        return;
    case MID:
        middle.push_back(std::unique_ptr<ChimpMobile>( new ChimpMobile(renderer, til, x, y, tilesX, tilesY) ));
        return;
    case FORE:
        foreground.push_back(std::unique_ptr<ChimpMobile>( new ChimpMobile(renderer, til, x, y, tilesX, tilesY) ));
    }
}

void ChimpGame::pushChar(const Layer lay, const TileVec &tilRn, const TileVec &tilJmp, TileVec &tilIdl, const int x,
                         const int y, const int tilesX, const int tilesY, const int maxH, const Faction frnds,
                         const Faction enms)
{
    switch(lay)
    {
    case BACK:
        background.push_back(std::unique_ptr<ChimpCharacter>(
            new ChimpCharacter(renderer, tilRn, tilJmp, tilIdl, x, y, tilesX, tilesY, frnds, enms, maxH) ));
        break;
    case MID:
        middle.push_back(std::unique_ptr<ChimpCharacter>(
            new ChimpCharacter(renderer, tilRn, tilJmp, tilIdl, x, y, tilesX, tilesY, frnds, enms, maxH) ));
        break;
    case FORE:
        foreground.push_back(std::unique_ptr<ChimpCharacter>(
            new ChimpCharacter(renderer, tilRn, tilJmp, tilIdl, x, y, tilesX, tilesY, frnds, enms, maxH) ));
        break;
    }
}

void ChimpGame::pushChar(const Layer lay, const ChimpTile &til, const int x, const int y, const int tilesX,
                         const int tilesY, const int maxH, const Faction frnds, const Faction enms)
{
    TileVec tVec = {til};
    pushChar(lay, tVec, tVec, tVec, x, y, tilesX, tilesY, maxH, frnds, enms);
}

void ChimpGame::translateWindowX(const int x)
{
    if(x == 0)
        return;
    
    midWindow.l += x;
    midWindow.r += x;
    
    if(midWindow.l < worldBox.l)
    {
        midWindow.r += worldBox.l - midWindow.l;
        midWindow.l = worldBox.l;
    }
    else if(midWindow.r > worldBox.r)
    {
        midWindow.l += worldBox.r - midWindow.r;
        midWindow.r = worldBox.r;
    }
    
    backWindow.l = midWindow.l * scroll_factor_back;
    backWindow.r = midWindow.r * scroll_factor_back;
    foreWindow.l = midWindow.l * scroll_factor_fore;
    foreWindow.r = midWindow.r * scroll_factor_fore;
}

void ChimpGame::translateWindowY(const int y)
{
    if(y == 0)
        return;
    
    midWindow.t += y;
    midWindow.b += y;
    
    if(midWindow.t < worldBox.t)
    {
        midWindow.b += worldBox.t - midWindow.t;
        midWindow.t = worldBox.t;
    }
    else if(midWindow.b > worldBox.b)
    {
        midWindow.t += worldBox.b - midWindow.b;
        midWindow.b = worldBox.b;
    }
    
    backWindow.t = midWindow.t * scroll_factor_back;
    backWindow.b = midWindow.b * scroll_factor_back;
    foreWindow.t = midWindow.t * scroll_factor_fore;
    foreWindow.b = midWindow.b * scroll_factor_fore;
}

void ChimpGame::initialize()
{
    midWindow.l = 0;
    midWindow.r = windowWidth;
    midWindow.t = 0;
    midWindow.b = windowHeight;
    backWindow = midWindow;
    foreWindow = midWindow;
    
    for(auto& obj : background)
        obj->initialize(*this);
    for(auto& obj : middle)
        obj->initialize(*this);
    for(auto& obj : foreground)
        obj->initialize(*this);
    
    player->initialize(*this);
}

void ChimpGame::update(const Uint32 time)
{
    for(auto& obj : background)
        obj->update(background, *this, time);
    for(auto& obj : middle)
        obj->update(middle, *this, time);
    player->update(middle, *this, time);
    for(auto& obj : foreground)
        obj->update(foreground, *this, time);
    
    for(auto& obj : background)
        obj->accelerate();
    for(auto& obj : middle)
        obj->accelerate();
    player->accelerate();
    for(auto& obj : foreground)
        obj->accelerate();
    
    /*SDL_Thread* threadBack = SDL_CreateThread(updateThreadBack, "back update thread", this);
    SDL_Thread* threadMid  = SDL_CreateThread(updateThreadMid, "mid update thread",  this);
    SDL_Thread* threadFore = SDL_CreateThread(updateThreadFore, "fore update thread", this);
    SDL_WaitThread(threadBack, nullptr);
    SDL_WaitThread(threadMid,  nullptr);
    SDL_WaitThread(threadFore, nullptr);
    player->update(middle, midWindow, worldBox);*/
    
    if(player->getX() + player->getWidth() > midWindow.r - FOLLOW_ZONE_X && midWindow.r < worldBox.r)
        translateWindowX(player->getX() + player->getWidth() + FOLLOW_ZONE_X - midWindow.r);
    else if(player->getX() - midWindow.l < FOLLOW_ZONE_X && midWindow.l > worldBox.l)
        translateWindowX(player->getX() - FOLLOW_ZONE_X - midWindow.l);
    if(player->getY() - midWindow.t < FOLLOW_ZONE_Y && midWindow.t > worldBox.t)
        translateWindowY(player->getY() - FOLLOW_ZONE_Y - midWindow.t);
    else if(player->getY() + player->getHeight() > midWindow.b - FOLLOW_ZONE_Y && midWindow.b < worldBox.b)
        translateWindowY(player->getY() + player->getHeight() + FOLLOW_ZONE_Y - midWindow.b);
}

/*void ChimpGame::updateBack()
{
    for(auto& obj : background)
        obj->update(background, midWindow, worldBox);
}

void ChimpGame::updateMid()
{
    for(auto& obj : middle)
        obj->update(middle, midWindow, worldBox);
}

void ChimpGame::updateFore()
{
    for(auto& obj : foreground)
        obj->update(foreground, midWindow, worldBox);
}

int ChimpGame::updateThreadBack(void* game)
{
    ((ChimpGame*)game)->updateBack();
    return 0;
}

int ChimpGame::updateThreadMid(void* game)
{
    ((ChimpGame*)game)->updateMid();
    return 0;
}

int ChimpGame::updateThreadFore(void* game)
{
    ((ChimpGame*)game)->updateFore();
    return 0;
}*/

void ChimpGame::render()
{
    for(auto& obj : background)
        obj->render(backWindow);
    for(auto& obj : middle)
        obj->render(midWindow);
    player->render(midWindow);
    for(auto& obj : foreground)
        obj->render(foreWindow);
}

void ChimpGame::reset()
{
    for(auto& obj : background)
        obj->reset();
    for(auto& obj : middle)
        obj->reset();
    player->reset();
    for(auto& obj : foreground)
        obj->reset();
    
    initialize();
}






















} // namespace chimp
