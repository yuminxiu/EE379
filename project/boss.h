#ifndef BOSS_H
#define BOSS_H

#include <stdbool.h>

struct Boss {
  bool active;
  int hp;
  int max_health;
  int timer_pattern;
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
void boss_shoot(struct Boss *boss, struct Bullet bullets[], int max_bullets);

#endif
