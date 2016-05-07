#ifndef CHIMPCONSTANTS_H
#define CHIMPCONSTANTS_H

#include <string>
#include <SDL2/SDL.h>

static const int
    SCREEN_WIDTH           = 1200,
    SCREEN_HEIGHT          = 690,
    ACTIVE_ZONE            = 750,   // Mobiles activate when this far from the screen.
    INACTIVE_ZONE          = 1500,  // Mobiles deactivate when this far from the screen
    FOLLOW_ZONE_X          = 350,   // maximum horizontal distance from player to screen edge
    FOLLOW_ZONE_Y          = SCREEN_HEIGHT / 4, // maximum vertical distance from player to screen edge
    JOYSTICK_DEAD_ZONE     = 8000,
    FONT_SIZE              = 24,
    INVULNERABLE_TIME      = 750,  // Character invulnerable time after being damaged in miliseconds
    PIXELS_PER_FRAME_X     = 50,   // for run animation
    PIXELS_PER_FRAME_Y     = 30;   // for jump animation    

static const Uint32
    TIME_PER_FRAME         = 600;  // for idle animation
                                 
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
    APPROX_ZERO_Y_FACTOR   = 1.0,//0.90,
    DAMAGE_VELOCITY        = 20.0, // when a character takes damage from an object, it gains velocity equal to this radially from object's center
    DAMAGE                 = 10.0, // enemy damage
    SCROLL_BACK_FACTOR     = 0.1,  // background window location as a multiple of middle window position
    SCROLL_FORE_FACTOR     = 1.25; // foreground window location as a multiple of middle window position

static /*const*/ std::string
    TEXTURE_DELIMITER      = ";",
    TEXTURE_COMMENT        = "#",
    ASSETS_PATH            = "assets/",
    TEXTURES_FILE          = ASSETS_PATH + "textures",
    TILES_FILE             = ASSETS_PATH + "tiles",
    FONT_FILE              = "LiberationSans-Bold.ttf",
    CONTROLLER_MAP_FILE    = "gamecontrollerdb",
    TEXT_HEALTH            = "Health: ";

static const SDL_Color
    FONT_COLOR             = {0, 0, 0, 255}; // HUD font color

#endif // CHIMPCONSTANTS_H
