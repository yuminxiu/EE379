#include "ship.h"
#include "constants.h"


void init_ship(struct Ship *s){
  s->active = false;

  s-> pos_x=0;
  s-> pos_y = 0;
  s-> dx = 0;

  s-> spawn_timer = 0;

  s-> direction= 1; 
}

void spawn_ship(struct Ship *s, int direction){
  s->active = true;
  s->direction = direction;
  s->dx = s->direction * SHIP_SPEED;

  s-> pos_y = 20; // near top of screen

  if (direction == 1){
    //moving left -> right
      s->pos_x = -SHIP_WIDTH;}
  else { 
    //moving right -> left
    s->pos_x = SCREEN_WIDTH;
  }
}



void ship_move(struct Ship *s){
    if (!s->active){
      return;
    }

  s-> pos_x += s->dx;

  if (s->pos_x > SCREEN_WIDTH || s->pos_x + SHIP_WIDTH <0){
      s-> active = false;
  }
}

void update_ship(struct Ship *s){
  if (!s->active){
    return;
      }

ship_move(s);

}

  
