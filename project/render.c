#include "render.h"
#include "constants.h"
#include <MyDisp.h>

MYDISP display;

void init_render(void){
	display.begin();
	display.clearDisplay(clrWhite);
}

void render_game((struct Game_State *game, struct Player *player, struct PowerUp powerups[],int max_powerups, struct Ship *ship, struct Alien *aliens[MAX_ALIENS], int max_aliens,
    struct Score_Sys *sc, struct Boss *boss, struct Bullet bullets[], int max_bullets) {


	display.clearDisplay(clrBlack);

	if (game->mode == MODE_START){
		//place holder start screen
		display.fillRectangle(40,140,160,40,clrWhite);
		return;
	}

	if (game->mode == MODE_PAUSED){
		display.fillRectangle(60,140,120,40, clrYellow);
		return;
	}

	if (game->mode == MODE_GAMEOVER){
		display.fillRectangle(40, 140,160,40, clrRed);
		return;
	}

	draw_aliens(aliens, max_aliens);
    draw_ship(ship);
    draw_boss(boss);
    draw_player(player);
    draw_bullets(bullets, max_bullets);
    draw_powerups(powerups, max_powerups);
    draw_ui(player, sc, game, boss);
}

void draw_bullets(struct Bullet bullets[], int max_bullets){
	for (int i = 0; i < max_bullets; i++){
		if (!bullet[i].active){
			continue;
		}

		int w = PLAYER_BULLET_WIDTH;
		int h = PLAYER_BULLET_HEIGHT;

		if (bullets[i].owner == OWNER_ALIEN || bullets[i].owner == OWNER_BOSS){
			w = ALIEN_BULLET_WIDTH;
			h = ALIEN_BULLET_HEIGHT;
		}

		display.fillRectangle(bullets[i].pos_x, bullets[i].pos_y, w, h, clrWhite);
	}
}

void draw_aliens(struct Alien *aliens[], int max_aliens){
	for (int i = 0; i < max_aliens; i++){
		if (!aliens[i].active){
			continue;
		}

		display.fillRectangle(aliens[i].pos_x, aliens[i].pos_y, ALIEN_WIDTH, ALIEN_HEIGHT, clrGreen);
	}
}

void draw_ship(struct Ship *ship){
	if (!ship->active){
		return;
	}

	display.fillRectangle(ship->pos_x, ship->pos_y, SHIP_WIDTH, SHIP_HEIGHT, clrBlue);
}


void draw_powerups(struct PowerUp powerups[], int max_powerups) {
    for (int i = 0; i < max_powerups; i++) {
        if (!powerups[i].active) {
            continue;
        }

        display.fillRectangle(powerups[i].pos_x,
                              powerups[i].pos_y,
                              POWERUP_WIDTH,
                              POWERUP_HEIGHT,
                              clrYellow);
    }
}


void draw_ui(struct Player *player, struct Score_Sys *sc, struct Game_State *game, struct Boss *boss) {
    // Simple UI strip
    display.fillRectangle(0, 0, SCREEN_WIDTH, UI_BAR_HEIGHT, clrWhite);

    // Placeholder lives blocks
    for (int i = 0; i < player->lives; i++) {
        display.fillRectangle(4 + i * 10, 4, 8, 8, clrGreen);
    }

    // Placeholder boss HP bar
    if (game->boss_stage && boss.active) {
        display.fillRectangle(70, 4, BOSS_HP_BAR_WIDTH, BOSS_HP_BAR_HEIGHT, clrRed);
    }
}

	
