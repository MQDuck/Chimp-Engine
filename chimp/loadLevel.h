#ifndef LOADLEVEL_H
#define LOADLEVEL_H

#include <map>
#include <tinyxml2.h>
#include "ChimpGame.h"

namespace chimp
{

tinyxml2::XMLError loadLevel(const std::string levelFile, std::map<std::string, ChimpTile>& tiles,
                             SDL_Renderer* const renderer, ChimpGame& game);
void loadWorldBox(const tinyxml2::XMLElement* const edges, ChimpGame& game);
void loadAnimation(tinyxml2::XMLElement* const objXML, std::string anim, TileVec& tilvec, std::map<std::string,
                   ChimpTile>& tiles);
bool loadAllAnimations(tinyxml2::XMLElement* const objXML, TileVec& idletiles, TileVec& runtiles,
                       TileVec& jumptiles, std::map<std::string, ChimpTile>& tiles);
void loadObject(tinyxml2::XMLElement* const objXML, ChimpObject& obj);
void loadWorldBox(tinyxml2::XMLNode* const level, ChimpGame& game);
Layer getLayer(const tinyxml2::XMLElement* objXML);
bool getBool(const char* const boolStr, bool& result);
bool getString(const char* const cStr, std::string& str);
std::string getMode(const tinyxml2::XMLElement* const tag);

} // namespace chimp

#endif // LOADLEVEL_H
