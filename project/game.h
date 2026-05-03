#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "constants.h"

#define MODE_START 0
#define MODE_PLAYING 1
#define MODE_PAUSED 2
#define MODE_GAMEOVER 3
#define MODE_SCOREBOARD 4
#define MODE_ENTER_INITIALS 5

extern struct Game_State game;
extern struct Player player;
extern struct PowerUp powerups[MAX_POWERUPS];
extern struct Ship ship;
extern struct Alien aliens[MAX_ALIENS];
extern struct Score_Sys sc;
extern struct Boss boss;
extern struct Bullet bullets[MAX_BULLETS];
extern struct Input input;

struct Timers {
  int frame_count; // counts frams up to GAME_FPS
  int seconds_count; // seconds elapsed, currently optional
  int ship_spawn_timer;
  int next_ship_spawn;

  int powerup_spawn_timer;
  int next_powerup_spawn;

  int wave_transition_timer;
};

struct Game_State {
  int mode; // start, playing, paused, game over, scoreboard, entering intials
  bool boss_stage; // true if gameplay is boss level
  int wave; // current wave number
 struct Timers timers;
};

void init_game(void);
void update_game(void);

#endif
