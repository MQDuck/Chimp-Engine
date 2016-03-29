#include "ChimpGame.h"

namespace chimp
{

ChimpGame::ChimpGame(SDL_Renderer* rend, const ChimpCharacter& plyr) : renderer(rend), player(plyr) {}

ChimpObject& ChimpGame::getObj(Layer lay, size_t in)
{
    switch(lay)
    {
    case BACK:
        return *background[in];
    case MID:
        return *middle[in];
    case FORE:
        return *foreground[in];
    }
}

ChimpObject& ChimpGame::getObjBack(Layer lay)
{
    switch(lay)
    {
    case BACK:
        return *background.back();
    case MID:
        return *middle.back();
    case FORE:
        return *foreground.back();
    }
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

void ChimpGame::render()
{
    for(auto& obj : background)
    {
        (*obj).update(background);
        (*obj).render();
    }
    for(auto& obj : middle)
    {
        (*obj).update(middle);
        (*obj).render();
    }
    player.update(middle);
    player.render();
    for(auto& obj : foreground)
    {
        (*obj).update(foreground);
        (*obj).render();
    }
}

} // namespace chimp
