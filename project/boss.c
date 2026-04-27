#include "boss.h"
#include "constants.h"

//Boss initialization

void init_boss(struct Boss *boss) { 
  boss->active = false; //inactive
  boss-> hp = 100;
  boss-> max_hp = 100;
 
  boss-> pattern_timer = 0;
  boss-> pattern_state = 0;

  boss-> width = boss_width;
  boss-> height = boss_height;

  boss->pos_x =88;
  boss->pos_y = 40;
  boss->dx = boss_speed;
  boss->dy = 0;
} // all values will be adjusted later


void move_boss(struct Boss *boss) {
    if(!boss->active){
        return;
    }

    boss->pos_x += boss->dx;
    boss->pos_y += boss->dy;

    if(boss->pos_x + boss->width >= screen_width){
      boss->pos_x = screen_width - boss->width;
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
