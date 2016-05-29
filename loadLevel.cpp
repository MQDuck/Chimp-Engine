#include "loadLevel.h"

using namespace tinyxml2;

tinyxml2::XMLError loadLevel(std::map<std::string, chimp::ChimpTile>& tiles, SDL_Renderer* renderer,
                             chimp::ChimpGame& game)
{    
    game.setWorldBox(-SCREEN_WIDTH/2, SCREEN_WIDTH*2, -SCREEN_HEIGHT*0.15, SCREEN_HEIGHT);
        
    XMLDocument levelXML;
    XMLError result;
    XMLNode* level;
    XMLElement* objXML;
    
    if( (result = levelXML.LoadFile("assets/world2.xml")) != XML_SUCCESS )
        return result;
    level = levelXML.FirstChildElement("chimp_level");
    if(!level)
        return XML_ERROR_FILE_READ_ERROR;
    
    for( objXML = level->FirstChildElement("object"); objXML; objXML = objXML->NextSiblingElement("object") )
    {
        const char* type = objXML->Attribute("type");
        if(!type)
            continue;
        std::string typeStr = type;
        if(typeStr == "player")
        {
            chimp::TileVec runtiles, jumptiles, idletiles;
            if(loadAllAnimations(objXML, idletiles, runtiles, jumptiles, tiles))
            {
                game.getPlayer() = new chimp::ChimpCharacter(renderer, runtiles, jumptiles, idletiles);
                loadObject(objXML, game.getPlayer());
            }
        }
        else if(typeStr == "character")
        {
            chimp::TileVec runtiles, jumptiles, idletiles;
            std::string tile;
            if(loadAllAnimations(objXML, idletiles, runtiles, jumptiles, tiles))
            {
                chimp::Layer layer = getLayer(objXML);
                game.pushChar(layer, runtiles, jumptiles, idletiles);
                loadObject(objXML, &game.getObjBack(layer));
            }
            else if(getString(objXML->FirstChildElement("tile")->GetText(), &tile))
            {
                //chimp::Layer layer = getLayer(objXML);
                //game.pushChar(layer, tiles[tile]);
                //loadObject(objXML, &game.getObjBack(layer));
                game.pushChar(chimp::MID, tiles["baddie"], -SCREEN_WIDTH>>1, 160, 1, 1, 100, chimp::FACTION_BADDIES,
                              chimp::FACTION_PLAYER);
                game.getObjBack(chimp::MID).setDamageTop(false);
                game.getObjBack(chimp::MID).setRunAccel(RUN_ACCEL / 2.0);
                game.getObjBack(chimp::MID).runRight();
                game.getObjBack(chimp::MID).setJumper(true);
            }
        }
        else if(typeStr == "object")
        {
            std::string tile;
            if(getString(objXML->FirstChildElement("tile")->GetText(), &tile))
            {
                chimp::Layer layer = getLayer(objXML);
                game.pushObj(layer, tiles[tile]);
                loadObject(objXML, &game.getObjBack(layer));
            }   
        }
    }
    
    return result;
}

void loadAnimation(XMLElement* objXML, std::string anim, chimp::TileVec& tilvec,
                       std::map<std::string, chimp::ChimpTile>& tiles)
{
    std::string animation;
    for( XMLElement* tag = objXML->FirstChildElement("tile"); tag; tag = tag->NextSiblingElement("tile") )
        if(getString(tag->Attribute("animation"), &animation) && anim == animation)
            tilvec.push_back( tiles[tag->GetText()] );
}

bool loadAllAnimations(XMLElement *objXML, chimp::TileVec &idletiles, chimp::TileVec &runtiles,
                       chimp::TileVec &jumptiles, std::map<std::string, chimp::ChimpTile> &tiles)
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

void loadObject(XMLElement* objXML, chimp::ChimpObject* obj)
{
    XMLElement* tag;
    
    if( (tag = objXML->FirstChildElement("position")) )
    {
        int pos;
        if(tag->QueryIntAttribute("x", &pos) == XML_SUCCESS)
            obj->setInitialX(pos);
        if(tag->QueryIntAttribute("y", &pos) == XML_SUCCESS)
            obj->setInitialY(SCREEN_HEIGHT - pos - obj->height);
    }
    if( (tag = objXML->FirstChildElement("factions")) )
    {
        int factions;
        if(tag->QueryIntAttribute("friends", &factions) == XML_SUCCESS)
            obj->setFriends((chimp::Faction)factions);
        if(tag->QueryIntAttribute("enemies", &factions) == XML_SUCCESS)
            obj->setEnemies((chimp::Faction)factions);
    }
    if( (tag = objXML->FirstChildElement("tiles")) )
    {
        int tiles;
        if(tag->QueryIntAttribute("x", &tiles) == XML_SUCCESS)
            obj->setTilesX(tiles);
        if(tag->QueryIntAttribute("y", &tiles) == XML_SUCCESS)
            obj->setTilesY(tiles);
    }
    if( (tag = objXML->FirstChildElement("maxhealth")) )
    {
        int health;
        if(tag->QueryIntText(&health) == XML_SUCCESS)
        {
            obj->setMaxHealth(health);
            obj->setHealth(health);
        }
    }
    if( (tag = objXML->FirstChildElement("respawn")) )
    {
        bool respawn;
        if(getBool(tag->GetText(), &respawn))
            obj->setRespawn(respawn);
    }
    if( (tag = objXML->FirstChildElement("jumper")) )
    {
        bool jumper;
        if(getBool(tag->GetText(), &jumper))
            obj->setJumper(jumper);
    }
    if( (tag = objXML->FirstChildElement("damage")) )
    {
        bool tf;
        if(getBool(tag->Attribute("left"), &tf))
            obj->setDamageLeft(tf);
        if(getBool(tag->Attribute("right"), &tf))
            obj->setDamageRight(tf);
        if(getBool(tag->Attribute("top"), &tf))
            obj->setDamageTop(tf);
        if(getBool(tag->Attribute("bottom"), &tf))
            obj->setDamageBottom(tf);
    }
    if( (tag = objXML->FirstChildElement("bounded")) )
    {
        bool tf;
        if(getBool(tag->Attribute("left"), &tf))
            obj->setBoundLeft(tf);
        if(getBool(tag->Attribute("right"), &tf))
            obj->setBoundRight(tf);
        if(getBool(tag->Attribute("top"), &tf))
            obj->setBoundTop(tf);
        if(getBool(tag->Attribute("bottom"), &tf))
            obj->setBoundBottom(tf);
    }
    if( (tag = objXML->FirstChildElement("run")) )
    {
        std::string run;
        if(getString(tag->GetText(), &run))
        {
            if(run == "left")
                obj->runLeft();
            else if(run == "right")
                obj->runRight();
        }
    }
    if( (tag = objXML->FirstChildElement("jumper")) )
    {
        bool jumper;
        if(getBool(tag->GetText(), &jumper))
            obj->setJumper(jumper);
    }
    
    for(tag = objXML->FirstChildElement("acceleration"); tag; tag = tag->NextSiblingElement("acceleration"))
    {
        float accel;
        std::string type, mode;
        if(   tag->QueryFloatText(&accel) == XML_SUCCESS
           && getString(tag->Attribute("type"), &type)
           && getString(tag->Attribute("mode"), &mode) )
        {
            if(type == "run")
            {
                if(mode == "absolute")
                    obj->setRunAccel(accel);
                else if(mode == "scale")
                    obj->setRunAccel(obj->getRunAccel() * accel);
            }
            else if(type == "jump")
            {
                if(mode == "absolute")
                    obj->setJumpAccel(accel);
                else if(mode == "scale")
                    obj->setJumpAccel(obj->getJumpAccel() * accel);
            }
        }
    }
    
    /*for(tag = objXML->FirstChildElement("bounded"); tag; tag = tag->NextSiblingElement("bounded"))
    {
        std::string type;
        bool bound;
        if(getString(tag->Attribute("type"), &type) && getBool(tag->GetText(), &bound))
        {
            if(type == "left")
                obj->setBoundLeft(bound);
            else if(type == "right")
                obj->setBoundRight(bound);
            else if(type == "top")
                obj->setBoundTop(bound);
            else if(type == "bottom")
                obj->setBoundBottom(bound);
        }
    }*/
}

chimp::Layer getLayer(XMLElement* objXML)
{
    const char* layer = objXML->Attribute("layer");
    if(layer)
    {
        std::string layerStr = layer;
        if(layerStr == "background")
            return chimp::BACK;
        else if(layerStr == "foreground")
            return chimp::FORE;
    }
    return chimp::MID;
}

bool getBool(const char* boolStr, bool* result)
{
    if(!boolStr)
        return false;
    if(strcmp(boolStr, "true") == 0)
    {
        *result = true;
        return true;
    }
    if(strcmp(boolStr, "false") == 0)
    {
        *result = false;
        return true;
    }
    return false;
}

bool getString(const char* cStr, std::string* str)
{
    if(cStr)
    {
        *str = cStr;
        return true;
    }
    return false;
}



























