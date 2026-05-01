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



void init_game(void){
  game.mode = MODE_START;
  game.boss_stage = false; 
  game.wave = 1;

  game.timers.frame_count = 0;
  game.timers.seconds_count = 0;
  game.timers.event_timer = 0;
  game.timers.powerup_spawn_timer = 0;

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

  if (game.mode == MODE_START){
    printf("Press Space to Start!");

    if (input.shoot){
    game.mode = MODE_PLAYING;
    }    
    return;
}
  if (game.mode == MODE_PLAYING){
      if(input.pause){
        game.mode = MODE_PAUSED;
        return;
      }
    

    update_player(&player);
    update_bullet_arr(bullets, MAX_BULLETS);
    update_powerup_arr(powerups, MAX_POWERUPS);

    if (game.boss_stage){
      update_boss(&boss);
      boss_shoot(&boss, bullets, MAX_BULLETS);
    } else {
      update_alien_arr(aliens, MAX_ALIENS);
      update_ship(&ship);
    }

  }


  if (game.mode == MODE_PAUSED){
    printf("PAUSED");

    if(input.pause||input.shoot){
      game.mode = MODE_PLAYING;
    }
  return;
}

if(game.mode == MODE_GAMEOVER){
  printf("GAME OVER");
  if (qualify_high_score(&sc,sc.current_score)){
    game.mode = MODE_ENTER_INITIALS;
    return;
  }

  else {
    game.mode = MODE_SCOREBOARD;
    return;
  }

  if (input.restart){
    init_game();
    game.mode = MODE_PLAYING;
    return;
  }
}

if (game.mode == MODE_ENTER_INITIALS){
    insert_high_score(&sc, sc.current_score, "AAA");
  if(input.shoot){
    game.mode = MODE_SCOREBOARD;
    return;
  }
}

  if (game.mode == MODE_SCOREBOARD){
      if (input.restart){
        init_game();
        game.mode = MODE_PLAYING;
      }
    return;
  }

  update_timers();
  handle_input_playing();
  update_entities();
  handle_collisions();
  handle_spawning();
  return;
}


// definitions

static void update_timers(void){
      game.timers.frame_count++;
      game.timers.powerup_spawn_timer++;
      game.timers.event_timer++;

    if (game.timers.frame_count >= GAME_FPS){
      game.timers.seconds_count++;
    }

}
static void handle_input_playing(void){
}
static void update_entities(void){
}
static void handle_spawning(void){
}
static void handle_collisions(void){
}
