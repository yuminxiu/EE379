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

void init_boss_beam(struct BossBeam *t);
void init_boss_beam_arr(struct BossBeam beams[], int max_beams);
void beam_cage(struct BossBeam beams
