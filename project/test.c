// this is just a file to test the code without the board

#include <stdio.h>
#include "player.h"
#include "bullet.h"

int main() {
  struct Player player;
  struct Bullet bullets[max_bullets];

  init_player(&player);
  init_bullet_arr(bullets, max_bullets);

  printf("Initial player position: %d, %d\n", player.pos_x, player.pos_y);

  player_shoot(&player, bullets, max_bullets);

  for (int i = 0; i < max_bullets; i++){
    if (bullets[i].active){
      printf("bullet spawned at: %d, %d \n", bullets[i].pos_x, bullets[i].pos_y);
    }
  }

 for (int frame = 0; frame < 5; frame++) {
        update_player(&player);
        update_bullet_array(bullets, max_bullets);

        printf("Frame %d:\n", frame);

        for (int i = 0; i < max_bullets; i++) {
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
