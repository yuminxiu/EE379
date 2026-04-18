#ifndef BULLET_H
#define BULLET_H

#include <stdbool.h>

#define max_bullets 20 // value can be changed later

struct Bullet {
  int pos_x;
  int pos_y;

  int dy; // speed/direction
  int dx;

  bool active; // true = bullet exists on screen, false = no

  int type; // normal, spread, beam, cluster
  int owner; // player, alien, boss

};

void init_bullet(struct Bullet *bullet);
void init_bullet_arr(struct bullet bullets[], int size); //initializes bullets in an array instead of dynamically creating bullets

void update_bullet(struct Bullet *bullet);
void bullet_move(struct Bullet *bullet);
void update_bullet_arr(struct Bullet bullets[], int size); // loops through bullet array

void deactivate_bullet(struct Bullet *bullet); // marks a slot as unused

void spawn_bullet(struct Bullet bullet[], int size, int x, int y, int dx, int dy,
                  int type, int owner);   // finds inactive slot in array and activates it

#endif
