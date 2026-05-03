#include "collision.h"
#include "constants.h"

bool rect_col(struct Rect a, struct Rect b){
  return (
    a.x < b.x + b.width && a.x + a.width > b.x && a.y < b.y + b.height && a.y + a.height > b.y
    );
}

struct Rect player_rect(struct Player *player){
  struct Rect r;

  r.x = player->pos_x + (PLAYER_WIDTH - PLAYER_HITBOX_WIDTH)/2;
  r.y = player->pos_y + (PLAYER_HEIGHT - PLAYER_HITBOX_HEIGHT)/2;
  r.width = PLAYER_HITBOX_WIDTH;
  r.height = PLAYER_HITBOX_HEIGHT;

  return r;
}

struct Rect bullet_rect(struct Bullet *bullet){
  struct Rect r;

  r.x = bullet->pos_x;
  r.y = bullet->pos_y;

  if (bullet->owner == OWNER_PLAYER){
  r.width = PLAYER_BULLET_WIDTH;
  r.height = PLAYER_BULLET_HEIGHT;}
  else { r.width = ALIEN_BULLET_WIDTH;
        r.height = ALIEN_BULLET_HEIGHT;
       }
  return r;

}

  struct Rect alien_rect(struct Alien *alien) {
    struct Rect r;

    r.x = alien->pos_x;
    r.y = alien->pos_y;
    r.width = ALIEN_WIDTH;
    r.height = ALIEN_HEIGHT;

    return r;
  }

struct Rect boss_rect(struct Boss *boss){
  struct Rect r;

  r.x = boss->pos_x;
  r.y = boss->pos_y;
  r.width = BOSS_WIDTH;
  r.height = BOSS_HEIGHT;

  return r;
}

struct Rect ship_rect(struct Ship *s){
  struct Rect r;
  r.x = s->pos_x;
  r.y = s->pos_y;
  r.width = SHIP_WIDTH;
  r.height = SHIP_HEIGHT;

  return r;
}

struct Rect powerup_rect(struct PowerUp *p){
  struct Rect r;

  r.x = p->pos_x;
  r.y = p->pos_y;
  r.width = POWERUP_WIDTH;
  r.height = POWERUP_HEIGHT;

  return r;
}
