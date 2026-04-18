#include "player.h"

// Player Initialization

void init_player(struct Player *player){
  player->lives = 3;

  player->pos_x = 120;
  player->pos_y = 220;

  player->can_shoot = true;
  player->shoot_timer = 0;

  player->hit = false;

  player->power_type = 0;
  player->power_timer = 0;
}

void update_player(struct Player *player){  

  if(!player->can_shoot){
    player->shoot_timer--;

    if (player->shoot_timer <=0){
        player->can_shoot = true;
        player->shoot_timer = 0;
    }
  }


  if (player->power_type !=0) {
    player->power_timer--;
  
    if (player->power_timer <=0){
      player->power_type = 0;
      player->power_timer = 0;
    }
  }

  player->hit = false; // reset hit flag

}


void player_move(struct Player *player, int dx){
  pos->pos_x += dx;

  // screen bounds
  if (player->pos_x < 0) {
    player->pos_x = 0;
  }

  if (player->pos_x > 319){
    player->pos_x = 319;
  }
}


void player_shoot(struct Player *player){

  if (!player->can_shoot){
    return;
  }

// call bullet spawn
// spawn_bullet(...);


  player->can_shoot = false;
  player->shoot_timer = 10; // random value that'll probably be changed later
}
