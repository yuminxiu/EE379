#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define MODE_START 0
#define MODE_PLAYING 1
#define MODE_PAUSED 2
#define MODE_GAMEOVER 3
#define MODE_SCOREBOARD 4
#define MODE_ENTER_INITIALS 5


struct Timers {
  int frame_count;
  int seconds_count;
  int event_timer;
  int powerup_spawn_timer;
};

struct Game_State {
  int mode; // start, playing, paused, game over, scoreboard, entering intials
  bool boss_stage; // true if gameplay is boss level
  int wave; // current wave number
 struct Timers timers;
};

void init_game_state(struct Game_State *game);
void update_game_state(struct Game_State *game);

#endif
