#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

struct Player {
  int lives;
  int pos_x;
  int pos_y;

  bool can_shoot; // true = allowed to shoot, false = waiting (cooldown)
  int shoot_timer; // shooting cooldown

  bool hit; // true = recently hit

  int power_type; // 0 = none
  int power_timer; // duration
};


void init_player(struct Player *player);
void update_player(struct Player *player);
void player_move(struct Player *player, int dx);
void player_shoot(struct Player *player);

#endif
