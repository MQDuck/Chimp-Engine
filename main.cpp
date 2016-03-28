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
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_gamecontroller.h>
#include <string>
#include <vector>
#include "cleanup.h"
#include "ChimpConstants.h"
#include "ChimpObject.h"
#include "ChimpMobile.h"
#include "ChimpCharacter.h"
#include "SDLUtils.h"

using std::cout;
using std::endl;

typedef std::vector<std::unique_ptr<ChimpObject>> ObjectVector;


bool loadChimpTextures(std::vector<SDL_Texture*>& textures, std::vector<SDL_Rect>& texRects,
                       std::vector<SDL_Rect>& collRects, SDL_Renderer* renderer);
void addController(int id);
void pushObject(std::vector<std::unique_ptr<ChimpObject>>& objects, SDL_Texture* texture, SDL_Rect& texRect,
                SDL_Rect& collRect, SDL_Renderer* renderer, int x, int y, int tilesX, int tilesY);
void pushMobile(std::vector<std::unique_ptr<ChimpObject>>& objects, SDL_Texture* texture, SDL_Rect& texRect,
                SDL_Rect& collRect, SDL_Renderer* renderer, int x, int y, int tilesX, int tilesY);

int main(int argc, char** argv)
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* healthTex;
    //SDL_Texture* currentHealthTex;
    std::vector<SDL_Texture*> textures;
    std::vector<SDL_Rect> textureRects;
    std::vector<SDL_Rect> collisionRects;
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
    if( !loadChimpTextures(textures, textureRects, collisionRects, renderer) )
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
    ChimpCharacter player(textures[0], textureRects[0], collisionRects[0], renderer, SCREEN_WIDTH>>1, 30, 1, 1, 100,
                          FACTION_PLAYER, FACTION_BADDIES);
    player.setScreenBoundLeft(true);
    player.setScreenBoundRight(true);
    ObjectVector worldObjects;
    ObjectVector backgroundObjects;
    ObjectVector foregroundObjects;
    pushObject(worldObjects, textures[1], textureRects[1], collisionRects[1], renderer, 0, 140, 8, 1);
    pushObject(worldObjects, textures[1], textureRects[1], collisionRects[1], renderer, SCREEN_WIDTH / 10, 0,
               SCREEN_WIDTH / textureRects[1].w + 1, 3);
    pushMobile(worldObjects, textures[2], textureRects[2], collisionRects[2], renderer, -35, 160, 1, 1);
    (*worldObjects.back()).setRunAccel(RUN_ACCEL / 4.0);
    (*worldObjects.back()).runRight();
    pushMobile(worldObjects, textures[2], textureRects[2], collisionRects[2], renderer, SCREEN_WIDTH, 160, 1, 1);
    (*worldObjects.back()).setRunAccel(RUN_ACCEL / 4.0);
    (*worldObjects.back()).runLeft();
    (*worldObjects.back()).setJumper(true);
    (*worldObjects.back()).setJumpImpulse(JUMP_IMPULSE * 0.75);
    //(*worldObjects.back()).setResistanceY(RESISTANCE_Y);
    pushObject(backgroundObjects, textures[4], textureRects[4], collisionRects[4], renderer, 0, -textureRects[4].h + 25,
                SCREEN_WIDTH/textureRects[4].w+1, 1);
    pushObject(foregroundObjects, textures[5], textureRects[5], collisionRects[5], renderer, SCREEN_WIDTH*0.75, 10, 1, 1);
    
    healthTex = renderText(TEXT_HEALTH, font, FONT_COLOR, renderer);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    /*while(!quit)
    {
        SDL_PollEvent(&event);
        if(event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == SDL_CONTROLLER_BUTTON_Y)
            quit = true;
    }
    quit = false;*/
    
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
               
        for(auto& obj : backgroundObjects)
        {
            (*obj).update(backgroundObjects);
            (*obj).render();
        }
        for(auto& obj : worldObjects)
        {
            (*obj).update(worldObjects);
            (*obj).render();
        }
        player.update(worldObjects);
        player.render();
        for(auto& obj : foregroundObjects)
        {
            (*obj).update(foregroundObjects);
            (*obj).render();
        }
        
        int w1, w2, h, x;
        std::string healthString = std::to_string( player.getHealth() );
        SDL_Texture* currentHealthTex = renderText(healthString, font, FONT_COLOR, renderer);
        
        SDL_QueryTexture(healthTex, NULL, NULL, &w1, &h);
        SDL_QueryTexture(currentHealthTex, NULL, NULL, &w2, &h);
        x = (SCREEN_WIDTH - w1 - w2)>>1;
        renderTexture(healthTex, renderer, x, 10);
        renderTexture(currentHealthTex, renderer, x + w1, 10);
        SDL_DestroyTexture(currentHealthTex);
                
        SDL_RenderPresent(renderer);
        
        SDL_Delay(1);
    }
    
    return 0;
}

bool loadChimpTextures(std::vector<SDL_Texture*> &textures, std::vector<SDL_Rect>& texRects,
                       std::vector<SDL_Rect>& collRects, SDL_Renderer* renderer)
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
        sub1 = line.find(TEXTURE_DELIMITER);
        if(sub1 == std::string::npos)
            continue;
        sub2 = line.find(TEXTURE_COMMENT);
        if(sub2 != std::string::npos && sub2 < sub1)
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
        sub2 = line.find(TEXTURE_COMMENT);
        if(sub2 != std::string::npos && sub2 < sub1)
            continue;
        
        ++sub1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        textures.push_back( loadTexture(ASSETS_PATH + line.substr(sub1, sub2-sub1), renderer) );
        
        if(textures.back() == nullptr)
            return false;
        
        texRects.push_back( SDL_Rect() );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        texRects.back().x = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        texRects.back().y = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        texRects.back().w = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        texRects.back().h = std::stoi( line.substr(sub1, sub2-sub1) );
        
        collRects.push_back( SDL_Rect() );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        collRects.back().x = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        collRects.back().y = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        collRects.back().w = std::stoi( line.substr(sub1, sub2-sub1) );
        
        sub1 = sub2 + 1;
        sub2 = line.find(TEXTURE_DELIMITER, sub1);
        collRects.back().h = std::stoi( line.substr(sub1, sub2-sub1) );
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

void pushObject(std::vector<std::unique_ptr<ChimpObject>>& objects, SDL_Texture* texture, SDL_Rect& texRect,
                SDL_Rect& collRect, SDL_Renderer* renderer, int x, int y, int tilesX, int tilesY)
{
    objects.push_back(std::unique_ptr<ChimpObject>( new ChimpObject(texture, texRect, collRect, renderer, x, y, tilesX,
                                                                    tilesY) ));
}

void pushMobile(std::vector<std::unique_ptr<ChimpObject>>& objects, SDL_Texture* texture, SDL_Rect& texRect,
                SDL_Rect& collRect, SDL_Renderer* renderer, int x, int y, int tilesX, int tilesY)
{
    objects.push_back(std::unique_ptr<ChimpMobile>( new ChimpMobile(texture, texRect, collRect, renderer, x, y, tilesX,
                                                                    tilesY) ));
}


































