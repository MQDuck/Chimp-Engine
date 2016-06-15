#ifndef LOADLEVEL_H
#define LOADLEVEL_H

#include <map>
#include <tinyxml2.h>
#include "ChimpGame.h"

namespace chimp
{

typedef std::map<std::string, ChimpTile> TileMap;

tinyxml2::XMLError loadLevel(const std::string levelFile, std::map<std::string, ChimpTile>& tiles,
                             SDL_Renderer* const renderer, ChimpGame& game);

} // namespace chimp

#endif // LOADLEVEL_H
