#ifndef POWERUP_H
#define POWERUP_H

#include <stdbool.h>


struct PowerUp {
  bool active;

  int type;

  int pos_x;
  int pos_y;

  int dy;

  int despawn_timer;

  bool landed; //stay on bottom edge of screen until despawn or collision with player
};

void init_powerup(struct PowerUp *p);
void update_powerup(struct PowerUp *p);
void powerup_move(struct PowerUp *p);

#endif

