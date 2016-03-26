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
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <fstream>
#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_gamecontroller.h>
#include <string>
#include <vector>
#include "cleanup.h"
#include "ChimpConstants.h"
#include "ChimpObject.h"
#include "ChimpMobile.h"
#include "SDLUtils.h"

using std::cout;
using std::endl;


bool loadChimpTextures(std::vector<SDL_Texture*> &textures, std::vector<SDL_Rect> &rects, SDL_Renderer* renderer);
void addController(int id);
void pushObject(std::vector<std::unique_ptr<ChimpObject>>& objects, SDL_Texture* texture, SDL_Rect rect,
                SDL_Renderer* renderer, int x, int y, int tilesX, int tilesY);
void pushMobile(std::vector<std::unique_ptr<ChimpObject>>& objects, SDL_Texture* texture, SDL_Rect rect,
                SDL_Renderer* renderer, int x, int y, int tilesX, int tilesY);

int main(int argc, char **argv)
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> textures;
    std::vector<SDL_Rect> textureRects;
    std::vector<SDL_GameController*> controllers;
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
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
    /*if(TTF_Init() != 0)
    {
        logSDLError(std::cout, "TTF_Init");
        cleanup(window, renderer);
        SDL_Quit();
        return 1;
    }*/
    if( !loadChimpTextures(textures, textureRects, renderer) )
    {
        cleanup(window, renderer, &textures);
        SDL_Quit();
        return 1;
    }
    if(SDL_GameControllerAddMappingsFromFile("gamecontrollerdb") == -1)
        logSDLError(std::cout, "GameControllerAddMappingsFromFile");
    for(int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if( SDL_IsGameController(i) )
            controllers.push_back( SDL_GameControllerOpen(i) );
    }
    
    SDL_Event event;
    bool quit = false;
    bool keyJumpPressed = false;
    ChimpMobile player(textures[0], textureRects[0], renderer, SCREEN_WIDTH>>1, 30, 1, 1);
    std::vector< std::unique_ptr<ChimpObject> > worldObjects;
    pushObject(worldObjects, textures[1], textureRects[1], renderer, 0, 150, 8, 1);
    pushObject(worldObjects, textures[1], textureRects[1], renderer, -SCREEN_WIDTH, 0,
               SCREEN_WIDTH * 3 / textureRects[1].w + 1, 3);
    pushMobile(worldObjects, textures[2], textureRects[2], renderer, 100, 30, 1, 1);
    (*worldObjects.back()).runRight();
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    while(!quit)
    {
        while( SDL_PollEvent(&event) )
        {
            switch(event.type)
            {
            case SDL_QUIT:
            {
                quit = true;
                continue;
            }
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    player.runRight();
                    break;
                case SDLK_LEFT:
                    player.runLeft();
                    break;
                case SDLK_UP:
                case SDLK_SPACE:
                    if(!keyJumpPressed)
                    {
                        player.jump();
                        keyJumpPressed = true;
                    }
                    break;
                case SDLK_x:
                    player.sprint();
                    break;
                }
                break;
            }
            case SDL_KEYUP:
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    player.stopRunningRight();
                    break;
                case SDLK_LEFT:
                    player.stopRunningLeft();
                    break;
                case SDLK_UP:
                case SDLK_SPACE:
                    player.stopJumping();
                    keyJumpPressed = false;
                    break;
                case SDLK_x:
                    player.stopSprinting();
                    break;
                }
                break;
            }
            case SDL_CONTROLLERBUTTONDOWN:
            {
                if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A && !keyJumpPressed)
                {
                    player.jump();
                    keyJumpPressed = true;
                }
                else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
                    player.sprint();
                break;
            }
            case SDL_CONTROLLERBUTTONUP:
            {
                if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
                {
                    player.stopJumping();
                    keyJumpPressed = false;
                }
                else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
                    player.stopSprinting();
                break;
            }
            case SDL_CONTROLLERAXISMOTION:
                if(event.caxis.axis == 0)
                {
                    if(event.caxis.value > JOYSTICK_DEAD_ZONE)
                        player.runRight();
                    else if(event.caxis.value < -JOYSTICK_DEAD_ZONE)
                        player.runLeft();
                    else
                        player.stopRunning();
                }
            }
        }
        
        SDL_RenderClear(renderer);
        for(std::unique_ptr<ChimpObject>& obj : worldObjects)
        {
            (*obj).update(worldObjects);
            (*obj).render();
        }
        player.update(worldObjects);
        player.render();
        SDL_RenderPresent(renderer);
        
        SDL_Delay(1);
    }
    
    return 0;
}

bool loadChimpTextures(std::vector<SDL_Texture*> &textures, std::vector<SDL_Rect> &rects, SDL_Renderer* renderer)
{
    std::ifstream data(TEXTURE_METADATA_FILE);
    std::string line;
    int sub1, sub2;
    int numTextures;
    bool numTexturesLoaded = false;
    
    if( !data.is_open() )
    {
        std::cout << "Couldn't open texture data file.";
        return false;
    }
    
    while(!numTexturesLoaded)
    {
        std::getline(data, line);
        sub1 = line.find(";");
        if(sub1 == std::string::npos)
            continue;
        ++sub1;
        sub2 = line.find(";", sub1);
        numTextures = std::stoi( line.substr(sub1, sub2-sub1) );
        numTexturesLoaded = true;
    }
    
    for(int i = 0; i < numTextures; ++i)
    {
        std::getline(data, line);
        sub1 = line.find(TEXTURE_DELIMITER);
        if(sub1 == std::string::npos)
        {
            --i;
            continue;
        }
        ++sub1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        textures.push_back( loadTexture(ASSETS_PATH + line.substr(sub1, sub2-sub1), renderer) );
        
        if(textures.back() == nullptr)
            return false;
        
        rects.push_back( SDL_Rect() );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        rects.back().x = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        rects.back().y = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        rects.back().w = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        rects.back().h = std::stoi( line.substr(sub1, sub2-sub1) );
    }
    data.close();
    return true;
}

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

void pushObject(std::vector<std::unique_ptr<ChimpObject>>& objects, SDL_Texture* texture, SDL_Rect rect,
                SDL_Renderer* renderer, int x, int y, int tilesX, int tilesY)
{
    objects.push_back(std::unique_ptr<ChimpObject>( new ChimpObject(texture, rect, renderer, x, y, tilesX, tilesY) ));
}

void pushMobile(std::vector<std::unique_ptr<ChimpObject>>& objects, SDL_Texture* texture, SDL_Rect rect,
                SDL_Renderer* renderer, int x, int y, int tilesX, int tilesY)
{
    objects.push_back(std::unique_ptr<ChimpMobile>( new ChimpMobile(texture, rect, renderer, x, y, tilesX, tilesY) ));
}


































