#include "loadLevel.h"

using namespace tinyxml2;

tinyxml2::XMLError loadLevel(std::map<std::string, chimp::ChimpTile>& tiles, SDL_Renderer* renderer,
                             chimp::ChimpGame& game)
{    
    game.setWorldBox(-SCREEN_WIDTH/2, SCREEN_WIDTH*2, -SCREEN_HEIGHT*0.15, SCREEN_HEIGHT);
    
    /*chimp::TileVec runtiles =  { tiles["monkey run 1"], tiles["monkey run 2"], tiles["monkey run 3"],
                                tiles["monkey run 4"], tiles["monkey run 5"], tiles["monkey run 6"],
                                tiles["monkey run 7"] };
    chimp::TileVec jumptiles = { tiles["monkey jump 1"], tiles["monkey jump 2"], tiles["monkey jump 3"],
                                 tiles["monkey jump 4"], tiles["monkey jump 5"], tiles["monkey jump 6"],
                                 tiles["monkey jump 7"] };
    chimp::TileVec idletiles = { tiles["monkey idle 1"], tiles["monkey idle 1"], tiles["monkey idle 2"] };
    game.getPlayer() = new chimp::ChimpCharacter(runtiles, jumptiles, idletiles, renderer, SCREEN_WIDTH>>1, 400, 1, 1,
            chimp::FACTION_PLAYER, chimp::FACTION_BADDIES, 100);*/
    
    XMLDocument levelXML;
    XMLError result;
    XMLNode* level;
    XMLElement* objXML;
    XMLElement* tag;
    const char* attrib;
    const char* val;
    std::string attribStr, valStr;
    chimp::TileVec runtiles, jumptiles, idletiles;
    
    result = levelXML.LoadFile("assets/world2.xml");
    XMLCheckResult(result);
    level = levelXML.FirstChildElement("chimp_level");
    if(level == nullptr)
        return XML_ERROR_FILE_READ_ERROR;
    
    for( objXML = level->FirstChildElement("object"); objXML; objXML = objXML->NextSiblingElement("object") )
    {
        attrib = objXML->Attribute("type");
        if(!attrib)
            continue;
        attribStr = attrib;
        if(attribStr == "player")
        {
            loadAnimation(objXML, "run", runtiles, tiles);
            loadAnimation(objXML, "jump", jumptiles, tiles);
            loadAnimation(objXML, "idle", idletiles, tiles);
            game.getPlayer() = new chimp::ChimpCharacter(renderer, runtiles, jumptiles, idletiles);
            loadObject(objXML, *game.getPlayer());
        }
    }
    
    
    game.pushObj(chimp::BACK, tiles["background1"], -SCREEN_WIDTH/2, 0, 5, 1);
    //game.pushObj(chimp::BACK, tiles[13], -SCREEN_WIDTH>>1, tiles[13].drawRect.h, 5, 1);    
    
    game.pushObj(chimp::MID, tiles["top ground"], -SCREEN_WIDTH>>1, 0, 8, 1);
    game.pushObj(chimp::MID, tiles["top ground right cliff"], game.getObjBack(chimp::MID).collisionRight(), 0, 1, 1);
    game.pushObj(chimp::MID, tiles["mid island"], (SCREEN_WIDTH<<1) - tiles["mid island"].textureRect.w*2,
                 tiles["top ground"].textureRect.h*1.5, 2, 1);
    game.pushObj(chimp::MID, tiles["left island"],
                 (SCREEN_WIDTH<<1) - tiles["mid island"].textureRect.w*2 - tiles["left island"].textureRect.w,
                 tiles["top ground"].textureRect.h*1.5, 1, 1);
    
    game.pushChar(chimp::MID, tiles["baddie"], -SCREEN_WIDTH>>1, 160, 1, 1, 100, chimp::FACTION_BADDIES,
                  chimp::FACTION_PLAYER);
    game.getObjBack(chimp::MID).setDamageTop(false);
    game.getObjBack(chimp::MID).setRunAccel(RUN_ACCEL / 2.0);
    game.getObjBack(chimp::MID).runRight();
    game.getObjBack(chimp::MID).setJumper(true);
    
    game.pushObj(chimp::FORE, tiles["green bush"], 0, 0, 1, 1);
    
    game.initialize();
    
    return result;
}

XMLError loadAnimation(XMLElement* objXML, std::string anim, chimp::TileVec& tilvec,
                       std::map<std::string, chimp::ChimpTile>& tiles)
{
    for( XMLElement* tag = objXML->FirstChildElement("tile"); tag; tag = tag->NextSiblingElement("tile") )
        if( anim == tag->Attribute("animation") )
            tilvec.push_back( tiles[tag->GetText()] );
}

void loadObject(XMLElement* objXML, chimp::ChimpObject& obj)
{
    XMLElement* tag;
    const char* attrib;
    const char* val;
    std::string attribStr, valStr;
    
    tag = objXML->FirstChildElement("position");
    if(tag)
    {
        int pos;
        if(tag->QueryIntAttribute("x", &pos) == XML_SUCCESS)
        {
            obj.setInitialX(pos);
            obj.setX(pos);
        }
        if(tag->QueryIntAttribute("y", &pos) == XML_SUCCESS)
        {
            obj.setInitialY(SCREEN_HEIGHT - pos - obj.height);
            obj.setY(SCREEN_HEIGHT - pos - obj.height);
        }
    }
    
    tag = objXML->FirstChildElement("factions");
    if(tag)
    {
        int factions;
        if(tag->QueryIntAttribute("friends", &factions) == XML_SUCCESS)
            obj.setFriends((chimp::Faction)factions);
        if(tag->QueryIntAttribute("enemies", &factions) == XML_SUCCESS)
            obj.setEnemies((chimp::Faction)factions);
    }
    
    tag = objXML->FirstChildElement("maxhealth");
    if(tag)
    {
        int health;
        if(tag->QueryIntText(&health) == XML_SUCCESS)
        {
            obj.setMaxHealth(health);
            obj.setHealth(health);
        }
    }
    
    for(tag = objXML->FirstChildElement("bounded"); tag; tag = tag->NextSiblingElement("bounded"))
    {
        attrib = tag->Attribute("type");
        val = tag->GetText();
        if(!val || !attrib)
            continue;
        attribStr = attrib;
        valStr = val;
        
        bool tf;
        if(valStr == "true")
            tf = true;
        else if(valStr == "false")
            tf = false;
        else
            continue;
            
        if(attribStr == "left")
            obj.setBoundLeft(tf);
        else if(attribStr == "right")
            obj.setBoundRight(tf);
        else if(attribStr == "top")
            obj.setBoundTop(tf);
        else if(attribStr == "bottom")
            obj.setBoundBottom(tf);
    }
    
    tag = objXML->FirstChildElement("respawn");
    if(tag)
    {
        valStr = tag->GetText();
        if(valStr == "true")
            obj.setRespawn(true);
        else if(valStr == "false")
            obj.setRespawn(false);
    }
}






















