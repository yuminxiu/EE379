#include "render.h"
#include "constants.h"
#include "mtds.h"
#include <stdio.h>
#include <string.h>

static HDS hdsDisplay;
static HDS hdsBack;
static HBMP hbmpBack;

static HBR brBlack;
static HBR brWhite;
static HBR brGreen;
static HBR brRed;
static HBR brBlue;
static HBR brYellow;
static HBR brCyan;
static HBR brMagenta;
static HBR brLtGray;
static HBR brDkBlue;
static HBR brDkRed;
static HBR brDkMagenta;

static HBR brush_for_color(uint32_t color);

static void fill_rect(int x, int y, int w, int h, uint32_t color);
static void frame_rect(int x, int y, int w, int h, uint32_t color);
static void line_draw(int x1, int y1, int x2, int y2, uint32_t color);
static void draw_text(char *txt, int x, int y, uint32_t color);
static void clear_backbuffer(void);
static void present_frame(void);

static void draw_pause_screen(void);
static void draw_gameover_screen(void);

static void draw_tank_alien(int x, int y);
static void draw_drone_alien(int x, int y);
static void draw_crab_alien(int x, int y);

void init_render(void) {
    mtds.begin();
    mtds.SetDisplayOrientation(dsoPortrait);

    hdsDisplay = mtds.GetDisplayDs();

    hbmpBack = mtds.CreateBitmap(SCREEN_WIDTH, SCREEN_HEIGHT, 16);
    hdsBack = mtds.GetDs();
    mtds.SetDrawingSurface(hdsBack, hbmpBack);

    mtds.SetFont(hdsBack, hfntConsole);
    mtds.SetBkMode(hdsBack, bkTransparent);
    mtds.SetPen(hdsBack, penSolid);
    mtds.SetBrush(hdsBack, hbrNull);

    brBlack     = mtds.CreateSolidBrush(clrBlack);
    brWhite     = mtds.CreateSolidBrush(clrWhite);
    brGreen     = mtds.CreateSolidBrush(clrGreen);
    brRed       = mtds.CreateSolidBrush(clrRed);
    brBlue      = mtds.CreateSolidBrush(clrBlue);
    brYellow    = mtds.CreateSolidBrush(clrYellow);
    brCyan      = mtds.CreateSolidBrush(clrCyan);
    brMagenta   = mtds.CreateSolidBrush(clrMagenta);
    brLtGray    = mtds.CreateSolidBrush(clrLtGray);
    brDkBlue    = mtds.CreateSolidBrush(clrDkBlue);
    brDkRed     = mtds.CreateSolidBrush(clrDkRed);
    brDkMagenta = mtds.CreateSolidBrush(clrDkMagenta);

    clear_backbuffer();
    present_frame();
}

void render_game(struct Game_State *game,
                 struct Player *player,
                 struct PowerUp powerups[], int max_powerups,
                 struct Ship *ship,
                 struct Alien aliens[], int max_aliens,
                 struct Score_Sys *sc,
                 struct Boss *boss,
                 struct Bullet bullets[], int max_bullets,
                 struct BossBeam beams[], int max_beams) {

    clear_backbuffer();

    if (game->mode == MODE_START) {
        char start_text[] = "PRESS SHOOT";
        draw_text(start_text, 60, 150, clrWhite);
        present_frame();
        return;
    }

    if (game->mode == MODE_PAUSED) {
        draw_pause_screen();
        present_frame();
        return;
    }

    if (game->mode == MODE_GAMEOVER) {
        draw_gameover_screen();
        present_frame();
        return;
    }

    if (game->mode == MODE_SCOREBOARD) {
        char title[] = "SCOREBOARD";
        char line[24];

        draw_text(title, 60, 40, clrWhite);

        for (int i = 0; i < MAX_SCORES; i++) {
            sprintf(line, "%d. %s %d",
                    i + 1,
                    sc->top_scores[i].initials,
                    sc->top_scores[i].score);

            draw_text(line, 40, 70 + i * 20, clrWhite);
        }

        present_frame();
        return;
    }

    if (game->mode == MODE_ENTER_INITIALS) {
        char title[] = "ENTER INITIALS";
        char initials_text[8];

        sprintf(initials_text, "%c %c %c",
                game->initials[0],
                game->initials[1],
                game->initials[2]);

        draw_text(title, 40, 110, clrWhite);
        draw_text(initials_text, 90, 150, clrWhite);

        int cursor_x = 90 + game->initial_index * 16;
        fill_rect(cursor_x, 165, 8, 2, clrWhite);

        present_frame();
        return;
    }

    if (!game->boss_stage) {
        draw_aliens(aliens, max_aliens);
        draw_ship(ship);
    } else {
        draw_boss(boss);
        draw_boss_beams(beams, max_beams);
    }

    draw_player(player);
    draw_bullets(bullets, max_bullets);
    draw_powerups(powerups, max_powerups);
    draw_ui(player, sc, game, boss);

    present_frame();
}

/* ---------------- Gameplay Draw Functions ---------------- */

void draw_bullets(struct Bullet bullets[], int max_bullets) {
    for (int i = 0; i < max_bullets; i++) {
        if (!bullets[i].active) continue;

        int x = bullets[i].pos_x;
        int y = bullets[i].pos_y;

        if (bullets[i].owner == OWNER_PLAYER) {
            if (bullets[i].type == BULLET_LASER) {
                fill_rect(x, y, 3, 14, clrRed);
                line_draw(x + 1, y, x + 1, y + 13, clrWhite);
            }
            else if (bullets[i].type == BULLET_PIERCE) {
                fill_rect(x - 1, y, 4, 8, clrMagenta);
                line_draw(x + 1, y, x + 1, y + 9, clrWhite);
            }
            else if (bullets[i].type == BULLET_BURST) {
                fill_rect(x - 1, y - 1, 5, 5, clrYellow);
                fill_rect(x, y, 3, 3, clrWhite);
            }
            else {
                fill_rect(x, y, 2, 7, clrWhite);
            }
        }
        else {
            if (bullets[i].owner == OWNER_BOSS) {
                fill_rect(x - 2, y - 2, 7, 7, clrRed);
                fill_rect(x, y, 3, 3, clrYellow);
            } else {
                fill_rect(x - 1, y - 1, 5, 5, clrDkRed);
                fill_rect(x, y, 2, 2, clrRed);
            }
        }
    }
}

void draw_aliens(struct Alien aliens[], int max_aliens) {
    for (int i = 0; i < max_aliens; i++) {
        if (!aliens[i].active) continue;

        int x = aliens[i].pos_x;
        int y = aliens[i].pos_y;

        if (aliens[i].row == 0) {
            draw_tank_alien(x, y);
        }
        else if (aliens[i].row == 1) {
            draw_drone_alien(x, y);
        }
        else {
            draw_crab_alien(x, y);
        }
    }
}

void draw_ship(struct Ship *ship) {
    if (!ship->active) return;

    int x = ship->pos_x;
    int y = ship->pos_y;

    fill_rect(x + 4, y, 12, 4, clrLtGray);
    fill_rect(x, y + 4, 20, 6, clrBlue);
    fill_rect(x + 4, y + 10, 12, 3, clrLtGray);

    fill_rect(x + 3,  y + 6, 2, 2, clrYellow);
    fill_rect(x + 9,  y + 6, 2, 2, clrYellow);
    fill_rect(x + 15, y + 6, 2, 2, clrYellow);
}

void draw_powerups(struct PowerUp powerups[], int max_powerups) {
    for (int i = 0; i < max_powerups; i++) {
        if (!powerups[i].active) continue;

        int x = powerups[i].pos_x;
        int y = powerups[i].pos_y;

        if (powerups[i].type == POWERUP_EXTRA_LIFE) {
            fill_rect(x + 5, y, 3, 4, clrGreen);
            fill_rect(x + 3, y + 4, 7, 3, clrGreen);
            fill_rect(x, y + 7, 13, 4, clrGreen);
        }
        else if (powerups[i].type == POWERUP_SCORE_MULT) {
            line_draw(x + 6, y, x + 12, y + 6, clrYellow);
            line_draw(x + 12, y + 6, x + 6, y + 12, clrYellow);
            line_draw(x + 6, y + 12, x, y + 6, clrYellow);
            line_draw(x, y + 6, x + 6, y, clrYellow);
            fill_rect(x + 4, y + 4, 4, 4, clrYellow);
        }
        else if (powerups[i].type == POWERUP_LASER) {
            fill_rect(x + 5, y, 2, 12, clrRed);
            fill_rect(x + 3, y + 2, 6, 2, clrYellow);
            fill_rect(x + 3, y + 8, 6, 2, clrYellow);
        }
        else if (powerups[i].type == POWERUP_SHIELD) {
            frame_rect(x, y, 12, 12, clrCyan);
            fill_rect(x + 3, y + 3, 6, 6, clrCyan);
            fill_rect(x + 5, y + 1, 2, 10, clrWhite);
            fill_rect(x + 1, y + 5, 10, 2, clrWhite);
        }
        else if (powerups[i].type == POWERUP_TRIPLE_SHOT) {
            fill_rect(x + 1, y + 2, 2, 8, clrMagenta);
            fill_rect(x + 5, y, 2, 10, clrMagenta);
            fill_rect(x + 9, y + 2, 2, 8, clrMagenta);
        }
    }
}

void draw_player(struct Player *player) {
    int x = player->pos_x;
    int y = player->pos_y;

    fill_rect(x + 6, y, 4, 6, clrGreen);
    fill_rect(x + 3, y + 6, 10, 5, clrGreen);
    fill_rect(x, y + 11, PLAYER_WIDTH, 5, clrGreen);

    if (player->shield_active) {
        frame_rect(x - 2, y - 2, PLAYER_WIDTH + 4, PLAYER_HEIGHT + 4, clrCyan);
    }
}

void draw_boss(struct Boss *boss) {
    if (!boss->active) return;

    int x = boss->pos_x;
    int y = boss->pos_y;
    int w = boss->width;
    int h = boss->height;

    fill_rect(x, y + 10, 12, 16, clrMagenta);
    fill_rect(x + w - 12, y + 10, 12, 16, clrMagenta);

    fill_rect(x + 10, y + 4, w - 20, h - 8, clrDkMagenta);
    fill_rect(x + 20, y, w - 40, 8, clrLtGray);

    fill_rect(x + w / 2 - 8, y + h / 2 - 8, 16, 16, clrRed);
    fill_rect(x + w / 2 - 3, y + h / 2 - 3, 6, 6, clrWhite);

    fill_rect(x + 8, y + h - 4, 8, 6, clrRed);
    fill_rect(x + w - 16, y + h - 4, 8, 6, clrRed);
}

void draw_boss_beams(struct BossBeam beams[], int max_beams) {
    for (int i = 0; i < max_beams; i++) {
        if (!beams[i].active) continue;

        if (beams[i].firing) {
            fill_rect(beams[i].x, beams[i].y, beams[i].width, beams[i].height, clrDkBlue);
        } else {
            for (int yy = beams[i].y; yy < beams[i].y + beams[i].height; yy += 6) {
                fill_rect(beams[i].x, yy, beams[i].width, 3, clrMagenta);
            }
        }
    }
}

void draw_ui(struct Player *player,
             struct Score_Sys *sc,
             struct Game_State *game,
             struct Boss *boss) {

    for (int i = 0; i < player->lives; i++) {
        int x = 4 + i * 18;
        int y = 300;

        fill_rect(x + 5, y, 3, 4, clrGreen);
        fill_rect(x + 3, y + 4, 7, 3, clrGreen);
        fill_rect(x, y + 7, 13, 4, clrGreen);
    }

    char score_text[20];
    sprintf(score_text, "SCORE %d", sc->current_score);
    draw_text(score_text, 80, 300, clrLtGray);

    if (game->boss_stage && boss->active) {
        int hp_width = (boss->hp * BOSS_HP_BAR_WIDTH) / boss->max_hp;
        if (hp_width < 0) hp_width = 0;

        frame_rect(70, 18, BOSS_HP_BAR_WIDTH, BOSS_HP_BAR_HEIGHT, clrWhite);
        fill_rect(70, 18, hp_width, BOSS_HP_BAR_HEIGHT, clrMagenta);
    }

    int icon_x = 150;

    if (player->shield_active) {
        fill_rect(icon_x, 4, 8, 8, clrCyan);
        icon_x += 12;
    }

    if (player->score_mult_active) {
        fill_rect(icon_x, 4, 8, 8, clrYellow);
        icon_x += 12;
    }

    if (player->bullet_power_type == BULLET_POWER_LASER) {
        fill_rect(icon_x, 4, 8, 8, clrRed);
    }
    else if (player->bullet_power_type == BULLET_POWER_TRIPLE_SHOT) {
        fill_rect(icon_x, 4, 8, 8, clrGreen);
    }
    else if (player->bullet_power_type == BULLET_POWER_PIERCE) {
        fill_rect(icon_x, 4, 8, 8, clrMagenta);
    }
}

/* ---------------- Screens ---------------- */

static void draw_pause_screen(void) {
    char paused_text[] = "PAUSED";

    frame_rect(35, 115, 170, 80, clrWhite);

    fill_rect(75, 135, 10, 35, clrWhite);
    fill_rect(155, 135, 10, 35, clrWhite);

    draw_text(paused_text, 86, 150, clrYellow);
}

static void draw_gameover_screen(void) {
    char gameover_text[] = "GAME OVER";

    for (int i = 0; i < SCREEN_WIDTH; i += 16) {
        fill_rect(i, 110, 8, 20, clrDkRed);
        fill_rect(i + 8, 190, 8, 20, clrDkRed);
    }

    frame_rect(45, 130, 150, 50, clrRed);
    draw_text(gameover_text, 70, 150, clrRed);
}

/* ---------------- Enemy Designs ---------------- */

static void draw_tank_alien(int x, int y) {
    fill_rect(x, y + 3, 16, 10, clrBlue);
    fill_rect(x + 3, y, 10, 5, clrBlue);

    frame_rect(x + 1, y + 4, 14, 8, clrLtGray);

    fill_rect(x + 4, y + 6, 2, 2, clrWhite);
    fill_rect(x + 10, y + 6, 2, 2, clrWhite);

    fill_rect(x + 2, y + 13, 4, 3, clrBlue);
    fill_rect(x + 10, y + 13, 4, 3, clrBlue);
}

static void draw_drone_alien(int x, int y) {
    line_draw(x + 8, y, x + 16, y + 8, clrYellow);
    line_draw(x + 16, y + 8, x + 8, y + 16, clrYellow);
    line_draw(x + 8, y + 16, x, y + 8, clrYellow);
    line_draw(x, y + 8, x + 8, y, clrYellow);

    fill_rect(x + 5, y + 5, 6, 6, clrYellow);
    fill_rect(x + 7, y + 7, 2, 2, clrWhite);
}

static void draw_crab_alien(int x, int y) {
    fill_rect(x + 3, y + 3, 10, 8, clrCyan);
    fill_rect(x + 1, y + 5, 4, 5, clrCyan);
    fill_rect(x + 11, y + 5, 4, 5, clrCyan);

    line_draw(x + 1, y + 8, x - 3, y + 12, clrCyan);
    line_draw(x + 14, y + 8, x + 18, y + 12, clrCyan);

    fill_rect(x + 5, y + 5, 2, 2, clrWhite);
    fill_rect(x + 9, y + 5, 2, 2, clrWhite);
}

/* ---------------- Helpers ---------------- */

static void clear_backbuffer(void) {
    RCT r;
    r.xcoLeft = 0;
    r.ycoTop = 0;
    r.xcoRight = SCREEN_WIDTH;
    r.ycoBottom = SCREEN_HEIGHT;

    mtds.FillRect(hdsBack, &r, hbrBlack);
}

static void present_frame(void) {
    mtds.DrawBitmap(hdsDisplay,
                    0,
                    0,
                    SCREEN_WIDTH,
                    SCREEN_HEIGHT,
                    hdsBack,
                    0,
                    0);
}

static void fill_rect(int x, int y, int w, int h, uint32_t color) {
    RCT r;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (w <= 0 || h <= 0) return;

    r.xcoLeft = x;
    r.ycoTop = y;
    r.xcoRight = x + w;
    r.ycoBottom = y + h;

    mtds.FillRect(hdsBack, &r, brush_for_color(color));
}

static void frame_rect(int x, int y, int w, int h, uint32_t color) {
    RCT r;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (w <= 0 || h <= 0) return;

    r.xcoLeft = x;
    r.ycoTop = y;
    r.xcoRight = x + w;
    r.ycoBottom = y + h;

    mtds.SetFgColor(hdsBack, color);
    mtds.SetBrush(hdsBack, hbrNull);
    mtds.FrameRect(hdsBack, &r);
}

static void line_draw(int x1, int y1, int x2, int y2, uint32_t color) {
    mtds.SetFgColor(hdsBack, color);
    mtds.SetBrush(hdsBack, hbrNull);
    mtds.MoveTo(hdsBack, x1, y1);
    mtds.LineTo(hdsBack, x2, y2);
}

static void draw_text(char *txt, int x, int y, uint32_t color) {
    mtds.SetFgColor(hdsBack, color);
    mtds.SetBkMode(hdsBack, bkTransparent);
    mtds.SetBrush(hdsBack, hbrNull);

    mtds.TextOut(hdsBack,
                 x,
                 y,
                 (int)strlen(txt),
                 txt);
}

static HBR brush_for_color(uint32_t color) {
    if (color == clrBlack) return brBlack;
    if (color == clrWhite) return brWhite;
    if (color == clrGreen) return brGreen;
    if (color == clrRed) return brRed;
    if (color == clrBlue) return brBlue;
    if (color == clrYellow) return brYellow;
    if (color == clrCyan) return brCyan;
    if (color == clrMagenta) return brMagenta;
    if (color == clrLtGray) return brLtGray;
    if (color == clrDkBlue) return brDkBlue;
    if (color == clrDkRed) return brDkRed;
    if (color == clrDkMagenta) return brDkMagenta;

    return brWhite;
}
