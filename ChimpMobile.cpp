#include "ChimpMobile.h"

ChimpMobile::ChimpMobile(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX,
                         const int positionY) : ChimpObject(tex, texRect, rend, positionX, positionY)
{
    accelerationX = 0;
    accelerationY = 0;
    velocityX = 0;
    velocityY = 0;
}





