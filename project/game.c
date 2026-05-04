#include "game.h"

#include "constants.h"
#include "player.h"
#include "score.h"
#include "boss.h"
#include "alien.h"
#include "render.h"
#include "powerup.h"
#include "collision.h"
#include "ship.h"
#include "bullet.h"
#include "input.h"
#include <stdlib.h>

static void update_timers(void); // static makes it so only this file can use these functions
static void handle_input_playing(void);
static void update_entities(void);
static void handle_spawning(void);
static void handle_collisions(void);
static void clear_wave_check(void);
static void handle_alien_shooting(void);
static void start_boss_stage(void);

static bool prev_pause = false;

struct Game_State game;
struct Player player;
struct Boss boss;
struct Bullet bullets[MAX_BULLETS];
struct Alien aliens[MAX_ALIENS];
struct Alien_Formation f;
struct Ship ship;
struct PowerUp powerups[MAX_POWERUPS];
struct Score_Sys sc;
struct Input input;

#define MAX_WAVE 3


void init_game(void){
  game.mode = MODE_START;
  game.boss_stage = false; 
  game.wave = 1;

  game.timers.frame_count = 0;
  game.timers.seconds_count = 0;
  game.timers.ship_spawn_timer = 0;
  game.timers.next_ship_spawn = (rand() % 300) + 300; // roughly 10 -20 seconds
  game.timers.powerup_spawn_timer = 0;
  game.timers.next_powerup_spawn = (rand() % 300) + 200; // roughly 7-17 seconds

  game.timers.wave_transition_timer = 0;

  prev_pause  = false;

  init_player(&player);
  init_alien_formation(&f);
  init_alien_arr(aliens, MAX_ALIENS);
  init_bullet_arr(bullets, MAX_BULLETS);
  init_ship(&ship);
  init_score_sys(&sc);
  init_boss(&boss);
  init_powerup_arr(powerups, MAX_POWERUPS);
  init_input(&input);
}


void update_game(void){
  update_input(&input);

  bool paused_pressed = input.pause && !prev_pause;
  prev_pause = input.pause;

  if (game.mode == MODE_START){

    if (input.cheat){
     start_boss_stage();
      game.mode = MODE_PLAYING;
      return;
    }

    if (input.shoot){
    game.mode = MODE_PLAYING;
    }    
    return;
}
  
  if (game.mode == MODE_PLAYING){
      if(pause_pressed){
        game.mode = MODE_PAUSED;
        return;
      }
    
    update_timers();
    handle_input_playing();
    update_entities();
    handle_collisions();
    handle_spawning();
    clear_wave_check();
    return;
  }


  if (game.mode == MODE_PAUSED){

    if (input.cheat){
      start_boss_stage();
      game.mode= MODE_PLAYING;
      return;
    }

    if((input.pause||input.shoot)) && pause_lock ==0){
      game.mode = MODE_PLAYING;
      return;
    }
  return;
}

if(game.mode == MODE_GAMEOVER){

  if (qualify_high_score(&sc,sc.current_score)){
    game.mode = MODE_ENTER_INITIALS;
    return;
  }

  if (input.restart){
    init_game();
    game.mode = MODE_PLAYING;
    return;
  }

  game.mode = MODE_SCOREBOARD;
  return;
}

if (game.mode == MODE_ENTER_INITIALS){
  if(input.shoot) {
    insert_high_score(&sc, sc.current_score, "AAA");
    game.mode = MODE_SCOREBOARD;
  }
    return;
}

  if (game.mode == MODE_SCOREBOARD){
      if (input.restart||input.shoot){
        init_game();
        game.mode = MODE_PLAYING;
      }
    return;
  }

}


// definitions

static void update_timers(void){
      game.timers.frame_count++;
      game.timers.powerup_spawn_timer++;
      game.timers.ship_spawn_timer++;

    if (game.timers.frame_count >= GAME_FPS){
      game.timers.frame_count = 0;
      game.timers.seconds_count++;
    }

}

static void handle_input_playing(void){
  if(input.left){
    player_move(&player, -PLAYER_SPEED);
  }

  if(input.right){
    player_move(&player, PLAYER_SPEED);
  }

  if(input.shoot){
    player_shoot(&player, bullets, MAX_BULLETS);
  }
}

static void update_entities(void){
    update_player(&player);
    update_bullet_arr(bullets, MAX_BULLETS);
    update_powerup_arr(powerups, MAX_POWERUPS);

    if (game.boss_stage){
      update_boss(&boss);
      boss_shoot(&boss, bullets, MAX_BULLETS);
    } else {
      update_alien_arr(aliens, MAX_ALIENS, &f);
      update_ship(&ship);
      handle_alien_shooting();
    }
}

static void handle_alien_shooting(void){
  static int alien_shoot_timer = 0;
  alien_shoot_timer++;

  if (alien_shoot_timer < ALIEN_SHOOT_COOLDOWN) {
    return;
  }

  alien_shoot_timer = 0;

  int start = rand() % MAX_ALIENS;

  for (int i = 0; i < MAX_ALIENS; i++){
    int index = (start +i) % MAX_ALIENS;

    if (aliens[i].active){
      alien_shoot(&aliens[index],bullets, MAX_BULLETS);
      return;
    }
  }
}
static void handle_spawning(void){
  if(game.timers.powerup_spawn_timer > game.timers.next_powerup_spawn){
    int type = (rand() % 5) + 1;

    int x = rand() % (SCREEN_WIDTH - POWERUP_WIDTH); //randomizing x position
    int y = 0; //falls from the top
    
    spawn_powerup(powerups, MAX_POWERUPS, x, y, type, POWERUP_SPEED, POWERUP_DESPAWN_TIME);
    game.timers.powerup_spawn_timer = 0;
    game.timers.next_powerup_spawn = ((rand() % POWERUP_SPAWN_RANGE_SEC) + POWERUP_SPAWN_MIN_SEC) * GAME_FPS;
  }

  if(!ship.active && game.timers.ship_spawn_timer >= game.timers.next_ship_spawn){ 
    
    int direction; //overrides initialization
    
    if(rand() % 2 == 0){
      direction = 1;
    } else { direction = -1;}
    
    spawn_ship(&ship, direction);
    game.timers.ship_spawn_timer = 0;
    game.timers.next_ship_spawn = ((rand() % SHIP_SPAWN_RANGE_SEC) + SHIP_SPAWN_MIN_SEC) * GAME_FPS;
  }
}

static void handle_collisions(void){
  
  for (int i = 0; i <MAX_BULLETS; i++){
    if(!bullets[i].active){
      continue;
    }
//for player bullets hitting aliens, ship or boss
    if(bullets[i].owner == OWNER_PLAYER){
       //bullet vs aliens

      if (!game.boss_stage){
        for (int j = 0; j < MAX_ALIENS; j++){
          if(!aliens[j].active){
            continue;
          }

          if (rect_col(bullet_rect(&bullets[i]), alien_rect(&aliens[j]))){
            aliens[j].active = false;
            add_score(&sc, &player, ALIEN_POINTS);

            if (bullets[i].type != BULLET_PIERCE && bullets[i].type != BULLET_LASER){
              deactivate_bullet(&bullets[i]);
            }
            break;
          }
        }
      }

      //player vs ship

      if(ship.active && rect_col(bullet_rect(&bullets[i]), ship_rect(&ship))){
        ship.active = false;
        add_score(&sc, &player, SHIP_POINTS);
      
        if (bullets[i].type != BULLET_PIERCE && bullets[i].type != BULLET_LASER){
              deactivate_bullet(&bullets[i]);
            }
      }

      // player vs boss

      if (game.boss_stage && boss.active && rect_col(bullet_rect(&bullets[i]), boss_rect(&boss))){
        boss.hp--;
        
        if (bullets[i].type != BULLET_PIERCE && bullets[i].type != BULLET_LASER){
              deactivate_bullet(&bullets[i]);
            }

        if (boss.hp <= 0){
          boss.active = false;
          add_score(&sc, &player, BOSS_POINTS);
        }
      }
    }

    //enemies vs player
      if (bullets[i].owner == OWNER_ALIEN || bullets[i].owner == OWNER_BOSS){

        if (rect_col(bullet_rect(&bullets[i]), player_rect(&player))){

          deactivate_bullet(&bullets[i]);
          player_take_hit(&player);

          if(player.lives <= 0){
            game.mode = MODE_GAMEOVER;
          }
        }

      }
  }
      //beams vs player
      for (int i = 0, i < MAX_BEAMS; i++){
          if (!beams[i].active || !beams[i].firing){
            continue;
          }

          if (rect_col(player_rect(&player), boss_beam_rect(&beams[i]))) {
            player_take_hit(&player);

            if(player.lives <= 0) {
              game.mode = MODE_GAMEOVER;
            }
          }
        }
  //player and powerups

  for (int i = 0; i < MAX_POWERUPS; i++){
    if(!powerups[i].active){
      continue;
    }

    if (rect_col(player_rect(&player),powerup_rect(&powerups[i]))){
      apply_powerup(&powerups[i], &player);
    }
  }
  
}

static void clear_wave_check(void) {
    if (game.boss_stage) {
        if (boss.hp <= 0) {
            game.mode = MODE_GAMEOVER;
        }
        return;
    }

    for (int i = 0; i < MAX_ALIENS; i++) { // loops through every alien, if 1 is active, return. wave does not advance
        if (aliens[i].active) {
            return;
        }
    }

    game.wave++;

    init_bullet_arr(bullets, MAX_BULLETS);
    init_powerup_arr(powerups, MAX_POWERUPS);

    if (game.wave >= MAX_WAVE) {
      start_boss_stage();
    } else {
        init_alien_arr(aliens, MAX_ALIENS);
        init_alien_formation(&f);
    }
}

static void start_boss_stage(void){
  init_bullet_arr(bullets, MAX_BULLETS);
  init_powerup_arr(powerups, MAX_POWERUPS);
  init_alien_arr(aliens,MAX_ALIENS);
  init_ship(&ship);

  game.wave = 3;
  game.boss_stage = true;
  boss.active = true;
}
