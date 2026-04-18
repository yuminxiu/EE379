// this is just a file to test the code without the board

#include <stdio.h>
#include "player.h"
#include "bullet.h"

int main() {
  struct Player player;
  struct Bullet bullets[MAX_BULLETS];

  init_player(&player);
  init_bullet_arr(bullets, MAX_BULLETS);

  printf("Initial player position: %d, %d\n", player.pos_x, player.pos_y);

  player_shoot(&player, bullets, MAX_BULLETS);

  for (int i = 0; i < MAX_BULLETS; i++){
    if (bullets[i].active){
      printf("bullet spawned at: %d, %d \n", bullets[i].pos_x, bullets[i].pos_y);
    }
  }

 for (int frame = 0; frame < 5; frame++) {
        update_player(&player);
        update_bullet_array(bullets, MAX_BULLETS);

        printf("Frame %d:\n", frame);

        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                printf(" Bullet %d at (%d, %d)\n",
                       i,
                       bullets[i].pos_x,
                       bullets[i].pos_y);
            }
        }
    }

    return 0;
}
