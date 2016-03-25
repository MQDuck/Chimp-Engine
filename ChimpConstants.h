#ifndef CHIMPCONSTANTS_H
#define CHIMPCONSTANTS_H

#include <string>

static const int
    SCREEN_WIDTH           = 800,
    SCREEN_HEIGHT          = 600,
    JOYSTICK_DEAD_ZONE     = 8000,
    APPROX_ZERO_INT        = 9;

static const float
    RUN_IMPULSE            = 5,
    RUN_ACCEL              = 0.4,
    JUMP_IMPULSE           = -20,
    DOUBLE_JUMP_IMPULSE    = JUMP_IMPULSE * 2 / 3,
    JUMP_ACCEL             = -1.8,
    GRAVITY                = 2.0,
    STOP_FACTOR            = 0.9,
    SPRINT_FACTOR          = 2.0,
    RESISTANCE_X           = 0.05,
    RESISTANCE_Y           = 0.1,
	APPROX_ZERO_FLOAT      = RUN_IMPULSE / 4;

static const std::string
    TEXTURE_DELIMITER      = ";",
    ASSETS_PATH            = "assets/",
    TEXTURE_METADATA_FILE  = ASSETS_PATH + "texture_data";

// Derived constants:

static const float
    JUMP_ACCEL_NET = JUMP_ACCEL + GRAVITY;

#endif // CHIMPCONSTANTS_H
