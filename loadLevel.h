#ifndef LOADLEVEL_H
#define LOADLEVEL_H

#include <map>
#include <tinyxml2.h>
#include "ChimpGame.h"

tinyxml2::XMLError loadLevel(std::map<std::string, chimp::ChimpTile>& tiles, SDL_Renderer* renderer,
                             chimp::ChimpGame& game);
void loadAnimation(tinyxml2::XMLElement* objXML, std::string anim, chimp::TileVec& tilvec, std::map<std::string,
                   chimp::ChimpTile>& tiles);
bool loadAllAnimations(tinyxml2::XMLElement* objXML, chimp::TileVec& idletiles, chimp::TileVec& runtiles,
                       chimp::TileVec& jumptiles, std::map<std::string, chimp::ChimpTile>& tiles);
void loadObject(tinyxml2::XMLElement* objXML, chimp::ChimpObject* obj);
chimp::Layer getLayer(tinyxml2::XMLElement* objXML);
bool getBool(const char* boolStr, bool* result);
bool getString(const char* cStr, std::string* str);

#endif // LOADLEVEL_H
