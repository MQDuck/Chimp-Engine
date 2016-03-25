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
#include <cmath>
#include <vector>
#include "SDLUtils.h"
#include "cleanup.h"
#include "ChimpConstants.h"
#include "ChimpObject.h"
#include "ChimpMobile.h"

using std::cout;
using std::endl;


inline bool approxZero(const float f) { return f > -APPROX_ZERO && f < APPROX_ZERO; }

int main(int argc, char **argv)
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* playerTex;
    SDL_Texture* platformTex;
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
    playerTex = loadTexture("assets/player.png", renderer);
    if(playerTex == nullptr)
    {
        cleanup(window, renderer, playerTex);
        SDL_Quit();
    }
    platformTex = loadTexture("assets/platform.png", renderer);
    if(platformTex == nullptr)
    {
        cleanup(window, renderer, playerTex, platformTex);
        SDL_Quit();
    }
    if(SDL_GameControllerAddMappingsFromFile("gamecontrollerdb") == -1)
        logSDLError(std::cout, "GameControllerAddMappingsFromFile");
    /*for(int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        SDL_GameController *pad = SDL_GameControllerOpen(i);
        SDL_Joystick *joy = SDL_GameControllerGetJoystick( pad );
    }*/
    if(SDL_NumJoysticks() > 0)
    {
        controller = SDL_JoystickOpen(0);
        if(!controller)
            logSDLError(std::cout, "JoystickOpen");
    }
    
    SDL_Event e;
    bool quit = false;
    bool keyJumpPressed = false;
    SDL_Rect playerTexRect, platformTexRect;
    playerTexRect.x = 0;
    playerTexRect.y = 0;
    playerTexRect.w = PLAYER_WIDTH;
    playerTexRect.h = PLAYER_HEIGHT;
    platformTexRect.x = 0;
    platformTexRect.y = 0;
    platformTexRect.w = PLATFORM_WIDTH*5;
    platformTexRect.h = PLATFORM_HEIGHT*5;
    ChimpMobile player(playerTex, playerTexRect, renderer, SCREEN_WIDTH>>1, 30, 1, 1);
    std::vector<ChimpObject> worldObjects;
    worldObjects.push_back( ChimpObject(platformTex, platformTexRect, renderer, 0, 100, 8, 1) );
    worldObjects.push_back( ChimpObject(platformTex, platformTexRect, renderer, 0, 0, SCREEN_WIDTH/(PLATFORM_WIDTH*5)+1, 3) );
    
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



















