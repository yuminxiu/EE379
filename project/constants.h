#ifndef CONSTANTS_H
#define CONSTANTS_H


// MTDS screen orientation (portrait)
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

// Gameplay Regions
#define PLAYER_START_Y 280 //PLACEHOLDER VALUE
#define ENEMY_START_Y 40 // PLACEHOLDER VALUE

// ALIENS

#define ALIEN_WIDTH 16 // placeholder value
#define ALIEN_HEIGHT 16 // placeholder value

#define ALIEN_ROWS 3
#define ALIEN_COL 6
#define ALIEN_SPACING_Y 8 // placeholder
#define ALIEN_SPACING_X 8 // placeholder

#define ALIEN_MOVE_SPEED 1 //placeholder value
#define ALIEN_DROP_Y 12 // placeholder value

// SHIP

#define SHIP_WIDTH 16 // placeholder
#define SHIP_HEIGHT 16 // placeholder
#define SHIP_SPEED 2 // placeholder

// BOSS

#define BOSS_WIDTH 64 //placeholder
#define BOSS_HEIGHT 32 // placeholder

#define BOSS_START_Y 20 // placeholder
#define BOSS_SPEED 1 // placeholder

// PLAYER

#define PLAYER_WIDTH 16 //placeholder
#define PLAYER_HEIGHT 16 // placeholder

#define PLAYER_SPEED 3 // placeholder

// BULLETS
#define PLAYER_BULLET_WIDTH 2 // place holder
#define PLAYER_BULLET_HEIGHT 6 // placeholder

#define ALIEN_BULLET_WIDTH 2 // placeholder
#define ALIEN_BULLET_HEIGHT 6 // placeholder

#define BOSS_BULLET_WIDTH 2 // placeholder
#define BOSS_BULLET_HEIGHT 6 // placeholder

#define PLAYER_BULLET_SPEED -4 // place holder
#define ENEMY_BULLET_SPEED 2 //placeholder

// HITBOXES

#define PLAYER_HITBOX_WIDTH 16 // placehodler
#define BOSS_HITBOX_WIDTH 16 // placeholder

// POWERUPS

#define POWERUP_WIDTH 12 //place holder
#define POWERUP_HEIGHT 12 //place holder
#define POWEUP_SPEED 1 // placeholder

#define POWERUP_DESPAWN_TIME 300 // frames

// game limits

#define mAX_BULLETS 20 // place holder
#define MAX_POWERUPS 5

// TIMING
#define PLAYER_SHOOT_COOLDOWN 15 // placeholder
#define ALIEN_SHOOT_COOLDOWN 60 // placeholder
#define BOSS_SHOOT_COOLDOWN 30 //placeholder

//UI

#define UI_BAR_HEIGHT 16 // placeholder
#define BOSS_HP_BAR_WIDTH 150 // placeholder
#define BOSS_HP_BAR_HEIGHT 8 // placeholder

#endif
