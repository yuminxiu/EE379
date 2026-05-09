#ifndef SHIP_H
#define SHIP_H

#include <stdbool.h>

struct Ship {
  bool active;

  int pos_x;
  int pos_y;
  int dx;

  int spawn_timer;

  int direction; 
};

void init_ship(struct Ship *ship);
void update_ship(struct Ship *ship);
void ship_move(struct Ship *ship);
void spawn_ship(struct Ship *ship, int direction);

#endif

