# include "bullet.h"

// Bullet Initialization

void init_bullet(struct Bullet *bullet){
  bullet->pos_x = 0;
  bullet->pos_y = 0;
  bullet->dx = 0;
  bullet->dy = 0;
  bullet->active = false;
  bullet->type = 0;
  bullet->owner = 0;
}

void init_bullet_arr(struct bullet bullets[], int size){
  for (int i = 0; i < size; i++) {
    init_bullet(&bullet[i]);
  }
}

void bullet_move(struct Bullet *bullet){
    bullet->pos_x += bullet->dx;
    bullet->pos_y += bullet->dy;
}

void deactivate_bullet(struct Bullet *bullet) {
  bullet->active = false;
}

void update_bullet(struct Bullet *bullet) {
  if (!bullet->active) {
      return;
  }

  bullet_move(bullet);

  // screen bounds

  if (bullet->pos_x < 0 || bullet->pos_x > 319 || bullet->pos_y < 0 || bullet->pos_y > 239){
    for (int i =0, i < size, i++){
      update_bullet(&bullet[i]);
      }
}

void spawn_bullet(struct Bullet bullets[], int size,
                  int x, int y,
                  int dx, int dy,
                  int type, int owner) {
    for (int i = 0; i < size; i++) {
        if (!bullets[i].active) {
            bullets[i].pos_x = x;
            bullets[i].pos_y = y;
            bullets[i].dx = dx;
            bullets[i].dy = dy;
            bullets[i].type = type;
            bullets[i].owner = owner;
            bullets[i].active = true;
            return;
        }
    }
}
