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
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <cmath>
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
    
    if(SDL_Init(SDL_INIT_EVERYTHING & ~SDL_INIT_HAPTIC) != 0)
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
    
    
    SDL_Rect playerTexRect, playerLocRect;
    SDL_Event e;
    playerTexRect.x = 0;
    playerTexRect.y = 0;
    playerTexRect.w = PLAYER_WIDTH;
    playerTexRect.h = PLAYER_HEIGHT;
    playerLocRect.x = (SCREEN_WIDTH - PLAYER_WIDTH) / 2;
    playerLocRect.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
    playerLocRect.w = PLAYER_WIDTH;
    playerLocRect.h = PLAYER_HEIGHT;
    ChimpMobile player(playerTex, playerTexRect, renderer, SCREEN_WIDTH>>1, 0);
    bool quit = false;
    std::chrono::high_resolution_clock::time_point t1, t2;
    float accelY = 0;
    float accelX = 0;
    float velocityX = 0;
    float velocityY = 0;
    bool keyJumpPressed = false;
    //bool keyLeftPressed = false;
    //bool keyRightPressed = false;
    bool running = false;
    bool doubleJumped = false;
    
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    t1 = std::chrono::high_resolution_clock::now();
    while(!quit)
    {
        t2 = std::chrono::high_resolution_clock::now();
        int duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 10;
        t1 = t2;
        
        while ( SDL_PollEvent(&e) )
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
                continue;
            }
            if (e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    if( approxZero(velocityX) )
                    {
                        //cout << "impulse" << endl;
                        velocityX += RUN_IMPULSE;
                    }
                    velocityX += (RUN_ACCEL - velocityX * RESISTANCE_X) * duration;
                    running = true;
                    break;
                case SDLK_LEFT:
                    if( approxZero(velocityX) )
                    {
                        //cout << "impulse" << endl;
                        velocityX -= RUN_IMPULSE;
                    }
                    velocityX += (-RUN_ACCEL - velocityX * RESISTANCE_X) * duration;
                    running = true;
                    break;
                case SDLK_UP:
                case SDLK_SPACE:
                    //if(!keyJumpPressed && playerLocRect.y == SCREEN_HEIGHT - PLAYER_HEIGHT)
                    if(!keyJumpPressed && !doubleJumped)
                    {
                        if(playerLocRect.y < SCREEN_HEIGHT - PLAYER_HEIGHT)
                        {
                            doubleJumped = true;
                            velocityY = DOUBLE_JUMP_IMPULSE;
                        }
                        else
                            velocityY = JUMP_IMPULSE;
                        accelY = JUMP_ACCEL_NET;
                        keyJumpPressed = true;
                    }
                    break;
                }
            }
            else if (e.type == SDL_KEYUP)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    if(velocityX > 0)
                    {
                        accelX = 0;
                        running = false;
                    }
                    break;
                case SDLK_LEFT:
                    if(velocityX < 0)
                    {
                        accelX = 0;
                        running = false;
                    }
                    break;
                case SDLK_UP:
                case SDLK_SPACE:
                    keyJumpPressed = false;
                    if(velocityY < 0)
                        accelY = GRAVITY;
                    break;
                }
            }
        }
        
        playerLocRect.x += round(velocityX * duration); // Rounding might no be necessary
        if(playerLocRect.y > SCREEN_HEIGHT - PLAYER_HEIGHT)
        {
            playerLocRect.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
            velocityY = 0;
            accelY = 0;
            doubleJumped = false;
        }
        else
            playerLocRect.y += round(velocityY * duration);
        
        if(velocityX != 0 && running == false)
            velocityX *= STOP_FACTOR;
            
        if(velocityY > 0)
            accelY = GRAVITY;
        
        velocityY += (accelY - velocityY * RESISTANCE_Y) * duration;
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, playerTex, &playerTexRect, &playerLocRect);
        player.render();
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    
    return 0;
}



















