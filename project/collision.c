#include "collision.h"
#include "constants.h"

bool rect_col(struct Rect a, struct Rect b){
  return (
    a.x < b.x + b.width && a.x + a.width > b.x && a.y < b.y + b.height && a.y + a.height > b.y
    );
}

struct Rect player_rect(struct Player *player){
  struct Rect r;

  r.x = player->pos_x;
  r.y = player->pos_y;
  r.width = PLAYER_WIDTH;
  r.height = PLAYER_HEIGHT;

  return r;
}

struct Rect bullet_rect(struct Bullet *bullet){
  struct Rect r;

  r.x = bullet->pos_x;
  r.y = bullet->pos_y;

  if (bullet->owner == OWNER_PLAYER){
  r.width = PLAYER_BULLET_WIDTH;
  r.height = PLAYER_BULLET_HEIGHT;}
  else { r.width = ENEMY_BULLET_WIDTH;
        r.height = ENEMY_BULLET_HEIGHT;
       }
  return r;

}

  return r;
}
