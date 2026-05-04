#ifndef BOSS_H
#define BOSS_H

#include <stdbool.h>
#include "bullet.h"
#include "bossbeam.h"

struct Boss {
  bool active;
  int hp;
  int max_hp;
  int pattern_timer;
  int width;
  int height;
  int pos_x;
  int pos_y;
  int dx;
  int dy;

  int pattern_state;
};

void init_boss(struct Boss *boss);
void update_boss(struct Boss *boss);
void move_boss(struct Boss *boss);
void boss_shoot(struct Boss *boss, struct Bullet bullets[], int max_bullets,struct BossBeam beams[], max_beams);

#endif
