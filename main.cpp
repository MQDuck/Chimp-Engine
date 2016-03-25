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

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include <vector>
#include <fstream>
#include <string>
#include "SDLUtils.h"
#include "cleanup.h"
#include "ChimpConstants.h"
#include "ChimpObject.h"
#include "ChimpMobile.h"

using std::cout;
using std::endl;


inline bool approxZero(const float f) { return f > -APPROX_ZERO_FLOAT && f < APPROX_ZERO_FLOAT; }
bool loadChimpTextures(std::vector<SDL_Texture*> &textures, std::vector<SDL_Rect> &rects, SDL_Renderer* renderer);

int main(int argc, char **argv)
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> textures;
    std::vector<SDL_Rect> textureRects;
    SDL_Joystick* controller;
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
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
        for(SDL_Texture* tex : textures)
            cleanup(tex);
        cleanup(window, renderer);
        SDL_Quit();
        return 1;
    }
    if(SDL_GameControllerAddMappingsFromFile("gamecontrollerdb") == -1)
        logSDLError(std::cout, "GameControllerAddMappingsFromFile");
    if(SDL_NumJoysticks() > 0)
    {
        controller = SDL_JoystickOpen(0);
        if(!controller)
            logSDLError(std::cout, "JoystickOpen");
    }
    
    SDL_Event e;
    bool quit = false;
    bool keyJumpPressed = false;
    ChimpMobile player(textures[0], textureRects[0], renderer, SCREEN_WIDTH>>1, 30, 1, 1);
    std::vector<ChimpObject> worldObjects;
    worldObjects.push_back( ChimpObject(textures[1], textureRects[1], renderer, 0, 100, 8, 1) );
    worldObjects.push_back( ChimpObject(textures[1], textureRects[1], renderer, 0, 0,
                                        SCREEN_WIDTH / textureRects[1].w + 1, 3) );
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    while(!quit)
    {
        while( SDL_PollEvent(&e) )
        {
            switch(e.type)
            {
            case SDL_QUIT:
            {
                quit = true;
                continue;
            }
            case SDL_KEYDOWN:
            {
                switch(e.key.keysym.sym)
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
                }
                break;
            }
            case SDL_KEYUP:
            {
                switch(e.key.keysym.sym)
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
                }
                break;
            }
            case SDL_JOYBUTTONDOWN:
            {
                cout << "e.jbutton.button = " << int(e.jbutton.button) << endl;
                switch(e.jbutton.button)
                {
                case 2:
                    if(!keyJumpPressed)
                    {
                        player.jump();
                        keyJumpPressed = true;
                    }
                    break;
                }
                break;
            }
            case SDL_JOYBUTTONUP:
            {
                switch(e.jbutton.button)
                {
                case 2:
                    player.stopJumping();
                    keyJumpPressed = false;
                    break;
                }
                break;
            }
            case SDL_JOYAXISMOTION:
            {
                switch(e.jaxis.axis)
                {
                case 0:
                    if(e.jaxis.value > JOYSTICK_DEAD_ZONE)
                    {
                        cout << "right" << endl;
                        player.stopRunning();
                        player.runRight();
                    }
                    else if(e.jaxis.value > -JOYSTICK_DEAD_ZONE)
                    {
                        cout << "left" << endl;
                        player.stopRunning();
                        player.runLeft();
                    }
                    else
                    {
                        cout << "zero" << endl;
                        player.stopRunning();
                    }
                }
            }
            }
        }
        
        SDL_RenderClear(renderer);
        for(ChimpObject& obj : worldObjects)
            obj.render();
        player.render(&worldObjects);
        SDL_RenderPresent(renderer);
        
        SDL_Delay(1);
    }
    
    return 0;
}

bool loadChimpTextures(std::vector<SDL_Texture*> &textures, std::vector<SDL_Rect> &rects, SDL_Renderer* renderer)
{
    std::ifstream data("assets/texture_data");
    std::string line;
    int sub1, sub2;
    
    if( !data.is_open() )
    {
        std::cout << "Couldn't open texture data file.";
        return false;
    }
    std::getline(data, line);
    sub1 = line.find(";") + 1;
    sub2 = line.find(";", sub1);
    int numTextures = std::stoi( line.substr(sub1, sub2-sub1) );
    
    for(int i = 0; i < numTextures; ++i)
    {
        getline(data, line);
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


































