#ifndef LOADLEVEL_H
#define LOADLEVEL_H

#include <map>
#include <tinyxml2.h>
#include "ChimpGame.h"

tinyxml2::XMLError loadLevel(const std::string levelFile, std::map<std::string, chimp::ChimpTile>& tiles,
                             SDL_Renderer* const renderer, chimp::ChimpGame& game);
void loadWorldBox(const tinyxml2::XMLElement* const edges, chimp::ChimpGame& game);
void loadAnimation(tinyxml2::XMLElement* const objXML, std::string anim, chimp::TileVec& tilvec, std::map<std::string,
                   chimp::ChimpTile>& tiles);
bool loadAllAnimations(tinyxml2::XMLElement* const objXML, chimp::TileVec& idletiles, chimp::TileVec& runtiles,
                       chimp::TileVec& jumptiles, std::map<std::string, chimp::ChimpTile>& tiles);
void loadObject(tinyxml2::XMLElement* const objXML, chimp::ChimpObject& obj);
void loadWorldBox(tinyxml2::XMLNode* const level, chimp::ChimpGame& game);
chimp::Layer getLayer(const tinyxml2::XMLElement* objXML);
bool getBool(const char* const boolStr, bool& result);
bool getString(const char* const cStr, std::string& str);
std::string getMode(const tinyxml2::XMLElement* const tag);

#endif // LOADLEVEL_H
