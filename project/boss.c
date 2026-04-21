#include "boss.h"

//Boss initialization

void init_boss(struct Boss *boss) { 
  boss->active = false;
  boss-> hp = 100;
  boss-> max_hp = 100;
 
  boss-> pattern_timer = 0;
  boss-> pattern_state = 0;

  boss-> width = 64;
  boss-> height =32;

  boss->pos_x =88;
  boss->pos_y = 40;
  boss->dx = 1;
  boss->dy = 0;
} // all values will be adjusted later


void move_boss(struct Boss *boss) {
    if(!boss->active){
        return;
    }

    boss->pos_x += boss->dx;
    boss->pos_y += boss->dy;

    if(boss->pos_x + boss->width >=240){
      boss->pos_x = 240 - boss->width;
      boss->dx =-1;
    }
}

void boss_shoot(struct Boss *boss, struct Bullet bullets[], int max_bullets){
  if (!boss->active){
    return;
  }

  spawn_bullet(bullets, max_bullets, boss->pos_x + boss->width/2, boss->pos_y + boss->height,
      0, 2, 0, 2); //single bullet from center
}

void update_boss(struct Boss *boss){
    if (!boss->active){
      return;
    }

    move_boss(boss);
    boss->pattern_timer++;

  // pattern timer placeholder

  if (boss->hp <= boss->max_hp/2){
    boss->pattern_state = 1;
  }

  else { boss->pattern_state = 0;
       }
}
