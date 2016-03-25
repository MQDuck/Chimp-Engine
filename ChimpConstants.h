#ifndef CHIMPCONSTANTS_H
#define CHIMPCONSTANTS_H

static const int
    PLAYER_WIDTH           = 68,
    PLAYER_HEIGHT          = 97,
    PLATFORM_WIDTH         = 4,
    PLATFORM_HEIGHT        = 2,
    SCREEN_WIDTH           = 800,
    SCREEN_HEIGHT          = 600,
    JOYSTICK_DEAD_ZONE     = 8000;

static const float
    RUN_IMPULSE            = 5,
    RUN_ACCEL              = 2,
    JUMP_IMPULSE           = -20,
    DOUBLE_JUMP_IMPULSE    = JUMP_IMPULSE * 2 / 3,
    JUMP_ACCEL             = -1.8,
    GRAVITY                = 2.0,
    STOP_FACTOR            = 0.9,
    RESISTANCE_X           = 0.25,
    RESISTANCE_Y           = 0.1,
	APPROX_ZERO            = RUN_IMPULSE / 4;

// Derived constants:

static const float
    JUMP_ACCEL_NET = JUMP_ACCEL + GRAVITY;

#endif // CHIMPCONSTANTS_H
