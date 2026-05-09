#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "bullet.h"
#include "animation.h"

struct Player {
  int lives;
  int pos_x;
  int pos_y;

  bool can_shoot; // true = allowed to shoot, false = waiting (cooldown)
  int shoot_timer; // shooting cooldown

  bool hit; // true = recently hit

  bool shield_active;
  int shield_timer;

  bool score_mult_active;
  int score_mult_timer;

  int bullet_power_type;
  int bullet_power_timer;
};


void init_player(struct Player *player);
void update_player(struct Player *player);
void player_move(struct Player *player, int dx);
void player_shoot(struct Player *player, struct Bullet bullets[], int max_bullets);
void player_take_hit(struct Player *player);
#endif
