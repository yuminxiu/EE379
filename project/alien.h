#ifndef ALIEN_H
#define ALINE_H

#include <stdbool.h>
#include "bullets.h"

#define MAX_ALIENS 18 // 3 rows of 6

struct Alien {
  bool active;

  int pos_x;
  int pos_y;
  int row;
  int col;

  int sprite_type;
};

struct Alien_Formation {
  int speed;
  int direction; // -1 = left, +1 = right
  int step_down;
};

void init_alien(struct Alien *alien);
void move_alien(struct Alien *alien, struct Alien_Formation *f);
void update_alien(struct Alien *alien, struct Alien_Formation *f);
void alien_shoot(struct Alien *alien, struct Bullet bullets[], int max_bullets);
