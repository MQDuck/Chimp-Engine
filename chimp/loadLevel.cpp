#include "loadLevel.h"

namespace chimp
{

using namespace tinyxml2;

Layer getLayer(const XMLElement* objXML);
bool getBool(const char* const boolStr, bool& result);
bool getString(const char* const cStr, std::string& str);
std::string getMode(const XMLElement* const tag);
void loadWorldBox(const XMLElement* const edges, ChimpGame& game);
bool loadAllAnimations(XMLElement* const objXML, TileVec& idletiles, TileVec& runtiles, TileVec& jumptiles,
                       TileMap& tiles);
void loadAnimation(XMLElement* const objXML, std::string anim, TileVec& tilvec, TileMap& tiles);
void loadObject(XMLElement* const objXML, ChimpObject& obj);

XMLError loadLevel(const std::string levelFile, std::map<std::string, ChimpTile>& tiles,
                             SDL_Renderer* const renderer, ChimpGame& game)
{
    XMLDocument levelXML;
    XMLError result;
    XMLNode* level;
    XMLElement* objXML;
    XMLElement* tag;
    
    if( (result = levelXML.LoadFile(levelFile.c_str())) != XML_SUCCESS )
        return result;
    level = levelXML.FirstChildElement("chimplevel");
    if(!level)
        return XML_ERROR_FILE_READ_ERROR;
    
    loadWorldBox(level->FirstChildElement("edges"), game);
    if( (tag = level->FirstChildElement("scrollfactor")) )
    {
        float factor;
        if(tag->QueryFloatAttribute("background", &factor) == XML_SUCCESS)
            game.setScrollFactor(BACK, factor);
        if(tag->QueryFloatAttribute("foreground", &factor) == XML_SUCCESS)
            game.setScrollFactor(FORE, factor);
    }
    
    for( objXML = level->FirstChildElement("object"); objXML; objXML = objXML->NextSiblingElement("object") )
    {
        const char* type = objXML->Attribute("type");
        if(!type)
            continue;
        std::string typeStr = type;
        if(typeStr == "player")
        {
            TileVec runtiles, jumptiles, idletiles;
            if(loadAllAnimations(objXML, idletiles, runtiles, jumptiles, tiles))
            {
                game.getPlayer() = new ChimpCharacter(renderer, runtiles, jumptiles, idletiles);
                loadObject(objXML, *game.getPlayer());
            }
        }
        else if(typeStr == "character")
        {
            TileVec runtiles, jumptiles, idletiles;
            std::string tile;
            if(loadAllAnimations(objXML, idletiles, runtiles, jumptiles, tiles))
            {
                Layer layer = getLayer(objXML);
                game.pushChar(layer, runtiles, jumptiles, idletiles);
                loadObject(objXML, game.getObjBack(layer));
            }
            else if(getString(objXML->FirstChildElement("tile")->GetText(), tile))
            {
                Layer layer = getLayer(objXML);
                game.pushChar(layer, tiles[tile]);
                loadObject(objXML, game.getObjBack(layer));
            }
        }
        else if(typeStr == "object")
        {
            std::string tile;
            if(getString(objXML->FirstChildElement("tile")->GetText(), tile))
            {
                Layer layer = getLayer(objXML);
                game.pushObj(layer, tiles[tile]);
                loadObject(objXML, game.getObjBack(layer));
            }   
        }
    }
    
    return XML_SUCCESS;
}

Layer getLayer(const XMLElement *objXML)
{
    const char* layer = objXML->Attribute("layer");
    if(layer)
    {
        std::string layerStr = layer;
        if(layerStr == "background")
            return BACK;
        else if(layerStr == "foreground")
            return FORE;
    }
    return MID;
}

bool getBool(const char * const boolStr, bool &result)
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

bool getString(const char* const cStr, std::string& str)
{
    if(cStr)
    {
        str = cStr;
        return true;
    }
    return false;
}

std::string getMode(const XMLElement* const tag)
{
    std::string mode;
    return getString(tag->Attribute("mode"), mode) ? mode : "absolute";
}

void loadWorldBox(const XMLElement* const edges, ChimpGame& game)
{
    int wbLeft = 0;
    int wbRight = SCREEN_WIDTH;
    int wbTop = 0;
    int wbBottom = SCREEN_HEIGHT;
    if(edges)
    {
        int val;
        if(edges->QueryIntAttribute("left", &val) == XML_SUCCESS)
            wbLeft = val;
        if(edges->QueryIntAttribute("right", &val) == XML_SUCCESS)
            wbRight = val;
        if(edges->QueryIntAttribute("top", &val) == XML_SUCCESS)
            wbTop = val;
        if(edges->QueryIntAttribute("bottom", &val) == XML_SUCCESS)
            wbBottom = val;
    }
    game.setWorldBox(wbLeft, wbRight, wbTop, wbBottom);
}

bool loadAllAnimations(XMLElement* const objXML, TileVec& idletiles, TileVec& runtiles, TileVec& jumptiles,
                       TileMap& tiles)
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

void loadAnimation(XMLElement* const objXML, std::string anim, TileVec& tilvec, TileMap& tiles)
{
    std::string animation;
    for( XMLElement* tag = objXML->FirstChildElement("tile"); tag; tag = tag->NextSiblingElement("tile") )
        if(getString(tag->Attribute("animation"), animation) && anim == animation)
            tilvec.push_back( tiles[tag->GetText()] );
}

void  loadObject(XMLElement* const objXML, ChimpObject& obj)
{
    XMLElement* tag;
    
    if( (tag = objXML->FirstChildElement("position")) )
    {
        int pos;
        if(tag->QueryIntAttribute("x", &pos) == XML_SUCCESS)
            obj.setInitialX(pos);
        if(tag->QueryIntAttribute("y", &pos) == XML_SUCCESS)
            obj.setInitialY(SCREEN_HEIGHT - pos - obj.height);
    }
    if( (tag = objXML->FirstChildElement("tiles")) )
    {
        int tiles;
        if(tag->QueryIntAttribute("x", &tiles) == XML_SUCCESS)
            obj.setTilesX(tiles);
        if(tag->QueryIntAttribute("y", &tiles) == XML_SUCCESS)
            obj.setTilesY(tiles);
    }
    if( (tag = objXML->FirstChildElement("maxhealth")) )
    {
        int health;
        if(tag->QueryIntText(&health) == XML_SUCCESS)
        {
            obj.setMaxHealth(health);
            obj.setHealth(health);
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
    if( (tag = objXML->FirstChildElement("run")) )
    {
        std::string run;
        if(getString(tag->GetText(), run))
        {
            if(run == "left")
                obj.runLeft();
            else if(run == "right")
                obj.runRight();
        }
    }
    if( (tag = objXML->FirstChildElement("stopfactor")) )
    {
        float factor;
        std::string mode;
        if(tag->QueryFloatText(&factor) == XML_SUCCESS)
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
        if(tag->QueryFloatText(&factor) == XML_SUCCESS)
            obj.setSprintFactor(factor);
    }
    if( (tag = objXML->FirstChildElement("maxjumps")) )
    {
        int max;
        if(tag->QueryIntText(&max) == XML_SUCCESS)
            obj.setMaxJumps(max);
    }
    if( (tag = objXML->FirstChildElement("behavior")) )
    {
        std::string behavior;
        if(getString(tag->GetText(), behavior))
            obj.setBehavior(behavior);
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
        if(tag->QueryFloatText(&accel) == XML_SUCCESS && getString(tag->Attribute("type"), type))
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
        if(tag->QueryFloatText(&impulse) == XML_SUCCESS && getString(tag->Attribute("type"), type))
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
        if(tag->QueryFloatText(&resistance) == XML_SUCCESS && getString(tag->Attribute("type"), type))
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
}

} // namespace chimp



























