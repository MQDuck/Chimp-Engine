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

ChimpGame::ChimpGame(SDL_Renderer* rend, ChimpCharacter* plyr) : renderer(rend), player(plyr) {}

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

void ChimpGame::pushObj(const Layer lay, const ChimpTile &til, const int x, const int y, const int tilesX,
                        const int tilesY)
{
    switch(lay)
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

void ChimpGame::pushMob(const Layer lay, const ChimpTile &til, const int x, const int y, const int tilesX,
                        const int tilesY)
{
    switch(lay)
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
    midWindow.r = SCREEN_WIDTH;
    midWindow.t = 0;
    midWindow.b = SCREEN_HEIGHT;
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

void ChimpGame::update()
{
    IntBox mScreen = midWindow;
    IntBox mWorld = worldBox;
    
    for(auto& obj : background)
        obj->update(background, mScreen, mWorld);
    for(auto& obj : middle)
        obj->update(middle, mScreen, mWorld);
    player->update(middle, mScreen, mWorld);
    for(auto& obj : foreground)
        obj->update(foreground, mScreen, mWorld);
    
    if(player->getX() + player->getWidth() > midWindow.r - FOLLOW_ZONE_X && midWindow.r < worldBox.r)
        translateScreenX(player->getX() + player->getWidth() + FOLLOW_ZONE_X - midWindow.r);
    else if(player->getX() - midWindow.l < FOLLOW_ZONE_X && midWindow.l > worldBox.l)
        translateScreenX(player->getX() - FOLLOW_ZONE_X - midWindow.l);
    if(player->getY() - midWindow.t < FOLLOW_ZONE_Y && midWindow.t > worldBox.t)
        translateScreenY(player->getY() - FOLLOW_ZONE_Y - midWindow.t);
    else if(player->getY() + player->getHeight() > midWindow.b - FOLLOW_ZONE_Y && midWindow.b < worldBox.b)
        translateScreenY(player->getY() + player->getHeight() + FOLLOW_ZONE_Y - midWindow.b);
}

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
