#ifndef GAMETIMER_H
#define GAMETIMER_H

#include <stdbool.h>
#include "timer.h"

struct GameTimer {
  bool active;
  int sec;
  int max_hp;
  int 
  int width;
  int height;
  int pos_x;
  int pos_y;
  int dx;
  int dy;

  int pattern_state;
};

void init_timer(struct GameTimer *timer);
void init_timer_arr(struct GameTimer seconds[], int size);

void update_timer(struct GameTimer *timer);
void update_timer_arr(struct GameTimer seconds[], int size);

void deactivate_timer(struct GameTimer *timer);

void activate_timer(struct GameTimer seconds[], int size, int x, int y, int dx, int dy, int type, int owner);

#endif
