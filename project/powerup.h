#ifndef POWERUP_H
#define POWERUP_H

#include <stdbool.h>

#define MAX_POWERUPS 5 // value to be adjusted later

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
void deactivate_powerup(struct PowerUp *p);

void init_powerup_arr(struct PowerUp powerups[], int size);
void update_powerup_arr(struct PowerUp powerups[], int size);
void spawn_powerup(struct PowerUp powerups[], int size, int x, int y, int type, int dy, int despawn_timer);

#endif

