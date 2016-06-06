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

#include <fstream>
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_gamecontroller.h>
#include <string>
#include <vector>
#include <map>
#include <tinyxml2.h>
#include <lua.hpp>
#include "cleanup.h"
#include "ChimpConstants.h"
#include "chimp/ChimpGame.h"
#include "chimp/ChimpObject.h"
#include "chimp/ChimpMobile.h"
#include "chimp/ChimpCharacter.h"
#include "chimp/ChimpTile.h"
#include "chimp/ChimpStructs.h"
#include "chimp/loadLevel.h"
#include "SDLUtils.h"

bool loadChimpTextures(chimp::TileMap& tiles, std::map<std::string, SDL_Texture*>& textures,
                       SDL_Renderer* const renderer);
//void addController(int id);

inline void keyDown(SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed);
inline void keyUp(SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed);
inline void buttonDown(SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed);
inline void buttonUp(SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed);
inline void axisMotion(SDL_Event& event, chimp::ChimpGame& game);

void drawHUD(chimp::ChimpGame& game, SDL_Renderer* const renderer, TTF_Font* font, SDL_Texture* const healthTex);

static Uint32 resetTimer(Uint32 interval, void* const game);

int main(const int argc, char** const argv)
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::vector<SDL_GameController*> controllers;
    //std::vector<SDL_Texture*> textures;
    std::map<std::string, SDL_Texture*> textures;
    chimp::TileMap tiles;
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER) < 0)
    {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }
    window = SDL_CreateWindow("Chimp Out!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == nullptr)
    {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == nullptr)
    {
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window);
        SDL_Quit();
        return 1;
    }
    if( (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG )
    {
        logSDLError(std::cout, "IMG_Init");
        cleanup(window, renderer);
        SDL_Quit();
        return 1;
    }
    if(TTF_Init() != 0)
    {
        logSDLError(std::cout, "TTF_Init");
        cleanup(window, renderer);
        SDL_Quit();
        return 1;
    }
    font = TTF_OpenFont( (ASSETS_PATH + FONT_FILE).c_str(), FONT_SIZE );
    if(font == nullptr)
    {
        logSDLError(std::cout, "TTF_OpenFont");
        cleanup(window, renderer, font);
        SDL_Quit();
        return 1;
    }
    if( !loadChimpTextures(tiles, textures, renderer) )
    {
        cleanup(window, renderer, font, &textures);
        SDL_Quit();
        return 1;
    }
    if(SDL_GameControllerAddMappingsFromFile( CONTROLLER_MAP_FILE.c_str() ) == -1)
        logSDLError(std::cout, "GameControllerAddMappingsFromFile");
    for(int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if( SDL_IsGameController(i) )
            controllers.push_back( SDL_GameControllerOpen(i) );
    }
    
    SDL_Event event;
    bool quit = false;
    bool keyJumpPressed = false;
    chimp::ChimpGame game(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Texture* healthTex = renderText(TEXT_HEALTH, font, FONT_COLOR, renderer);
    Uint32 timeLast, timeNow;
    std::string levelFile = ASSETS_PATH + DEFAULT_LEVEL;
    
    if(argc > 1)
    {
        levelFile = argv[1];
        if(levelFile[0] != '/')
            levelFile = ASSETS_PATH + levelFile;
    }
    if(chimp::loadLevel(levelFile, tiles, renderer, game) != tinyxml2::XML_SUCCESS)
    {
        std::cout << "Couldn't load level file \"" << levelFile << "\"." << std::endl;
        cleanup(window, renderer, font, &textures);
        SDL_Quit();
        return 1;
    }
    game.initialize();
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    timeLast = SDL_GetTicks();
    while(!quit)
    {
        while( SDL_PollEvent(&event) )
        {
            switch(event.type)
            {
            case SDL_QUIT:
                quit = true;
                continue;
            case SDL_KEYDOWN:
                keyDown(event, game, keyJumpPressed);
                break;
            case SDL_KEYUP:
                keyUp(event, game, keyJumpPressed);
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                buttonDown(event, game, keyJumpPressed);
                break;
            case SDL_CONTROLLERBUTTONUP:
                buttonUp(event, game, keyJumpPressed);
                break;
            case SDL_CONTROLLERAXISMOTION:
                axisMotion(event, game);
                break;
            }
        }
        
        SDL_RenderClear(renderer);
        
        timeNow = SDL_GetTicks();
        game.update(timeNow - timeLast);
        timeLast = timeNow;
        
        game.render();
        drawHUD(game, renderer, font, healthTex);
        SDL_RenderPresent(renderer);
        if( game.getPlayer()->getHealth() <= 0 && game.getPlayer()->isActive() )
        {
            game.getPlayer()->deactivate();
            SDL_AddTimer(GAME_OVER_TIME, resetTimer, &game);
        }
        /*{
            SDL_Delay(INVULNERABLE_TIME);
            game.reset();
        }*/
        
        
        SDL_Delay(1);
    }
    
    cleanup(window, renderer, font/*, &textures*/);
    
    return 0;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
bool loadChimpTextures(chimp::TileMap& tiles, std::map<std::string, SDL_Texture*>& textures,
                       SDL_Renderer* const renderer)
{
    std::string line;
    int sub1, sub2;
    int count;
    bool countLoaded;
    
    // Load Textures
    std::ifstream textureData(TEXTURES_FILE);
    if( !textureData.is_open() )
    {
        std::cout << "Couldn't open texture data file." << std::endl;
        return false;
    }
    countLoaded = false;
    while(!countLoaded)
    {
        std::getline(textureData, line);
        sub1 = line.find(TEXTURE_DELIMITER);
        if(sub1 == std::string::npos)
            continue;
        sub2 = line.find(TEXTURE_COMMENT);
        if(sub2 != std::string::npos && sub2 < sub1)
            continue;
        
        ++sub1;
        sub2 = line.find(";", sub1);
        count = std::stoi( line.substr(sub1, sub2-sub1) );
        countLoaded = true;
    }
    for(int i = 0; i < count; ++i)
    {
        std::getline(textureData, line);
        sub1 = line.find(TEXTURE_DELIMITER);
        if(sub1 == std::string::npos)
        {
            --i;
            continue;
        }
        sub2 = line.find(TEXTURE_COMMENT);
        if(sub2 != std::string::npos && sub2 < sub1)
            continue;
        ++sub1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        const std::string texfile = ASSETS_PATH + line.substr(sub1, sub2-sub1);
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        const std::string texname = line.substr(sub1, sub2-sub1);
        textures[texname] = loadTexture(texfile, renderer);
        
        if(textures[texname] == nullptr)
            return false;
    }
    textureData.close();
    
    // Load Tiles
    std::ifstream tileData(TILES_FILE);
    if( !tileData.is_open() )
    {
        std::cout << "Couldn't open tile data file." << std::endl;
        return false;
    }
    countLoaded = false;
    while(!countLoaded)
    {
        std::getline(tileData, line);
        sub1 = line.find(TEXTURE_DELIMITER);
        if(sub1 == std::string::npos)
            continue;
        sub2 = line.find(TEXTURE_COMMENT);
        if(sub2 != std::string::npos && sub2 < sub1)
            continue;
        
        ++sub1;
        sub2 = line.find(";", sub1);
        count = std::stoi( line.substr(sub1, sub2-sub1) );
        countLoaded = true;
    }
    for(int i = 0; i < count; ++i)
    {
        std::getline(tileData, line);
        sub1 = line.find(TEXTURE_DELIMITER);
        if(sub1 == std::string::npos)
        {
            --i;
            continue;
        }
        sub2 = line.find(TEXTURE_COMMENT);
        if(sub2 != std::string::npos && sub2 < sub1)
        {
            --i;
            continue;
        }
        
        ++sub1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        const std::string tilename = line.substr(sub1, sub2-sub1);
        
        tiles[tilename] = chimp::ChimpTile();
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        tiles[tilename].texture = textures[line.substr(sub1, sub2-sub1)];
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        tiles[tilename].textureRect.x = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        tiles[tilename].textureRect.y = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        tiles[tilename].textureRect.w = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        tiles[tilename].textureRect.h = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        tiles[tilename].drawRect.w = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        tiles[tilename].drawRect.h = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        tiles[tilename].collisionBox.l = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        tiles[tilename].collisionBox.r = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        tiles[tilename].collisionBox.t = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        tiles[tilename].collisionBox.b = std::stoi( line.substr(sub1, sub2-sub1) );
    }
    tileData.close();
    
    return true;
}
#pragma GCC diagnostic pop

/*void addController(int id)
{
    if( SDL_IsGameController(id) )
    {
        SDL_GameController* pad = SDL_GameControllerOpen(id);
        if(pad)
        {
            SDL_Joystick* joy = SDL_GameControllerGetJoystick(pad);
            int instanceID = SDL_JoystickInstanceID(joy);
        }
    }
}*/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
static Uint32 resetTimer(Uint32 interval, void* const game)
{
    ((chimp::ChimpGame*)game)->reset();
    return 0;
}
#pragma GCC diagnostic pop

inline void keyDown(SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed)
{
    switch(event.key.keysym.sym)
    {
    case SDLK_RIGHT:
        game.getPlayer()->runRight();
        break;
    case SDLK_LEFT:
        game.getPlayer()->runLeft();
        break;
    case SDLK_UP:
    case SDLK_SPACE:
        if(!keyJumpPressed)
        {
            game.getPlayer()->jump();
            keyJumpPressed = true;
        }
        break;
    case SDLK_x:
        game.getPlayer()->sprint();
        break;
    }
}

inline void keyUp(SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed)
{
    switch(event.key.keysym.sym)
    {
    case SDLK_RIGHT:
        game.getPlayer()->stopRunningRight();
        break;
    case SDLK_LEFT:
        game.getPlayer()->stopRunningLeft();
        break;
    case SDLK_UP:
    case SDLK_SPACE:
        game.getPlayer()->stopJumping();
        keyJumpPressed = false;
        break;
    case SDLK_x:
        game.getPlayer()->stopSprinting();
        break;
    }
}

inline void buttonDown(SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed)
{
    if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A && !keyJumpPressed)
    {
        game.getPlayer()->jump();
        keyJumpPressed = true;
    }
    else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
        game.getPlayer()->sprint();
}

inline void buttonUp(SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed)
{
    if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
    {
        game.getPlayer()->stopJumping();
        keyJumpPressed = false;
    }
    else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
        game.getPlayer()->stopSprinting();
}

inline void axisMotion(SDL_Event& event, chimp::ChimpGame& game)
{
    if(event.caxis.axis == 0)
    {
        if(event.caxis.value > JOYSTICK_DEAD_ZONE)
            game.getPlayer()->runRight();
        else if(event.caxis.value < -JOYSTICK_DEAD_ZONE)
            game.getPlayer()->runLeft();
        else
            game.getPlayer()->stopRunning();
    }
}

void drawHUD(chimp::ChimpGame& game, SDL_Renderer* const renderer, TTF_Font* font, SDL_Texture* const healthTex)
{
    static int oldHealth = -1, w1, w2, h, x;
    static SDL_Texture* currentHealthTex = nullptr;
    static SDL_Texture* gameOverTex = nullptr;
    static int gameOverX, gameOverY;
    
    if(!gameOverTex)
    {
        gameOverTex = renderText(GAME_OVER_TEXT, font, FONT_COLOR, renderer);
        SDL_QueryTexture(gameOverTex, nullptr, nullptr, &gameOverX, &gameOverY);
        gameOverX = (SCREEN_WIDTH - gameOverX) >> 1;
        gameOverY = (SCREEN_HEIGHT - gameOverY) >> 1;
    }
    
    if( oldHealth != game.getPlayer()->getHealth() )
    {
        SDL_DestroyTexture(currentHealthTex);
        oldHealth = game.getPlayer()->getHealth();
        std::string healthString = std::to_string(oldHealth); // Cannot be combined with the line below, apparently
        currentHealthTex = renderText(healthString, font, FONT_COLOR, renderer);
        SDL_QueryTexture(healthTex, nullptr, nullptr, &w1, &h);
        SDL_QueryTexture(currentHealthTex, nullptr, nullptr, &w2, &h);
    }
    
    x = (SCREEN_WIDTH>>1) - w1;
    renderTexture(healthTex, renderer, x, 10);
    renderTexture(currentHealthTex, renderer, x + w1, 10);
    if(game.getPlayer()->getHealth() <= 0)
        renderTexture(gameOverTex, renderer, gameOverX, gameOverY);
}































