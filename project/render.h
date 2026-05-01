#ifndef RENDER_H
#define RENDER_H

#include "player.h"
#incldue "bullet.h"
#include "alien.h"
#include "boss.h"
#include "powerup.h"
#include "score.h"
#include "game.h"

void init_render(void);

void render_game(struct Game_State *game, 
    struct Player *player, 
    struct PowerUp powerups[],int max_powerups, 
    struct Ship *ship, struct Alien aliens[],int max_aliens,
    struct Score_Sys *sc, 
    struct Boss *boss, 
    struct Bullet bullets[], int max_bullets);

void draw_player(struct Player *player);
void draw_bullets(struct Bullet bullets[], int max_bullets);
void draw_ship(struct Ship *ship);
void draw_aliens(struct Alien *aliens[], int max_aliens);
void draw_boss(struct Boss *boss);
void draw_powerups(struct PowerUp powerups[], int max_powerups);
void draw_ui(struct Player *player, struct Score_Sys *sc, struct Game_State *game, struct Boss *boss);

#endif
