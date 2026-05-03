#include "score.h"
#include "constants.h"


void init_score_sys(struct Score_Sys *sc}(
  sc->current_score = 0;

  for (i = 0; i < MAX_SCORES; i++){
      sc->top_scores[i].initials[0] = '-';
      sc->top_scores[i].initials[1] = '-';
      sc->top_scores[i].initials[2] = '-';
      sc->top_scores[i].initials[3] = '\0';

      sc->top_scores[i].score = 0;
  }
}

void add_score(struct Score_Sys *sc, struct Player *player, int points){
  sc ->current_score = 0;

  if(player->score_mult_active){
    points *= SCORE_MULT;
  }

  sc->current_score += points
}

bool qualify_high_score(struct Score_Sys *sc, int score){
  return score > sc->top_scores[MAX_SCORES -1].score;
}

int high_score_rank(struct Score_Sys *sc, int score){
  for (i = 0; i < MAX_SCORES; i++){
    if (score > sc->top_scores[i].score){
      return i;
    }
  }
return -1;
}

void insert_high_score(struct Score_Sys *sc, int score, const char initials[4]){
  int rank = high_score_rank(sc, score);

if (rank == -1) {
  return;
}

for (i= MAX_SCORES - 1; i>rank; i--) {
  sc->top_scores[i] = sc -> top_scores[i-1];

    sc->top_scores[rank].score = score;

    sc->top_scores[rank].initials[0] = initials[0];
    sc->top_scores[rank].initials[1] = initials[1];
    sc->top_scores[rank].initials[2] = initials[2];
    sc->top_scores[rank].initials[3] = '\0';
}
  
