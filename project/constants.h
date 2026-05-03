#ifndef CONSTANTS_H
#define CONSTANTS_H


// MTDS screen orientation (portrait)
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

// FPS

#define GAME_FPS 30
#define TIMER_CLOCK_HZ 100000000
#define TIMER_RESET_VALUE (0xFFFFFFFF - (TIMER_CLOCK_HZ / GAME_FPS))

// 10 frames = .33seconds, 15 = 0.5seconds, 300 = 10 seconds

// Gameplay Regions
#define PLAYER_START_Y 280 //PLACEHOLDER VALUE
#define ENEMY_START_Y 40 // PLACEHOLDER VALUE

// ALIENS

#define ALIEN_WIDTH 16 // placeholder value
#define ALIEN_HEIGHT 16 // placeholder value

#define ALIEN_ROWS 3
#define ALIEN_COLS 6
#define ALIEN_SPACING_Y 8 // placeholder
#define ALIEN_SPACING_X 8 // placeholder
#define MAX_ALIENS (ALIEN_ROWS * ALIEN_COLS)

#define ALIEN_MOVE_SPEED 1 //placeholder value
#define ALIEN_DROP_Y 8 // placeholder value

// SHIP

#define SHIP_WIDTH 16 // placeholder
#define SHIP_HEIGHT 16 // placeholder
#define SHIP_SPEED 2 // placeholder

// BOSS

#define BOSS_WIDTH 64 //placeholder
#define BOSS_HEIGHT 32 // placeholder

#define BOSS_START_Y 20 // placeholder
#define BOSS_SPEED 1 // placeholder

#define BOSS_PATTERN_STRAIGHT 0
#define BOSS_PATTERN_SPREAD 1
#define BOSS_PATTERN_SPIRAL 2
#define BOSS_PATTERN_TRACK 3
#define BOSS_PATTERN_BURST 4


// PLAYER

#define PLAYER_WIDTH 16 //placeholder
#define PLAYER_HEIGHT 16 // placeholder

#define PLAYER_SPEED 3 // placeholder
#define MAX_LIVES 4
#define PLAYER_START_LIVES 3

// BULLETS
#define PLAYER_BULLET_WIDTH 2 // place holder
#define PLAYER_BULLET_HEIGHT 10 // placeholder

#define ALIEN_BULLET_WIDTH 2 // placeholder
#define ALIEN_BULLET_HEIGHT 6 // placeholder

#define BOSS_BULLET_WIDTH 2 // placeholder
#define BOSS_BULLET_HEIGHT 6 // placeholder

#define PLAYER_BULLET_SPEED -5 // place holder
#define ENEMY_BULLET_SPEED 2 //placeholder

// Bullet types

#define BULLET_NORMAL 0
#define BULLET_LASER 1
#define BULLET_PIERCE 2
#define BULLET_ROUND 3
#define BULLET_BURST 4

#define BULLET_POWER_NONE        0
#define BULLET_POWER_LASER       1
#define BULLET_POWER_TRIPLE_SHOT 2
#define BULLET_POWER_PIERCE      3

// OWNERS

#define OWNER_PLAYER 0
#define OWNER_ALIEN 1
#define OWNER_BOSS 2

// HITBOXES

#define PLAYER_HITBOX_WIDTH 12 // placehodler
#define PLAYER_HITBOX_HEIGHT 12 // placeholder
#define BOSS_HITBOX_WIDTH 16 // placeholder

// POWERUPS

#define POWERUP_WIDTH 12 //place holder
#define POWERUP_HEIGHT 12 //place holder
#define POWERUP_SPEED 1 // placeholder

#define POWERUP_DESPAWN_TIME 300 // frames

#define POWERUP_NONE        0
#define POWERUP_EXTRA_LIFE  1
#define POWERUP_SCORE_MULT  2
#define POWERUP_LASER       3
#define POWERUP_SHIELD      4
#define POWERUP_TRIPLE_SHOT 5

#define SCORE_MULT_TIME   600
#define LASER_TIME        300
#define SHIELD_TIME       600
#define TRIPLE_SHOT_TIME  450

// game limits

#define MAX_BULLETS 64
#define MAX_POWERUPS 5

// TIMING
#define PLAYER_SHOOT_COOLDOWN 10 // placeholder
#define ALIEN_SHOOT_COOLDOWN 15 // placeholder
#define BOSS_SHOOT_COOLDOWN 15 //placeholder

//UI

#define UI_BAR_HEIGHT 16 // placeholder
#define BOSS_HP_BAR_WIDTH 150 // placeholder
#define BOSS_HP_BAR_HEIGHT 8 // placeholder

// POINTS

#define ALIEN_POINTS 20
#define SHIP_POINTS 50
#define BOSS_POINTS 500

#define SCORE_MULT 2

//BEAMS

#define MAX_BEAMS 8
#define BEAM_LANES 8
#define SAFE_LANES 2

#define BEAM_LANE_WIDTH (SCREEN_WIDTH / BEAM_LANES)
#define BEAM_WARNING_TIME 90 //place holder
#define BEAM_FIRE_TIME 45 //place holder

//Spawning

#define SHIP_SPAWN_MIN_SEC       10
#define SHIP_SPAWN_RANGE_SEC     10

#define POWERUP_SPAWN_MIN_SEC    7
#define POWERUP_SPAWN_RANGE_SEC  10

#endif
