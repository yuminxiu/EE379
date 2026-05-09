// THIS FILE IS JUST FOR BRAINSTORMING FUNCTIONS. THEY WILL BE MOVED TO THE PROPER header FILES LATER


struct Player {
  int lives;
  int pos_x;
  int pos_y;

  bool can_shoot; // true = allowed to shoot, false = waiting (cooldown)
  int shoot_timer; // shooting cooldown

  bool hit; // true = recently hit

  int power_type; // 0 = none
  int power_timer; // duration
};


struct Bullet {
  int pos_x;
  int pos_y;

  int dy; // speed/direction
  int dx;

  bool active; // true = bullet exists on screen, false = no

  int type; // for future implementation
  int owner; // player, alien, boss


};

struct Alien {
  bool active;

  int pos_x;
  int pos_y;
  int row;
  int col;

  int sprite_type;
};

struct Alien_Formation {
  int speed;
  int direction; // -1 = left, +1 = right
  int step_down;
};

struct Ship {
  bool active;

  int pos_x;
  int pos_y;
  int dx;

  int spawn_timer;

  int direction; // 1 = left, 0 = right
};


struct PowerUp {
  bool active;

  int type;

  int pos_x;
  int pos_y;

  int dy;

  int despawn_timer;
  int spawn_timer;

  bool landed; //stay on bottom edge of screen until despawn or collision with player
};


struct High_Score {
  char initials[4];
  int score;
};

struct Boss {
  bool active;
  int hp;
  int max_health;
  int timer_pattern;
  int width;
  int height;
  int pos_x;
  int pos_y;
  int dx;
  int dy;

  int pattern_state;
};


struct Score_Sys {
  int current_score;

  struct High_Score top_scores[5];
};

struct Timers {
  int frame_count;
  int seconds_count;
  int event_timer;
};

struct game_state {
  int mode; // start, playing, paused, game over, scoreboard, entering intials
  bool boss_stage; // true if gameplay is boss level
  int wave; // current wave number
 struct Timers timers;
};

struct Animation {
  int frame;
  int frame_count;
  int frame_delay;
  int timer;
};

struct Sprite {
  int frame_w;
  int frame_h;
  int frame_count;
  const char *f; // point to file name or identifier
};

struct Animated_Sprite {
  struct Sprite *sprite;
  struct Animation ani;
};

struct Rect {  // hitbox needed for collisions
    int x;
    int y;
    int width;
    int height;
};
