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
#include "bossbeam.h"
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
static bool prev_shoot = false;

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
struct BossBeam beams[MAX_BEAMS];

#define MAX_WAVE 3


void init_game(void){
  game.mode = MODE_START;
  game.boss_stage = false; 
  game.wave = 1;


  game.timers.frame_count = 0;
  game.timers.seconds_count = 0;
  game.timers.ship_spawn_timer = 0;
  game.timers.next_ship_spawn = ((rand() % 2)+5)*GAME_FPS;
  game.timers.powerup_spawn_timer = 0;
  game.timers.next_powerup_spawn = ((rand() % POWERUP_SPAWN_RANGE_SEC) + POWERUP_SPAWN_MIN_SEC)* GAME_FPS;
  game.timers.wave_transition_timer = 0;

  game.initials[0] = 'A';
  game.initials[1] = 'A';
  game.initials[2] = 'A';
  game.initials[3] = '\0';
  game.initial_index = 0;

  prev_pause  = false;
  prev_pause = false;
  input.cheat = false;

  init_player(&player);
  init_alien_formation(&f);
  init_alien_arr(aliens, MAX_ALIENS);
  init_bullet_arr(bullets, MAX_BULLETS);
  init_ship(&ship);
  init_score_sys(&sc);
  init_boss(&boss);
  init_powerup_arr(powerups, MAX_POWERUPS);
  //init_input(&input);
  init_boss_beam_arr(beams,MAX_BEAMS);
}


void update_game(void){
  update_input(&input);

  bool paused_pressed = input.pause && !prev_pause;
  prev_pause = input.pause;

  bool shoot_pressed = input.shoot && !prev_shoot;
  prev_shoot = input.shoot;

  if (game.mode == MODE_START){

    if (input.cheat){
    input.cheat = false;
     start_boss_stage();
      game.mode = MODE_PLAYING;
      return;
    }

    if (shoot_pressed){
    game.mode = MODE_PLAYING;
    return;
    }    
    return;
}
  
  if (game.mode == MODE_PLAYING){
      if(paused_pressed){
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
    	input.cheat = false;
      start_boss_stage();
      game.mode= MODE_PLAYING;
      return;
    }

    if(paused_pressed){
      game.mode = MODE_PLAYING;
      return;
    }
  return;
}

if(game.mode == MODE_GAMEOVER){
	  if (input.restart){
	    init_game();
	    game.mode = MODE_START;
	    return;
	  }

	if(shoot_pressed){

  if (qualify_high_score(&sc,sc.current_score)){
    game.mode = MODE_ENTER_INITIALS;
  } else {
	  game.mode = MODE_SCOREBOARD;}
  return;
  }

  return;
}

if (game.mode == MODE_ENTER_INITIALS){
	if(input.left){
		game.initials[game.initial_index]--;

		if(game.initials[game.initial_index] < 'A'){
			game.initials[game.initial_index] = 'Z';
		}
	}

	if(input.right){
		game.initials[game.initial_index]++;
		if (game.initials[game.initial_index] > 'Z'){
			game.initials[game.initial_index]= 'A';
		}
	}

  if(shoot_pressed) {
	game.initial_index++;

	if(game.initial_index >= 3){
    insert_high_score(&sc, sc.current_score, game.initials);
    game.initial_index = 0;
    game.mode = MODE_SCOREBOARD;
  }
    return;
}
return;
}

  if (game.mode == MODE_SCOREBOARD){
      if (input.restart||input.shoot){
        init_game();
        game.mode = MODE_START;
        return;
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
      boss_shoot(&boss, bullets, MAX_BULLETS, beams, MAX_BEAMS);
      update_boss_beam_arr(beams, MAX_BEAMS);
    } else {
      update_alien_arr(aliens, MAX_ALIENS, &f);
      update_ship(&ship);
      handle_alien_shooting();
    }

    for (int i = 0; i < MAX_ALIENS; i++){
    	if (aliens[i].active && aliens[i].pos_y + ALIEN_HEIGHT >= PLAYER_START_Y){
    		game.mode = MODE_GAMEOVER;
    		return;
    	}
    }
  }

/*static bool alien_bullet_exists(void){
	for (int i = 0; i < MAX_BULLETS; i++){
		if (bullets[i].active && bullets[i].owner == OWNER_ALIEN){
			return true;
		}
	}
	return false;
}
*/
static void handle_alien_shooting(void){
  static int alien_shoot_timer = 0;
  alien_shoot_timer++;

  if (alien_shoot_timer < ALIEN_SHOOT_COOLDOWN) {
    return;
  }

  // required alien shooting parameter
  /*if (alien_bullet_exists()){
	  return;
  }
*/
  alien_shoot_timer = 0;

  int start = rand() % MAX_ALIENS;

  for (int i = 0; i < MAX_ALIENS; i++){
    int index = (start +i) % MAX_ALIENS;

    if (aliens[index].active){
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
      for (int i = 0; i < MAX_BEAMS; i++){
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
            game.boss_stage = false;
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
  init_boss_beam_arr(beams, MAX_BEAMS);

  init_ship(&ship);
  init_boss(&boss);
  game.wave = 3;
  game.boss_stage = true;
  boss.active = true;
}
