#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>

#include "player.h"
#include "bullet.h"
#include "boss.h"
#include "alien.h"
#include "ship.h"
#include "powerup.h"
#include "bossbeam.h"

struct Rect {  // hitbox needed for collisions
    int x;
    int y;
    int width;
    int height;
};

bool rect_col(struct Rect a, struct Rect b);

struct Rect player_rect(struct Player *player);
struct Rect bullet_rect(struct Bullet *bullet);
struct Rect boss_rect(struct Boss *boss);
struct Rect powerup_rect(struct PowerUp *p);
struct Rect alien_rect(struct Alien *alien);
struct Rect ship_rect(struct Ship *s);
struct Rect boss_beam_rect(struct BossBeam *b);

#endif
