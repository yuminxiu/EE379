#ifndef BOSSBEAM_H
#define BOSSBEAM_H

#include <stdbool.h>
#include "constants.h"
struct BossBeam{
  bool active;
  bool firing;
  int x;
  int y;
  int width;
  int height;

  int warning_timer; 
  int fire_timer;
};

void init_boss_beam(struct BossBeam *b);
void init_boss_beam_arr(struct BossBeam beams[], int size);
void start_beam_cage(struct BossBeam beams[], int size);
void update_boss_beam(struct BossBeam *b);
void update_boss_beam_arr(struct BossBeam beams[], int size);

void deactivate_boss_beam(struct BossBeam *b);

#endif
