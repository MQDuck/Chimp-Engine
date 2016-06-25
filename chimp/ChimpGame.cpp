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
#include <SDL2/SDL_image.h>
#include <iostream>
#include "ChimpLuaInterface.h"

namespace chimp
{

ChimpGame* ChimpGame::self;
ChimpObject* ChimpGame::currentObj;
ChimpCharacter* ChimpGame::player;

ChimpGame::ChimpGame(SDL_Renderer* const rend, const unsigned int winWidth, const unsigned int winHeight,
                     ChimpCharacter* plyr)
    : renderer(rend), windowWidth(winWidth), windowHeight(winHeight)
{
    player = plyr;
    scroll_factor_back = 1.0;
    scroll_factor_fore = 1.0;
    activeZone = ACTIVE_ZONE;
    inactiveZone = INACTIVE_ZONE;
    luast = luaL_newstate();
    setupLua(luast);
    self = this;
    music = nullptr;
}

ChimpGame::~ChimpGame()
{
    if(player)
        delete player;
    for(auto& tex : textures)
        SDL_DestroyTexture(tex.second);
    for(auto& snd : sounds)
        Mix_FreeChunk(snd.second);
    for(auto& mus : musics)
        Mix_FreeMusic(mus.second);
}

ChimpObject& ChimpGame::getObj(Layer lay, size_t index)
{
    switch(lay)
    {
    case BACK:
        return *background[index];
    case FORE:
        return *foreground[index];
    case MID:
    default:
        return *middle[index];
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

bool ChimpGame::setActiveZone(const int zone)
{
    if(zone < 0)
        return false;
    activeZone = zone;
    return true;
}

bool ChimpGame::setInactiveZone(const int zone)
{
    if(zone < 0)
        return false;
    inactiveZone = zone;
    return true;
}

bool ChimpGame::setMusic(const std::string& mus)
{
    if(mus == "")
    {
        music = nullptr;
        return true;
    }
    else if(musics.find(mus) != musics.end())
    {
        music = musics[mus];
        return true;
    }
    return false;
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
    
    if(music)
        Mix_PlayMusic(music, -1);
}

void ChimpGame::update(const Uint32 time)
{
    static Uint32 accelTime = 0;
    
    for(auto& obj : background)
        obj->update(background, *this, time);
    for(auto& obj : middle)
        obj->update(middle, *this, time);
    player->update(middle, *this, time);
    for(auto& obj : foreground)
        obj->update(foreground, *this, time);
    
    accelTime += time;
    if(accelTime >= MS_PER_ACCEL)
    {
        accelTime -= MS_PER_ACCEL;
        for(auto& obj : background)
            obj->accelerate();
        for(auto& obj : middle)
            obj->accelerate();
        player->accelerate();
        for(auto& obj : foreground)
            obj->accelerate();
    }
    
    if(player->getX() + player->getWidth() > midWindow.r - FOLLOW_ZONE_X && midWindow.r < worldBox.r)
        translateWindowX(player->getX() + player->getWidth() + FOLLOW_ZONE_X - midWindow.r);
    else if(player->getX() - midWindow.l < FOLLOW_ZONE_X && midWindow.l > worldBox.l)
        translateWindowX(player->getX() - FOLLOW_ZONE_X - midWindow.l);
    if(player->getY() - midWindow.t < FOLLOW_ZONE_Y && midWindow.t > worldBox.t)
        translateWindowY(player->getY() - FOLLOW_ZONE_Y - midWindow.t);
    else if(player->getY() + player->getHeight() > midWindow.b - FOLLOW_ZONE_Y && midWindow.b < worldBox.b)
        translateWindowY(player->getY() + player->getHeight() + FOLLOW_ZONE_Y - midWindow.b);
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

tinyxml2::XMLError ChimpGame::loadLevel(const std::string& levelFile)
{
    tinyxml2::XMLDocument levelXML;
    tinyxml2::XMLError loadFileResult;
    tinyxml2::XMLNode* level;
    tinyxml2::XMLElement* objXML;
    tinyxml2::XMLElement* tag;
    
    loadFileResult = levelXML.LoadFile(levelFile.c_str());
    if(loadFileResult != tinyxml2::XML_SUCCESS)
        return loadFileResult;
    level = levelXML.FirstChildElement("chimplevel");
    if(!level)
        return tinyxml2::XML_ERROR_FILE_READ_ERROR;
    
    if(   !loadTextures(levelXML, textures, renderer)
       || !loadTiles(levelXML, textures, tiles)
       || !loadSounds(levelXML, sounds, musics) )
        return tinyxml2::XML_NO_TEXT_NODE;
    
    loadWorldBox(level->FirstChildElement("edges"));
    if( (tag = level->FirstChildElement("scrollfactor")) )
    {
        float factor;
        if(tag->QueryFloatAttribute("background", &factor) == tinyxml2::XML_SUCCESS)
            setScrollFactor(BACK, factor);
        if(tag->QueryFloatAttribute("foreground", &factor) == tinyxml2::XML_SUCCESS)
            setScrollFactor(FORE, factor);
    }
    if( (tag = level->FirstChildElement("music")) )
    {
        std::string name;
        if(getString(tag->GetText(), name))
            setMusic(name);
    }
    if( (tag = level->FirstChildElement("activezone")) )
    {
        int zone;
        if(tag->QueryIntText(&zone) == tinyxml2::XML_SUCCESS)
            setActiveZone(zone);
    }
    if( (tag = level->FirstChildElement("inactivezone")) )
    {
        int zone;
        if(tag->QueryIntText(&zone) == tinyxml2::XML_SUCCESS)
            setInactiveZone(zone);
    }
    
    for( objXML = level->FirstChildElement("object"); objXML; objXML = objXML->NextSiblingElement("object") )
    {
        std::string type;
        if(getString(objXML->Attribute("type"), type))
        {
            if(type == "player")
            {
                TileVec runtiles, jumptiles, idletiles;
                if(loadAllAnimations(objXML, idletiles, runtiles, jumptiles, tiles))
                {
                    player = new ChimpCharacter(renderer, runtiles, jumptiles, idletiles);
                    loadObject(objXML, *player);
                }
            }
            else if(type == "character")
            {
                TileVec runtiles, jumptiles, idletiles;
                std::string tile;
                if(loadAllAnimations(objXML, idletiles, runtiles, jumptiles, tiles))
                {
                    Layer layer = getLayer(objXML);
                    pushChar(layer, runtiles, jumptiles, idletiles);
                    loadObject(objXML, getObjBack(layer));
                }
                else if(getString(objXML->FirstChildElement("tile")->GetText(), tile))
                {
                    Layer layer = getLayer(objXML);
                    pushChar(layer, tiles[tile]);
                    loadObject(objXML, getObjBack(layer));
                }
            }
            else if(type == "object")
            {
                std::string tile;
                if(getString(objXML->FirstChildElement("tile")->GetText(), tile))
                {
                    Layer layer = getLayer(objXML);
                    pushObj(layer, tiles[tile]);
                    loadObject(objXML, getObjBack(layer));
                }   
            }
        }
    }
    
    return tinyxml2::XML_SUCCESS;
}

Layer ChimpGame::getLayer(const tinyxml2::XMLElement *objXML)
{
    std::string layer;
    if(getString(objXML->Attribute("layer"), layer))
    {
        if(layer == "background")
            return BACK;
        else if(layer == "foreground")
            return FORE;
    }
    return MID;
}

bool ChimpGame::getBool(const char* const boolStr, bool& result)
{
    if(!boolStr)
        return false;
    if(strcmp(boolStr, "true") == 0)
    {
        result = true;
        return true;
    }
    if(strcmp(boolStr, "false") == 0)
    {
        result = false;
        return true;
    }
    return false;
}

bool ChimpGame::getString(const char* const cStr, std::string& str)
{
    if(cStr)
    {
        str = cStr;
        return true;
    }
    return false;
}

std::string ChimpGame::getMode(const tinyxml2::XMLElement* const tag)
{
    std::string mode;
    return getString(tag->Attribute("mode"), mode) ? mode : "absolute";
}

void ChimpGame::loadWorldBox(const tinyxml2::XMLElement* const edges)
{
    int wbLeft = 0;
    int wbRight = SCREEN_WIDTH;
    int wbTop = 0;
    int wbBottom = SCREEN_HEIGHT;
    if(edges)
    {
        int val;
        if(edges->QueryIntAttribute("left", &val) == tinyxml2::XML_SUCCESS)
            wbLeft = val;
        if(edges->QueryIntAttribute("right", &val) == tinyxml2::XML_SUCCESS)
            wbRight = val;
        if(edges->QueryIntAttribute("top", &val) == tinyxml2::XML_SUCCESS)
            wbTop = val;
        if(edges->QueryIntAttribute("bottom", &val) == tinyxml2::XML_SUCCESS)
            wbBottom = val;
    }
    setWorldBox(wbLeft, wbRight, wbTop, wbBottom);
}

bool ChimpGame::loadAllAnimations(tinyxml2::XMLElement* const objXML, TileVec& idletiles, TileVec& runtiles,
                                  TileVec& jumptiles, TileMap& tiles)
{
    loadAnimation(objXML, "idle", idletiles, tiles);
    if(idletiles.empty())
        return false;
    loadAnimation(objXML, "run", runtiles, tiles);
    if(runtiles.empty())
        runtiles = idletiles;
    loadAnimation(objXML, "jump", jumptiles, tiles);
    if(jumptiles.empty())
        jumptiles = idletiles;
    return true;
}

void ChimpGame::loadAnimation(tinyxml2::XMLElement* const objXML, std::string anim, TileVec& tilvec, TileMap& tiles)
{
    std::string animation;
    for( tinyxml2::XMLElement* tag = objXML->FirstChildElement("tile"); tag; tag = tag->NextSiblingElement("tile") )
        if(getString(tag->Attribute("animation"), animation) && anim == animation)
            tilvec.push_back( tiles[tag->GetText()] );
}

void ChimpGame::loadObject(tinyxml2::XMLElement* const objXML, ChimpObject& obj)
{
    tinyxml2::XMLElement* tag;
    
    if( (tag = objXML->FirstChildElement("position")) )
    {
        int pos;
        if(tag->QueryIntAttribute("x", &pos) == tinyxml2::XML_SUCCESS)
            obj.setInitialX(pos);
        if(tag->QueryIntAttribute("y", &pos) == tinyxml2::XML_SUCCESS)
            obj.setInitialY(SCREEN_HEIGHT - pos - obj.getHeight());
    }
    if( (tag = objXML->FirstChildElement("tiles")) )
    {
        int tiles;
        if(tag->QueryIntAttribute("x", &tiles) == tinyxml2::XML_SUCCESS)
            obj.setTilesX(tiles);
        if(tag->QueryIntAttribute("y", &tiles) == tinyxml2::XML_SUCCESS)
            obj.setTilesY(tiles);
    }
    if( (tag = objXML->FirstChildElement("maxhealth")) )
    {
        int health;
        if(tag->QueryIntText(&health) == tinyxml2::XML_SUCCESS)
        {
            obj.setMaxHealth(health);
        }
    }
    if( (tag = objXML->FirstChildElement("respawn")) )
    {
        bool respawn;
        if(getBool(tag->GetText(), respawn))
            obj.setRespawn(respawn);
    }
    if( (tag = objXML->FirstChildElement("damage")) )
    {
        bool tf;
        if(getBool(tag->Attribute("left"), tf))
            obj.setDamageLeft(tf);
        if(getBool(tag->Attribute("right"), tf))
            obj.setDamageRight(tf);
        if(getBool(tag->Attribute("top"), tf))
            obj.setDamageTop(tf);
        if(getBool(tag->Attribute("bottom"), tf))
            obj.setDamageBottom(tf);
    }
    if( (tag = objXML->FirstChildElement("bounded")) )
    {
        bool tf;
        if(getBool(tag->Attribute("left"), tf))
            obj.setBoundLeft(tf);
        if(getBool(tag->Attribute("right"), tf))
            obj.setBoundRight(tf);
        if(getBool(tag->Attribute("top"), tf))
            obj.setBoundTop(tf);
        if(getBool(tag->Attribute("bottom"), tf))
            obj.setBoundBottom(tf);
    }
    if( (tag = objXML->FirstChildElement("stopfactor")) )
    {
        float factor;
        std::string mode;
        if(tag->QueryFloatText(&factor) == tinyxml2::XML_SUCCESS)
        {
            mode = getMode(tag);
            if(mode == "absolute")
                obj.setStopFactor(factor);
            else if(mode == "scale")
                obj.setStopFactor(obj.getStopFactor() * factor);
        }
    }
    if( (tag = objXML->FirstChildElement("sprintfactor")) )
    {
        float factor;
        if(tag->QueryFloatText(&factor) == tinyxml2::XML_SUCCESS)
            obj.setSprintFactor(factor);
    }
    if( (tag = objXML->FirstChildElement("maxjumps")) )
    {
        int max;
        if(tag->QueryIntText(&max) == tinyxml2::XML_SUCCESS)
            obj.setMaxJumps(max);
    }
    
    for(tag = objXML->FirstChildElement("faction"); tag; tag = tag->NextSiblingElement("faction"))
    {
        std::string type, factionStr;
        if(getString(tag->Attribute("type"), type) && getString(tag->GetText(), factionStr))
        {
            Faction faction;
            if(factionStr == "player")
                faction = FACTION_PLAYER;
            else if(factionStr == "baddies")
                faction = FACTION_BADDIES;
            else
                continue;
            
            if(type == "friend")
                obj.addFriend(faction);
            else if(type == "enemy")
                obj.addEnemy(faction);
        }
    }
    for(tag = objXML->FirstChildElement("acceleration"); tag; tag = tag->NextSiblingElement("acceleration"))
    {
        float accel;
        std::string type, mode;
        if(tag->QueryFloatText(&accel) == tinyxml2::XML_SUCCESS && getString(tag->Attribute("type"), type))
        {
            mode = getMode(tag);
            if(type == "run")
            {
                if(mode == "absolute")
                    obj.setRunAccel(accel);
                else if(mode == "scale")
                    obj.setRunAccel(obj.getRunAccel() * accel);
            }
            else if(type == "jump")
            {
                if(mode == "absolute")
                    obj.setJumpAccel(accel);
                else if(mode == "scale")
                    obj.setJumpAccel(obj.getJumpAccel() * accel);
            }
        }
    }
    for(tag = objXML->FirstChildElement("impulse"); tag; tag = tag->NextSiblingElement("impulse"))
    {
        float impulse;
        std::string type, mode;
        if(tag->QueryFloatText(&impulse) == tinyxml2::XML_SUCCESS && getString(tag->Attribute("type"), type))
        {
            mode = getMode(tag);
            if(type == "run")
            {
                if(mode == "absolute")
                    obj.setRunImpulse(impulse);
                else if(mode == "scale")
                    obj.setRunImpulse(obj.getRunImpulse() * impulse);
            }
            else if(type == "jump")
            {
                if(mode == "absolute")
                    obj.setJumpImpulse(impulse);
                else if(mode == "scale")
                    obj.setJumpImpulse(obj.getRunImpulse() * impulse);
            }
            else if(type == "multijump")
            {
                if(mode == "absolute")
                    obj.setMultiJumpImpulse(impulse);
                else if(mode == "scale")
                    obj.setMultiJumpImpulse(obj.getMultiJumpImpulse() * impulse);
            }
        }
    }
    for(tag = objXML->FirstChildElement("resistance"); tag; tag = tag->NextSiblingElement("resistance"))
    {
        float resistance;
        std::string type, mode;
        if(tag->QueryFloatText(&resistance) == tinyxml2::XML_SUCCESS && getString(tag->Attribute("type"), type))
        {
            mode = getMode(tag);
            if(type == "run")
            {
                if(mode == "absolute")
                    obj.setResistanceX(resistance);
                else if(mode == "scale")
                    obj.setResistanceX(obj.getResistanceX() * resistance);
            }
            else if(type == "jump")
            {
                if(mode == "absolute")
                    obj.setResistanceY(resistance);
                else if(mode == "scale")
                    obj.setResistanceY(obj.getResistanceY() * resistance);
            }
        }
    }
    for(tag = objXML->FirstChildElement("script"); tag; tag = tag->NextSiblingElement("script"))
    {
        std::string type, script;
        if(getString(tag->Attribute("type"), type) && getString(tag->GetText(), script))
        {
            if(type == "behavior")
                obj.setScriptBehavior(script);
            else if(type == "init")
                obj.setScriptInit(script);
        }
    }
    for(tag = objXML->FirstChildElement("sound"); tag; tag = tag->NextSiblingElement("sound"))
    {
        std::string sound, type;
        if(   getString(tag->Attribute("type"), type)
           && getString(tag->GetText(), sound)
           && sounds.find(sound) != sounds.end())
        {
            if(type == "jump")
                obj.setSoundJump(sounds[sound]);
            else if(type == "multijump")
                obj.setSoundMultijump(sounds[sound]);
        }
    }
}

bool ChimpGame::loadTextures(tinyxml2::XMLDocument& levelXML, TextureMap& textures, SDL_Renderer* const renderer)
{
    for(tinyxml2::XMLElement* texture = levelXML.FirstChildElement("chimptexture");
        texture;
        texture = texture->NextSiblingElement("chimptexture"))
    {
        std::string texName, texFile;
                
        if(!getString(texture->Attribute("name"), texName))
        {
            std::cout << "Error: chimptexture tag without name attribute" << std::endl;
            return false;
        }
        if(!getString(texture->Attribute("file"), texFile))
        {
            std::cout << "Error: texture tag without file attribute" << std::endl;
            return false;
        }
        SDL_Texture* tex = IMG_LoadTexture(renderer, (ASSETS_PATH + texFile).c_str());
        if(!tex)
        {
            std::cout << "Error loading texture file: " << SDL_GetError() << std::endl;
            return false;
        }
        textures[texName] = tex;
    }
    
    return true;
}

bool ChimpGame::loadTiles(tinyxml2::XMLDocument& levelXML, TextureMap& textures, TileMap& tiles)
{
    for(tinyxml2::XMLElement* tile = levelXML.FirstChildElement("chimptile");
        tile;
        tile = tile->NextSiblingElement("chimptile"))
    {
        std::string tileName, texName;
        tinyxml2::XMLElement* tag;
        int x, y, width, height, widthStretched, heightStretched,
            left   = 0,
            right  = 0,
            top    = 0,
            bottom = 0;
        
        if(!getString(tile->Attribute("name"), tileName))
        {
            std::cout << "Error: chimptile tag without name attribute" << std::endl;
            return false;
        }
        
        if( !(tag = tile->FirstChildElement("texture")) )
        {
            std::cout << "Error: chimptile tag without texture child" << std::endl;
            return false;
        }
        if(!getString(tag->Attribute("name"), texName))
        {
            std::cout << "Error: chimptile texture child without name attribute" << std::endl;
            return false;
        }
        if(textures.find(texName) == textures.end())
        {
            std::cout << "Error: no texture named \"" << texName << "\" found" << std::endl;
            return false;
        }
        if(tag->QueryIntAttribute("x", &x) != tinyxml2::XML_SUCCESS)
        {
            std::cout << "Error: chimptile texture child without x attribute" << std::endl;
            return false;
        }
        if(tag->QueryIntAttribute("y", &y) != tinyxml2::XML_SUCCESS)
        {
            std::cout << "Error: chimptile texture child without y attribute" << std::endl;
            return false;
        }
        if(tag->QueryIntAttribute("width", &width) != tinyxml2::XML_SUCCESS)
        {
            std::cout << "Error: chimptile texture child without width attribute" << std::endl;
            return false;
        }
        if(tag->QueryIntAttribute("height", &height) != tinyxml2::XML_SUCCESS)
        {
            std::cout << "Error: chimptile texture child without height attribute" << std::endl;
            return false;
        }
        
        if( (tag = tile->FirstChildElement("stretch")) )
        {
            if(tag->QueryIntAttribute("width", &widthStretched) != tinyxml2::XML_SUCCESS)
                widthStretched = width;
            if(tag->QueryIntAttribute("height", &heightStretched) != tinyxml2::XML_SUCCESS)
                heightStretched = height;
        }
        else
        {
            widthStretched = width;
            heightStretched = height;
        }
        
        if( (tag = tile->FirstChildElement("collision")) )
        {
            tag->QueryIntAttribute("left", &left);
            tag->QueryIntAttribute("right", &right);
            tag->QueryIntAttribute("top", &top);
            tag->QueryIntAttribute("bottom", &bottom);
        }
        
        SDL_Rect texRect, drRect;
        IntBox colBox;
        texRect.x = x;
        texRect.y = y;
        texRect.w = width;
        texRect.h = height;
        drRect.w = widthStretched;
        drRect.h = heightStretched;
        colBox.l = left;
        colBox.r = right;
        colBox.t = top;
        colBox.b = bottom;
        tiles[tileName] = ChimpTile(textures[texName], texRect, drRect, colBox);
    }
    
    return true;
}

bool ChimpGame::loadSounds(tinyxml2::XMLDocument& levelXML, SoundMap& sounds, MusicMap& musics)
{
    for(tinyxml2::XMLElement* sound = levelXML.FirstChildElement("chimpsound");
        sound;
        sound = sound->NextSiblingElement("chimpsound"))
    {
        std::string name, file;
        if(!getString(sound->Attribute("name"), name))
        {
            std::cout << "Error: chimpsound tag without name attribute" << std::endl;
            return false;
        }
        if(!getString(sound->Attribute("file"), file))
        {
            std::cout << "Error: chimpsound tag without file attribute" << std::endl;
            return false;
        }
        
        if( !(sounds[name] = Mix_LoadWAV((ASSETS_PATH + file).c_str())) )
        {
            std::cout << "Mix_LoadWAV error: " << SDL_GetError() << std::endl;
            return false;
        }
    }
    
    for(tinyxml2::XMLElement* music = levelXML.FirstChildElement("chimpmusic");
        music;
        music = music->NextSiblingElement("chimpmusic"))
    {
        std::string name, file;
        if(!getString(music->Attribute("name"), name))
        {
            std::cout << "Error: chimpmusic tag without name attribute" << std::endl;
            return false;
        }
        if(!getString(music->Attribute("file"), file))
        {
            std::cout << "Error: chimpmusic tag without file attribute" << std::endl;
            return false;
        }
        
        if( !(musics[name] = Mix_LoadMUS((ASSETS_PATH + file).c_str())) )
        {
            std::cout << "Mix_LoadMUS error: " << SDL_GetError() << std::endl;
            return false;
        }
    }
    
    return true;
}























} // namespace chimp
