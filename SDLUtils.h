#ifndef SDLUTILS
#define SDLUTILS

#include <iostream>
#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void logSDLError(std::ostream& os, const std::string& msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* const ren);
void renderTexture(SDL_Texture* tex, SDL_Renderer* const rend, SDL_Rect dst, SDL_Rect* clip = nullptr);
void renderTexture(SDL_Texture* tex, SDL_Renderer* const rend, int x, int y, SDL_Rect* clip = nullptr);
SDL_Texture* renderText(const std::string& message, TTF_Font* const font, const SDL_Color color,
                        SDL_Renderer* const renderer);

#endif // SDLUTILS

