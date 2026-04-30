#ifndef SCORE_H
#define SCORE_H

#include <stdbool.h>
#include "player.h"

#define MAX_SCORES 5


struct High_Score {
  char initials[4];
  int score;
};

struct Score_Sys {
  int current_score;

  struct High_Score top_scores[MAX_SCORES];
};

void init_score_sys(struct Score_Sys *sc);
void reset_current_score(struct Score_Sys *sc);
void add_score(struct Score_Sys *sc, struct Player *player, int points);
void insert_high_score(struct Score_sys *sc, int score, const char initials[4]);

bool qualify_high_score(struct Score_Sys *sc, int score);

int high_score_rank(struct Score_Sys *sc, int score);

#endif
