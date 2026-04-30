#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>
#include "timer.h"

struct Timer {
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

void init_timer(struct Timer *timer);
void init_timer_arr(struct Timer seconds[], int size);

void update_timer(struct Timer *timer);
void update_timer_arr(struct Timer seconds[], int size);

void deactivate_timer(struct Timer *timer);

void activate_timer(struct Timer seconds[], int size, int x, int y, int dx, int dy, int type, int owner);

#endif
