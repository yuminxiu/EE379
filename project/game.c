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

struct Game_State game;
struct Player player;
struct Boss boss;
struct Bullet bullets[MAX_BULLETS]
struct Alien aliens[MAX_ALIENS]
struct Alien_Formation f;
struct Ship ship;
struct PowerUps powerups[MAX_POWERUPS];
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
