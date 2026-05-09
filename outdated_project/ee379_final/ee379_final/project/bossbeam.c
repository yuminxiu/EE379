#include "bossbeam.h"


#include <stdlib.h>

void init_boss_beam(struct BossBeam *b){
  b->active = false;
  b->firing = false;
  b->x = 0;
  b->y = 0;
  b->width = 0;
  b->height = 0;

  b->warning_timer = 0;
  b-> fire_timer = 0;
}

void init_boss_beam_arr(struct BossBeam beams[], int size){
  for (int i=0; i <size; i++){
    init_boss_beam(&beams[i]);
  }
}

void deactivate_boss_beam(struct BossBeam *b){
  b->active = false;
  b->firing = false;
  b->warning_timer = 0;
  b->fire_timer = 0;
}

void start_beam_cage(struct BossBeam beams[], int size){
  int safe1= rand() % BEAM_LANES;
  int safe2 = rand() % BEAM_LANES;

  while (safe2 == safe1){
    safe2 = rand() % BEAM_LANES;
  }

  int beam_index = 0;

  for (int lane = 0; lane < BEAM_LANES; lane++){
    if (lane == safe1 || lane == safe2){
      continue;
    }

    if (beam_index >= size){
      return;
    }

    beams[beam_index].active = true;
    beams[beam_index].firing = false;
    beams[beam_index].x = lane * BEAM_LANE_WIDTH;
    beams[beam_index].y = 0;
    beams[beam_index].fire_timer = BEAM_FIRE_TIME;
    beams[beam_index].warning_timer = BEAM_WARNING_TIME;
    beams[beam_index].width = BEAM_LANE_WIDTH;
    beams[beam_index].height = SCREEN_HEIGHT;

    beam_index++;
  }

//clear unused slots

  for (int i = beam_index; i < size; i++){
    deactivate_boss_beam(&beams[i]);
  }
}

void update_boss_beam(struct BossBeam *b){
  if (!b->active){
    return;
  }

  if (!b->firing){
    b->warning_timer--;

    if (b->warning_timer <= 0){
        b->firing = true;
    }

  return;
  }

  b->fire_timer--;
  
  if (b->fire_timer <= 0){
      deactivate_boss_beam(b);
  }
}

void update_boss_beam_arr(struct BossBeam beams[], int size){
  for (int i = 0; i<size; i++){
      update_boss_beam(&beams[i]);
  }
}



