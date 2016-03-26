#include "ChimpCharacter.h"

ChimpCharacter::ChimpCharacter(SDL_Texture* tex, SDL_Rect& texRect, SDL_Renderer* rend, const int positionX,
                               const int positionY, const int tilX, const int tilY, int maxH, int frnds, int enms)
    : ChimpMobile(tex, texRect, rend, positionX, positionY, tilX, tilY), maxHealth(maxH), friends(frnds), enemies(enms)
{
    health = maxHealth;
}
