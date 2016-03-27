#ifndef SDLUTILS
#define SDLUTILS

#include <iostream>
#include <utility>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void logSDLError(std::ostream& os, const std::string& msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer* ren);
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, SDL_Rect dst, SDL_Rect* clip = nullptr);
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip = nullptr);
/*SDL_Texture* renderText(const std::string& message, const std::string& fontFile, SDL_Color color, int fontSize,
                        SDL_Renderer* renderer);*/
SDL_Texture* renderText(std::string& message, TTF_Font* font, SDL_Color color,
                        SDL_Renderer* renderer);

#endif // SDLUTILS

