#ifndef CHIMPCHARACTER_H
#define CHIMPCHARACTER_H


#include "ChimpObject.h"
#include "ChimpMobile.h"

class ChimpCharacter : public ChimpMobile
{
private:
    int maxHealth, health, friends, enemies;
    
public:
    ChimpCharacter(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX, const int positionY,
                   const int tilX, const int tilY, int maxH, int frnds, int enms);
};

#endif // CHIMPCHARACTER_H
