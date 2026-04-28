#include "player.h"
#include "constants.h"
// Player Initialization

void init_player(struct Player *player){
  player->lives = 3;

  player->pos_x = 120;
  player->pos_y = player_start_y;

  player->can_shoot = true;
  player->shoot_timer = 0;

  player->hit = false;

  player->power_type = 0;
  player->power_timer = 0;
}

void update_player(struct Player *player){  

  if(!player->can_shoot){
    player->shoot_timer--;

    if (player->shoot_timer <= 0){
        player->can_shoot = true;
        player->shoot_timer = 0;
    }
  }


  if (player->power_type != POWERUP_NONE) {
    player->power_timer--;
  
    if (player->power_timer <=0){
      player->power_type = POWERUP_NONE;
      player->power_timer = 0;
    }
  }

  player->hit = false; // reset hit flag

}


void player_move(struct Player *player, int dx){
  player->pos_x += dx;

  // screen bounds
  if (player->pos_x < sreen_width) {
    player->pos_x = screen_width;
  }

  if (player->pos_x > screen_width){
    player->pos_x = screen_width;
  }
}


void player_shoot(struct Player *player, struct Bullet bullets[], int max_bullets){

  if (!player->can_shoot){
    return;
  }

  
  if (player->power_type == POWERUP_TRIPLE_SHOT) {
  }

  else if (player->power_type == POWERUP_LASER) {
  }

  else {
    // normal shot
  spawn_bullet(bullets, max_bullets, player->pos_x, player->pos_y, 0, PLAYER_BULLET_SPEED, BULLET_NORMAL, OWNER_PLAYER); // values to be adjusted
// spawns bullet at player pos w/o horizontal motion, only up. type 0, owner 0
  }

  player->can_shoot = false;
  player->shoot_timer = 10; // random value that'll probably be changed later
}
