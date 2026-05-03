#include "ship.h"
#include "constants.h"


void init_ship(struct Ship *ship){
  ship->active = false;

  ship-> pos_x=0;
  ship-> pos_y = 0;
  ship-> dx = 0;

  ship-> spawn_timer = 0;

  ship-> direction= 1; 
}

void spawn_ship(struct Ship *ship, int direction){
  ship->active = true;
  ship->direction = direction;
  ship->dx = ship->direction * SHIP_SPEED;

  ship-> pos_y = 20; // near top of screen

  if (direction == 1){
    //moving left -> right
      ship->pos_x = -SHIP_WIDTH;}
  else { 
    //moving right -> left
    ship->pos_x = SCREEN_WIDTH;
  }
}



void ship_move(struct Ship *ship){
    if (!ship->active){
      return;
    }

  ship-> pos_x += ship->dx;

  if (ship->pos_x > SCREEN_WIDTH || ship->pos_x + SHIP_WIDTH <0){
      ship-> active = false;
  }
}

void update_ship(struct Ship *ship){
  if (!ship->active){
    return;
      }

ship_move(s);

}

  
