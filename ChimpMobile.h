#ifndef CHIMPMOBILE_H
#define CHIMPMOBILE_H

#include "ChimpObject.h"

class ChimpMobile : public ChimpObject
{
private:
    float accelerationX, accelerationY, velocityX, velocityY;
    
public:
    ChimpMobile(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX, const int positionY);
};

#endif // CHIMPMOBILE_H
