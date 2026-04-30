#include "score.h"
#include "constants.h"


void init_score_sys(struct Score_Sys *sc)(
  sc->current_score = 0;

  for (i = 0; i < MAX_SCORE; i++){
      sc->top_scores[i].initials[0] = '-';
      sc->top_scores[i].initials[1] = '-';
      sc->top_scores[i].initials[2] = '-';
      sc->top_scores[i].initials[3] = '\0';

      sc->top_scores[i].score = 0;
  }
}

void add_score(struct Score_Sys *sc, struct Player *player, int points){
  sc ->current_score = 0;

  if(player->power_type = POWER_UP_SCORE_MULT){
    points *= score_mult;
  }

  sc->current_score += points
}

bool qualify_high_score(struct Score_Sys *sc, int score){
  return score > score_sys->top_scores[MAX_SCORES -1].score;
}

int high_score_rank(struct Score_Sys *sc, int score){
  for (i = 0; i < MAX_SCORES; i++){
    if (score > score_sys->top_scores[i].score){
      return i;
    }
  }
return -1;
}

void insert_high_score(struct Score_sys *sc, int score, const char initials[4]){
  int rank = high_score_rank(struct Score_Sys *sc, int score);

if (rank == -1) {
  return;
}

for (i= MAX_SCORES - 1; i>rank; i--) {
  score_sys->top_scores[i] = score_sys -> top_scores[i-1];

    score_sys->top_scores[rank].score = score;

    score_sys->top_scores[rank].initials[0] = initials[0];
    score_sys->top_scores[rank].initials[1] = initials[1];
    score_sys->top_scores[rank].initials[2] = initials[2];
    score_sys->top_scores[rank].initials[3] = '\0';
}
  
