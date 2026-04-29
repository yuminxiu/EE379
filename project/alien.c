#include "alien.h"
#include "constants.h"


void init_alien(struct Alien *alien){
  alien->pos_x = 0;
  alien->pos_y = 0;
  alien->row = 0;
  alien->col = 0;

  alien->sprite_type = 0 ;
  alien->active = true;
}

void init_alien_formation(struct Alien_Formation *f) {
  f->speed = ALIEN_MOVE_SPEED;
  f->direction = 1; // start moving right
  f->step_down = ALIEN_DROP_Y;
}

void init_alien_arr(struct Alien aliens[], int size){
  int start_x = 30;
  int start_y = ENEMY_START_Y;

  for (int i=0, i <size, i++){
    int row = i/ALIEN_COLS;
    int col = i % ALIEN_COLS;

    aliens[i].active = true;
    aliens[i].row = row;
    aliens[i].col = col;

    aliens[i].pos_x = start_x + col * (ALIEN_WIDTH + ALIEN_SPACING_X);
    aliens[i].pos_y = start_y + col * (ALIEN_HEIGHT + ALIEN_SPACING_Y);

    aliens[i].sprite_type = row;
  }
}

