#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <cmath>
#include "SDLUtils.h"
#include "cleanup.h"

using std::cout;
using std::endl;

static const int
    PLAYER_WIDTH   = 68,
    PLAYER_HEIGHT  = 97,
    SCREEN_WIDTH   = 800,
    SCREEN_HEIGHT  = 600;
static const float
    RUN_IMPULSE    = 8,
    RUN_ACCEL      = 2,
    //RUN_SPEED      = 10,
    JUMP_IMPULSE   = -20,
    JUMP_ACCEL     = -1.8,
    GRAVITY        = 2.0,
    STOP_FACTOR    = 0.9,
    RESISTANCE_X   = 0.2,
    RESISTANCE_Y   = 0.1;

// Derived constants:
static const float
    JUMP_ACCEL_NET = JUMP_ACCEL + GRAVITY;

//int playerX = SCREEN_WIDTH / 2;
//int playerY = SCREEN_HEIGHT / 2;

int main(int argc, char **argv)
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* playerTex;
    SDL_Event e;
    bool quit = false;
    SDL_Rect playerTexRect, playerLocRect;
    std::chrono::high_resolution_clock::time_point t1, t2;
    float accelY = 0;
    float accelX = 0;
    float velocityX = 0;
    float velocityY = 0;
    bool keyJumpPressed = false;
    //bool keyLeftPressed = false;
    //bool keyRightPressed = false;
    bool running = false;
    
    playerTexRect.x = 0;
    playerTexRect.y = 0;
    playerTexRect.w = PLAYER_WIDTH;
    playerTexRect.h = PLAYER_HEIGHT;
    playerLocRect.x = (SCREEN_WIDTH - PLAYER_WIDTH) / 2;
    playerLocRect.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
    playerLocRect.w = PLAYER_WIDTH;
    playerLocRect.h = PLAYER_HEIGHT;
    
    if(SDL_Init(SDL_INIT_EVERYTHING & ~SDL_INIT_HAPTIC) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }
    
    window = SDL_CreateWindow("DSMaze", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    playerTex = loadTexture("../assets/player.png", renderer);
    if(playerTex == nullptr)
    {
        cleanup(window, renderer, playerTex);
        SDL_Quit();
    }
    
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
                    if(!running)
                        velocityX += RUN_IMPULSE;
                    velocityX += (RUN_ACCEL - velocityX * RESISTANCE_X) * duration;
                    running = true;
                    break;
                case SDLK_LEFT:
                    if(!running)
                        velocityX -= RUN_IMPULSE;
                    velocityX += (-RUN_ACCEL - velocityX * RESISTANCE_X) * duration;
                    running = true;
                    break;
                case SDLK_UP:
                case SDLK_SPACE:
                    if(!keyJumpPressed && playerLocRect.y == SCREEN_HEIGHT - PLAYER_HEIGHT)
                    {
                        keyJumpPressed = true;
                        velocityY = JUMP_IMPULSE;
                        accelY = JUMP_ACCEL_NET;
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
        
        playerLocRect.x += round(velocityX * duration);
        if(playerLocRect.y > SCREEN_HEIGHT - PLAYER_HEIGHT)
        {
            playerLocRect.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
            velocityY = 0;
            accelY = 0;
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
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    
    return 0;
}


















