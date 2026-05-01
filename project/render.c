#include "render.h"
#include <MyDisp.h>

MYDISP display;

void init_render(void){
	display.begin();
	display.clearDisplay(clrWhite);
}

void render_game((struct Game_State *game, struct Player *player, struct PowerUp powerups[],int max_powerups, struct Ship *ship, struct Alien *aliens[MAX_ALIENS],int rows, int cols,
    struct Score_Sys *sc, struct Boss *boss, struct Bullet bullets[], int max_bullets) {
		//background
		//enemies
		//player
		...



    draw_aliens(aliens, max_aliens);
    draw_ship(ship);
    draw_boss(boss);
    draw_player(player);
    draw_bullets(bullets, max_bullets);
    draw_powerups(powerups, max_powerups);
    draw_ui(player, sc, game);
}

// not finished
