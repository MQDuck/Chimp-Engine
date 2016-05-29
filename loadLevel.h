#ifndef LOADLEVEL_H
#define LOADLEVEL_H

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

#include <map>
#include <tinyxml2.h>
#include "ChimpGame.h"

tinyxml2::XMLError loadLevel(std::map<std::string, chimp::ChimpTile>& tiles, SDL_Renderer* renderer,
                             chimp::ChimpGame& game);
tinyxml2::XMLError loadAnimation(tinyxml2::XMLElement* objXML, std::string anim, chimp::TileVec& tilvec,
                                 std::map<std::string, chimp::ChimpTile>& tiles);
void loadObject(tinyxml2::XMLElement* objXML, chimp::ChimpObject& obj);

#endif // LOADLEVEL_H
