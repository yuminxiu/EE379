#include "powerup.h"
#include "constants.h"

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

void apply_powerup(struct PowerUp *p, struct Player *player){
    if(!p->active){
        return;
    }

    switch(p->type) {
        case POWERUP_EXTRA_LIFE:
            if(player-> lives < PLAYER_MAX_LIVES){
                player->lives ++;
            }
                break;
        
        case POWERUP_SCORE_MULT:
            player->score_mult_active = true;
            player->score_mult_timer = SCORE_MULT_TIME;
            break;
        
        case POWERUP_LASER:
            player->bullet_power_type = BULLET_POWER_LASER;
            player->bullet_power_timer = LASER_TIME;
            break;
        
        case POWERUP_SHIELD:
            player->shield_active = true;
            player-> shield_timer = SHIELD_TIME;
            break;
        
        case POWERUP_TRIPLE_SHOT:
            player->bullet_power_type = BULLET_POWER_TRIPLE_SHOT;
            player->bullet_power_timer = TRIPLE_SHOT_TIME;
            break;
    }

    deactivate_powerup(p);
}
