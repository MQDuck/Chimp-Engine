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

#include "cleanup.h"
#include "chimp/ChimpGame.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_gamecontroller.h>
#if defined (__gnu_linux__) || defined (_WIN32)
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif
#if defined (__APPLE__) && defined (__MACH__)
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#endif

#include <iostream>
#include <string>
#include <tinyxml2.h>
#include <lua.hpp>

inline void addController(const int id, std::vector<SDL_GameController*>& controllers);
inline void keyDown(const SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed);
inline void keyUp(const SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed);
inline void buttonDown(const SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed);
inline void buttonUp(const SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed);
inline void axisMotion(const SDL_Event& event, chimp::ChimpGame& game);

inline void controllerAdded(const SDL_Event& event, std::vector<SDL_GameController*>& controllers);
void renderTexture(SDL_Texture* const tex, SDL_Renderer* const renderer, const int x, const int y,
                   SDL_Rect* const clip = nullptr);
SDL_Texture* renderText(const std::string& message, TTF_Font* const font, const SDL_Color color,
                        SDL_Renderer* const renderer);
void drawHUD(chimp::ChimpGame& game, SDL_Renderer* const renderer, TTF_Font* font, SDL_Texture* const healthTex);

void resize(SDL_Event& event, SDL_Window* window, SDL_Renderer* const renderer, const chimp::ChimpGame& game);

int main(const int argc, char** argv) // Don't mess with the signature, or else suffer "undefined reference to `SDL_main'" errors on Windows
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::vector<SDL_GameController*> controllers;
    
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER) < 0)
    {
        std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
        return 1;
    }
    window = SDL_CreateWindow("Chimp Out!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(window == nullptr)
    {
        std::cerr << "CreateWindow error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr)
    {
        std::cerr << "CreateRenderer error: " << SDL_GetError() << std::endl;
        cleanup(window);
        SDL_Quit();
        return 1;
    }
    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr << "IMG_Init error: " << SDL_GetError() << std::endl;
        cleanup(window, renderer);
        SDL_Quit();
        return 1;
    }
    if(TTF_Init() != 0)
    {
        std::cerr << "TTF_Init error: " << SDL_GetError() << std::endl;
        cleanup(window, renderer);
        SDL_Quit();
        return 1;
    }
    font = TTF_OpenFont( (ASSETS_PATH + FONT_FILE).c_str(), FONT_SIZE );
    if(font == nullptr)
    {
        std::cerr << "TTF_OpenFont error: " << SDL_GetError() << std::endl;
        cleanup(window, renderer, font);
        SDL_Quit();
        return 1;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Mix_OpenAudio error: " << SDL_GetError() << std::endl;
        cleanup(window, renderer, font);
        SDL_Quit();
        return 1;
    }
    if(SDL_GameControllerAddMappingsFromFile(CONTROLLER_MAP_FILE.c_str()) == -1)
        std::cerr << "GameControllerAddMappingsFromFile error: " << SDL_GetError() << std::endl;
    else
        for(int i = 0; i < SDL_NumJoysticks(); ++i)
            addController(i, controllers);
    
    SDL_Event event;
    bool quit = false;
    bool keyJumpPressed = false;
    chimp::ChimpGame game(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_Texture* healthTex = renderText(TEXT_HEALTH, font, FONT_COLOR, renderer);
    decltype(SDL_GetTicks()) timeLast, timeNow;
    std::string levelFile = ASSETS_PATH + DEFAULT_LEVEL;
    
    if(argc > 1)
    {
        levelFile = argv[1];
        if(levelFile[0] != '/' && !( levelFile[0] == '.' && (levelFile[1] == '.' || levelFile[1] == '/') )) //TODO: make Windows version of this
            levelFile = ASSETS_PATH + levelFile;
    }
    if(game.loadLevel(levelFile) != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Couldn't load level file \"" << levelFile << "\"." << std::endl;
        cleanup(window, renderer, font);
        SDL_Quit();
        return 1;
    }
    
    game.initialize();
    
    timeLast = SDL_GetTicks();
    while(!quit)
    {
        while(SDL_PollEvent(&event))
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
            case SDL_CONTROLLERDEVICEADDED:
                addController(event.cdevice.which, controllers);
                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                    resize(event, window, renderer, game);
                break;
            }
        }
        
        SDL_RenderClear(renderer);
        
        timeNow = SDL_GetTicks();
        /*static double numframes = 0;
        ++numframes;
        std::cout << "FPS current: " << 1000 / float(timeNow-timeLast)
                  << "\tFPS average: " << 1000 * numframes / SDL_GetTicks() << std::endl;*/
        game.update(timeNow - timeLast);
        timeLast = timeNow;
        
        game.render();
        drawHUD(game, renderer, font, healthTex);
        SDL_RenderPresent(renderer);
        if(!game.getPlayer()->isActive())
        {
            SDL_Delay(GAME_OVER_TIME);
            game.reset();
        }
    }
    
    cleanup(window, renderer, font);
    SDL_Quit();
    return 0;
}

inline void addController(const int id, std::vector<SDL_GameController*>& controllers)
{
    if(SDL_IsGameController(id))
        controllers.push_back(SDL_GameControllerOpen(id));
}

inline void keyDown(const SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed)
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
            game.getPlayer()->jump(game);
            keyJumpPressed = true;
        }
        break;
    case SDLK_x:
        game.getPlayer()->sprint();
        break;
    }
}

inline void keyUp(const SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed)
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

inline void buttonDown(const SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed)
{
    if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A && !keyJumpPressed)
    {
        game.getPlayer()->jump(game);
        keyJumpPressed = true;
    }
    else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
        game.getPlayer()->sprint();
}

inline void buttonUp(const SDL_Event& event, chimp::ChimpGame& game, bool& keyJumpPressed)
{
    if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
    {
        game.getPlayer()->stopJumping();
        keyJumpPressed = false;
    }
    else if(event.cbutton.button == SDL_CONTROLLER_BUTTON_X)
        game.getPlayer()->stopSprinting();
}

inline void axisMotion(const SDL_Event& event, chimp::ChimpGame& game)
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

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height and taking a clip of the texture if desired
* If a clip is passed, the clip's width and height will be used instead of
*	the texture's
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture(SDL_Texture* const tex, SDL_Renderer* const renderer, const int x, const int y,
                   SDL_Rect* const clip)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != nullptr)
    {
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, tex, clip, &dst);
}

SDL_Texture* renderText(const std::string& message, TTF_Font* font, SDL_Color color,
                        SDL_Renderer* const renderer)
{
    SDL_Surface* surf = TTF_RenderText_Blended(font, message.c_str(), color);
    if (surf == nullptr)
    {
        std::cerr << "TTF_RenderText error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == nullptr)
        std::cerr << "CreateTexture error: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(surf);
    return texture;
}

void drawHUD(chimp::ChimpGame& game, SDL_Renderer* const renderer, TTF_Font* font, SDL_Texture* const healthTex)
{
    static int oldHealth = -1, w1, w2, h, x;
    static int gameOverX, gameOverY;
    static SDL_Texture* currentHealthTex;
    static SDL_Texture* gameOverTex = [renderer, font]()
    {
        SDL_Texture* tex = renderText(GAME_OVER_TEXT, font, FONT_COLOR, renderer);
        SDL_QueryTexture(tex, nullptr, nullptr, &gameOverX, &gameOverY);
        gameOverX = (SCREEN_WIDTH - gameOverX) >> 1;
        gameOverY = (SCREEN_HEIGHT - gameOverY) >> 1;
        return tex;
    }();
    
    if(oldHealth != game.getPlayer()->getHealth())
    {
        SDL_DestroyTexture(currentHealthTex);
        oldHealth = game.getPlayer()->getHealth();
        currentHealthTex = renderText(std::to_string(oldHealth), font, FONT_COLOR, renderer);
        SDL_QueryTexture(healthTex, nullptr, nullptr, &w1, &h);
        SDL_QueryTexture(currentHealthTex, nullptr, nullptr, &w2, &h);
        x = (SCREEN_WIDTH>>1) - w1;
    }
    
    renderTexture(healthTex, renderer, x, 10);
    renderTexture(currentHealthTex, renderer, x + w1, 10);
    if(!game.getPlayer()->isActive())
        renderTexture(gameOverTex, renderer, gameOverX, gameOverY);
}

void resize(SDL_Event& event, SDL_Window* window, SDL_Renderer* const renderer, const chimp::ChimpGame& game)
{
    static int width = SCREEN_WIDTH, height = SCREEN_HEIGHT;
    
    if(event.window.data2 == height) // only width changed
    {
        width = event.window.data1;
        const float ratioWidth = (float)width / (float)game.getViewWidth();
        height = ratioWidth * game.getViewHeight();
        SDL_RenderSetScale(renderer, ratioWidth, ratioWidth);
    }
    else if (event.window.data1 == width) // only height changed
    {
        height = event.window.data2;
        const float ratioHeight = (float)height / (float)game.getViewHeight();
        width = ratioHeight * game.getViewWidth();
        SDL_RenderSetScale(renderer, ratioHeight, ratioHeight);
    }
    else // both width and height changed, decrease window size to keep correct width/height ratio
    {
        const float ratioWidth = (float)event.window.data1 / (float)game.getViewWidth();
        const float ratioHeight = (float)event.window.data2 / (float)game.getViewHeight();
        if(ratioWidth < ratioHeight)
        {
            width = event.window.data1;
            height = ratioWidth * game.getViewHeight();
            SDL_RenderSetScale(renderer, ratioWidth, ratioWidth);
        }
        else
        {
            height = event.window.data2;
            width = ratioHeight * game.getViewWidth();
            SDL_RenderSetScale(renderer, ratioHeight, ratioHeight);
        }
    }
    SDL_SetWindowSize(window, width, height);
}






























