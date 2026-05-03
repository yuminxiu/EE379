#include "boss.h"
#include "constants.h"
#include <stdlib.h> //for rand()

#define SPIRAL_STEPS 16
static int spiral_dx[SPIRAL_STEPS] = { 0, 1, 2, 3, 2, 1, 0, -1, -2, -3, -2, -1, 0, 1, 2, 3};
static int spiral_dy[SPIRAL_STEPS] = { 3, 3, 2, 1, 0, -1, -2, -3, -3, -3, -2, -1, 0, 1, 2, 3};

//Boss initialization

void init_boss(struct Boss *boss) { 
  boss->active = false; //inactive
  boss-> hp = 100;
  boss-> max_hp = 100;
 
  boss-> pattern_timer = 0;
  boss-> pattern_state = 0;

  boss-> width = BOSS_WIDTH;
  boss-> height = BOSS_HEIGHT;

  boss->pos_x =88;
  boss->pos_y = 40;
  boss->dx = BOSS_SPEED;
  boss->dy = 0;
} // all values will be adjusted later


void move_boss(struct Boss *boss) {
    if(!boss->active){
        return;
    }

    boss->pos_x += boss->dx;
    boss->pos_y += boss->dy;

    if(boss->pos_x + boss->width >= SCREEN_WIDTH){
      boss->pos_x = SCREEN_WIDTH - boss->width;
      boss->dx =-1;
    }
}


void boss_shoot_straight(struct Boss *boss, struct Bullet bullets[], int max_bullets) {

    int x = boss->pos_x + boss->width / 2;
    int y = boss->pos_y + boss->height;

    spawn_bullet(bullets, max_bullets, x, y, 0, ENEMY_BULLET_SPEED, BULLET_NORMAL, OWNER_BOSS);
}

void boss_shoot_spread(struct Boss *boss, struct Bullet bullets[], int max_bullets) {

    int x = boss->pos_x + boss->width / 2;
    int y = boss->pos_y + boss->height;

    spawn_bullet(bullets, max_bullets, x, y, -2, ENEMY_BULLET_SPEED, BULLET_NORMAL, OWNER_BOSS);
    spawn_bullet(bullets, max_bullets, x, y,  0, ENEMY_BULLET_SPEED, BULLET_NORMAL, OWNER_BOSS);
    spawn_bullet(bullets, max_bullets, x, y,  2, ENEMY_BULLET_SPEED, BULLET_NORMAL, OWNER_BOSS);
}


void boss_shoot_multispiral(struct Boss *boss, struct Bullet bullets[], int max_bullets) {

    int base = boss->pattern_timer % SPIRAL_STEPS;

    int x = boss->pos_x + boss->width / 2;
    int y = boss->pos_y + boss->height / 2;

    // Spiral 1
    spawn_bullet(bullets, max_bullets, x, y, spiral_dx[base], spiral_dy[base], BULLET_NORMAL, OWNER_BOSS);

    // Spiral 2 (offset half rotation)
    int offset = (base + SPIRAL_STEPS / 2) % SPIRAL_STEPS;

    spawn_bullet(bullets, max_bullets, x, y, spiral_dx[offset], spiral_dy[offset],BULLET_NORMAL, OWNER_BOSS);
}


void boss_shoot_burst(struct Boss *boss, struct Bullet bullets[], int max_bullets) {
    int x = boss->pos_x + boss->width / 2;
    int y = boss->pos_y + boss->height / 2;

    for (int i = 0; i < 8; i++) {
        int dx = (rand() % 5) - 2;  // -2 to +2
        int dy = (rand() % 5) - 2;  // -2 to +2

        if (dx == 0 && dy == 0) {
            dy = 2;
        }

        spawn_bullet(bullets, max_bullets, x, y, dx, dy, BULLET_BURST, OWNER_BOSS);
    }
}

void boss_shoot(struct Boss *boss, struct Bullet bullets[], int max_bullets){
  if (!boss->active){
    return;
  }

    if (boss->pattern_timer % BOSS_SHOOT_COOLDOWN !=0){
      return;
    }

  switch (boss->pattern_state){
    case BOSS_PATTERN_STRAIGHT:
    boss_shoot_straight(boss,bullets,max_bullets);
    break;

    case BOSS_PATTERN_SPREAD:
      boss_shoot_spread(boss,bullets, max_bullets);
    break;

   /* case BOSS_PATTERN_TRACK:
      boss_shoot_track(boss, bullets, max_bullets);
    break; */

    case BOSS_PATTERN_SPIRAL:
      boss_shoot_multispiral(boss, bullets, max_bullets);
    break;

    case BOSS_PATTERN_BURST:
      boss_shoot_burst(boss, bullets, max_bullets);
    break;
    
}
}
void update_boss(struct Boss *boss){
    if (!boss->active){
      return;
    }

    move_boss(boss);
    boss->pattern_timer++;

  // pattern timer placeholder that only loops between 2 states
  if (boss->pattern_timer % 300 == 0) {
    boss->pattern_state++;

    if (boss->pattern_state > BOSS_PATTERN_SPIRAL){
      boss->pattern_state = BOSS_PATTERN_STRAIGHT;
    }
  }

  if (boss->hp <= boss->max_hp/2){
    boss->pattern_state = 1;
  }

  else { boss->pattern_state = 0;
       }
}
}
