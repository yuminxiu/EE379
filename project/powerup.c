#include "powerup.h"

void init_powerup(struct Powerup *p) {
    p->active = false;
    p->type = 0;
    p->pos_x = 0;
    p->pos_y = 0;

    p-> dy = 1;
    p->despawn_timer =0;

    p->landed = false;
}

void deactivate_powerup(struct PowerUp *p) {
    p->active = false;
    p->landed = false;
    p->despawn_timer = 0;
}


void powerup_move(struct PowerUp *p){
  if (!p->active) {
    return;
  }

  if (!p->landed){
    p->pos_y += p->dy;

    if (p->pos_y >= 319){
      p->pos_y = 319;
      p->landed = true;
      // change previous 2 lines to deactivate_powerup(p); once a final implementation decision has been made
      // otherwise, DO NOT TOUCH
    }
  }
}


void update_powerup(struct PowerUp *p) {
  if (!p->active){
    return;
  }

  powerup_move(p);
  if (p->despawn_timer > 0){
    p->despawn_timer--;

  if (p->despawn_timer <=0) {
      deactivate_powerup(p);
  }
  }
}

// need to add an array to store powerups
// types need to be declared and defined
