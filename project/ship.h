#ifndef SHIP_H
#define SHIP_H

#include <stdbool.h>

struct Ship {
  bool active;

  int pos_x;
  int pos_y;
  int dx;

  int spawn_timer;

  int direction; // 1 = left, 0 = right
};

void init_ship(struct Ship *s);
void update_ship(struct Ship *s);
void ship_move(struct Ship *s);
void spawn_ship(struct Ship *s);

#endif

