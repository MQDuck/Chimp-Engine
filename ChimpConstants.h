#ifndef CHIMPCONSTANTS_H
#define CHIMPCONSTANTS_H

#include <string>

static const int
    SCREEN_WIDTH           = 800,
    SCREEN_HEIGHT          = 600,
    JOYSTICK_DEAD_ZONE     = 8000;
                                 
static const float
    RUN_IMPULSE            = 2.5,  // magnitude of x impulse given when mobile begins running with x velocity near zero
    RUN_ACCEL              = 0.4,  // magnitude of base x acceleration while running
    JUMP_IMPULSE           = -20,  // y impulse given when mobile jumpes from standing position
    DOUBLE_JUMP_VELOCITY   = JUMP_IMPULSE * 0.75, // y velocity is replaced by this on double jump
    JUMP_ACCEL             = -1.8, // player y acceleration caused by holding the jump button before falling
    GRAVITY                = 2.0,
    STOP_FACTOR            = 0.9,  // x velocity scales by this when not running
    SPRINT_FACTOR          = 2.0,  // x acceleration scales by this when sprinting
    RESISTANCE_X           = 0.05, // x acceleration is reduced by the product of this and x velocity
    RESISTANCE_Y           = 0.1,  // y acceleration is reduced by the product of this and y velocity
	APPROX_ZERO_FLOAT      = RUN_IMPULSE / 4;

static const std::string
    TEXTURE_DELIMITER      = ";",
    ASSETS_PATH            = "assets/",
    TEXTURE_METADATA_FILE  = ASSETS_PATH + "texture_data";

// Derived constants:

static const int
    APPROX_ZERO_Y          = int( ceil(GRAVITY / RESISTANCE_Y / 2.0) ); // i.e. half terminal Y velocity

static const float
    JUMP_ACCEL_NET         = JUMP_ACCEL + GRAVITY;

// Factions::
static const int
    FACTION_PLAYER         = 1<<0,
    FACTION_BADDIES        = 1<<1;

#endif // CHIMPCONSTANTS_H
