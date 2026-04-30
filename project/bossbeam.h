#ifndef BOSSBEAM_H
#define BOSSBEAM_H

#include <stdbool.h>

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
void beam_cage(struct BossBeam beams[], int size);
void update_boss_beam(struct BossBeam *beam);
void update_boss_beam_arr(struct BossBeam beams[], int size);

void deactivate_boss_beam(struct BossBeam *beam);

#endif
