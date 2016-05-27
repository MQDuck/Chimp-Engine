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

namespace chimp
{

ChimpGame::ChimpGame(SDL_Renderer* rend, const unsigned int winWidth, const unsigned int winHeight,
                     ChimpCharacter* plyr)
    : renderer(rend), player(plyr), windowWidth(winWidth), windowHeight(winHeight) {}

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

bool ChimpGame::setRenderer(SDL_Renderer* rend)
{
    if(rend == nullptr)
        return false;
    renderer = rend;
    return true;
}

void ChimpGame::pushObj(const Layer layr, const ChimpTile &til, const int x, const int y, const int tilesX,
                        const int tilesY)
{
    switch(layr)
    {
    case BACK:
        background.push_back(std::unique_ptr<ChimpObject>( new ChimpObject(til, renderer, x, y, tilesX, tilesY) ));
        return;
    case MID:
        middle.push_back(std::unique_ptr<ChimpObject>( new ChimpObject(til, renderer, x, y, tilesX, tilesY) ));
        return;
    case FORE:
        foreground.push_back(std::unique_ptr<ChimpObject>( new ChimpObject(til, renderer, x, y, tilesX, tilesY) ));
    }
}

void ChimpGame::pushMob(const Layer layr, const ChimpTile &til, const int x, const int y, const int tilesX,
                        const int tilesY)
{
    switch(layr)
    {
    case BACK:
        background.push_back(std::unique_ptr<ChimpMobile>( new ChimpMobile(til, renderer, x, y, tilesX, tilesY) ));
        return;
    case MID:
        middle.push_back(std::unique_ptr<ChimpMobile>( new ChimpMobile(til, renderer, x, y, tilesX, tilesY) ));
        return;
    case FORE:
        foreground.push_back(std::unique_ptr<ChimpMobile>( new ChimpMobile(til, renderer, x, y, tilesX, tilesY) ));
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
            new ChimpCharacter(tilRn, tilJmp, tilIdl, renderer, x, y, tilesX, tilesY, frnds, enms, maxH) ));
        break;
    case MID:
        middle.push_back(std::unique_ptr<ChimpCharacter>(
            new ChimpCharacter(tilRn, tilJmp, tilIdl, renderer, x, y, tilesX, tilesY, frnds, enms, maxH) ));
        break;
    case FORE:
        foreground.push_back(std::unique_ptr<ChimpCharacter>(
            new ChimpCharacter(tilRn, tilJmp, tilIdl, renderer, x, y, tilesX, tilesY, frnds, enms, maxH) ));
        break;
    }
}

void ChimpGame::pushChar(const Layer lay, const ChimpTile &til, const int x, const int y, const int tilesX,
                         const int tilesY, const int maxH, const Faction frnds, const Faction enms)
{
    TileVec tVec = {til};
    pushChar(lay, tVec, tVec, tVec, x, y, tilesX, tilesY, maxH, frnds, enms);
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
        obj->initialize(midWindow);
    for(auto& obj : middle)
        obj->initialize(midWindow);
    for(auto& obj : foreground)
        obj->initialize(midWindow);
    
    player->initialize(midWindow);
}

void ChimpGame::update(const Uint32 time)
{
    for(auto& obj : background)
        obj->update(background, midWindow, worldBox, time);
    for(auto& obj : middle)
        obj->update(middle, midWindow, worldBox, time);
    player->update(middle, midWindow, worldBox, time);
    for(auto& obj : foreground)
        obj->update(foreground, midWindow, worldBox, time);
    
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
