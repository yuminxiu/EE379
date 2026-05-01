#include "player.h"
#include "constants.h"
// Player Initialization

void init_player(struct Player *player){
  player->lives = 3;

  player->pos_x = 120;
  player->pos_y = PLAYER_START_Y;

  player->can_shoot = true;
  player->shoot_timer = 0;

  player->hit = false;
  player->shield_active = false;
  player->shield_timer = 0;

  player->score_mult_active = false;
  player->score_mult_timer = 0;

  player->bullet_power_type = BULLET_POWER_NONE;
  player->bullet_power_timer = 0;
}

void update_player(struct Player *player){  

  if(!player->can_shoot){
    player->shoot_timer--;

    if (player->shoot_timer <= 0){
        player->can_shoot = true;
        player->shoot_timer = 0;
    }
  }

  if (player->shield_active) {
      player->shield_timer--;

      if (player->shield_timer <= 0) {
          player->shield_active = false;
          player->shield_timer = 0;
      }
  }

  if (player->score_mult_active) {
      player->score_mult_timer--;

      if (player->score_mult_timer <= 0) {
          player->score_mult_active = false;
          player->score_mult_timer = 0;
      }
  }

  if (player->bullet_power_type != BULLET_POWER_NONE) {
      player->bullet_power_timer--;

      if (player->bullet_power_timer <= 0) {
          player->bullet_power_type = BULLET_POWER_NONE;
          player->bullet_power_timer = 0;
      }
  }

  player->hit = false; // reset hit flag

}

void player_take_hit(struct Player *player) {
    if (player->shield_active) {
        player->shield_active = false;
        player->shield_timer = 0;
        return;
    }

    player->lives--;
    player->hit = true;
}

void player_move(struct Player *player, int dx){
  player->pos_x += dx;

  // screen bounds
    if (player->pos_x < 0) {
        player->pos_x = 0;
    }

    if (player->pos_x > SCREEN_WIDTH - PLAYER_WIDTH) {
        player->pos_x = SCREEN_WIDTH - PLAYER_WIDTH;
    }
}


void player_shoot(struct Player *player, struct Bullet bullets[], int max_bullets){

  if (!player->can_shoot){
    return;
  }

  int x = player->pos_x + PLAYER_WIDTH / 2;
  int y = player->pos_y;
  
  if (player->power_type == POWERUP_TRIPLE_SHOT) {
    //center
    spawn_bullet(bullets, max_bullets, x,y,0, PLAYER_BULLET_SPEED, BULLET_NORMAL, OWNER_PLAYER);

    // left

    spawn_bullet(bullets, max_bullets, x, y, -1, PLAYER_BULLET_SPEED, BULLET_NORMAL, OWNER_PLAYER);

    // right

    spawn_bullet(bullets, max_bullets, x, y, 1, PLAYER_BULLET_SPEED, BULLET_NORMAL, OWNER_PLAYER);
  }

  else if (player->power_type == POWERUP_LASER) {
    spawn_bullet(bullets, max_bullets, x,y,0, PLAYER_BULLET_SPEED, BULLET_LASER, OWNER_PLAYER);
  }

  else {
    // normal shot
  spawn_bullet(bullets, max_bullets, x, y, 0, PLAYER_BULLET_SPEED, BULLET_NORMAL, OWNER_PLAYER); // values to be adjusted
// spawns bullet at player pos w/o horizontal motion, only up. type 0, owner 0
  }

  player->can_shoot = false;
  player->shoot_timer = PLAYER_SHOOT_COOLDOWN; // random value that'll probably be changed later
}
