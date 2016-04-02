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

#include "ChimpGame.h"

namespace chimp
{

ChimpGame::ChimpGame(SDL_Renderer* rend, ChimpCharacter* plyr) : renderer(rend), player(plyr)
{
    screen.l = 0;
    screen.r = SCREEN_WIDTH;
    screen.t = 0;
    screen.b = SCREEN_HEIGHT;
    
    worldBox = screen;
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

void ChimpGame::pushObj(Layer lay, ChimpTile &til, const int x, const int y, const int tilesX, const int tilesY)
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

void ChimpGame::pushMob(Layer lay, ChimpTile &til, const int x, const int y, const int tilesX, const int tilesY)
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

void ChimpGame::pushChar(Layer lay, ChimpTile &til, const int x, const int y, const int tilesX, const int tilesY,
                         const int maxH, const Faction frnds, const Faction emns)
{
    TileVec tiles;
    tiles.push_back(til);
    switch(lay)
    {
    case BACK:
        background.push_back(std::unique_ptr<ChimpCharacter>(
                                 new ChimpCharacter(tiles, tiles, renderer, x, y, tilesX, tilesY, frnds, emns, maxH) ));
        break;
    case MID:
        middle.push_back(std::unique_ptr<ChimpCharacter>(
                                 new ChimpCharacter(tiles, tiles, renderer, x, y, tilesX, tilesY, frnds, emns, maxH) ));
        break;
    case FORE:
        foreground.push_back(std::unique_ptr<ChimpCharacter>(
                                 new ChimpCharacter(tiles, tiles, renderer, x, y, tilesX, tilesY, frnds, emns, maxH) ));
        break;
    }
}

void ChimpGame::update()
{
    IntBox mScreen = screen;
    IntBox mWorld = worldBox;
    
    for(auto& obj : background)
        (*obj).update(background, mScreen, mWorld);
    for(auto& obj : middle)
        (*obj).update(middle, mScreen, mWorld);
    player->update(middle, mScreen, mWorld);
    for(auto& obj : foreground)
        (*obj).update(foreground, mScreen, mWorld);
    
    if(player->getX() + player->getWidth() > screen.r - FOLLOW_ZONE_X && screen.r < worldBox.r)
        translateScreenX(player->getX() + player->getWidth() + FOLLOW_ZONE_X - screen.r);
    else if(player->getX() - screen.l < FOLLOW_ZONE_X && screen.l > worldBox.l)
        translateScreenX(player->getX() - FOLLOW_ZONE_X - screen.l);
    if(player->getY() - screen.t < FOLLOW_ZONE_Y && screen.t > worldBox.t)
        translateScreenY(player->getY() - FOLLOW_ZONE_Y - screen.t);
    else if(player->getY() + player->getHeight() > screen.b - FOLLOW_ZONE_Y && screen.b < worldBox.b)
        translateScreenY(player->getY() + player->getHeight() + FOLLOW_ZONE_Y - screen.b);
}

void ChimpGame::render()
{
    const IntBox* mScreen = &screen;
    
    for(auto& obj : background)
        (*obj).render( *mScreen );
    for(auto& obj : middle)
        (*obj).render(*mScreen);
    player->render(*mScreen);
    for(auto& obj : foreground)
        (*obj).render(*mScreen);
}






















} // namespace chimp
