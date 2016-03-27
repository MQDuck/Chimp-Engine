#ifndef CHIMPCONSTANTS_H
#define CHIMPCONSTANTS_H

#include <string>
#include <SDL2/SDL.h>

static const int
    SCREEN_WIDTH           = 800,
    SCREEN_HEIGHT          = 600,
    JOYSTICK_DEAD_ZONE     = 8000,
    FONT_SIZE              = 24;
                                 
static const float
    RUN_IMPULSE            = 2.5,  // magnitude of x impulse given when mobile begins running with x velocity near zero
    RUN_ACCEL              = 0.4,  // magnitude of base x acceleration while running
    JUMP_IMPULSE           = -20,  // y impulse given when mobile jumpes from standing position
    DOUBLE_JUMP_FRACTION   = 0.75, // y velocity is replaced by the product of this and JUMP_IMPULSE on double jump
    JUMP_ACCEL             = -1.5, // player y acceleration caused by holding the jump button before falling
    GRAVITY                = 1.6,  // this is added to y acceleration when not standing
    STOP_FACTOR            = 0.9,  // x velocity scales by this when not running
    SPRINT_FACTOR          = 2.0,  // x acceleration scales by this when sprinting
    RESISTANCE_X           = 0.05, // x acceleration is reduced by the product of this and x velocity
    RESISTANCE_Y           = 0.1,  // y acceleration is reduced by the product of this and y velocity
    APPROX_ZERO_Y_FACTOR   = 0.90;

static /*const*/ std::string
    TEXTURE_DELIMITER      = ";",
    ASSETS_PATH            = "assets/",
    TEXTURE_METADATA_FILE  = ASSETS_PATH + "texture_data",
    FONT_FILE              = "LiberationSans-Regular.ttf",
    CONTROLLER_MAP_FILE    = "gamecontrollerdb",
    TEXT_HEALTH            = "Health: ";

static const SDL_Color
    FONT_COLOR             = {0, 0, 0, 255};

// Factions::
static const int
    FACTION_PLAYER         = 1<<0,
    FACTION_BADDIES        = 1<<1;

#endif // CHIMPCONSTANTS_H
