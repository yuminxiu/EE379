

### Requirements

- 320 x 240 LCD disp
- player character - laser cannon
- left/right via pushbuttons
- minimum 3 rows of 6 aliens
- ship across screen every 5 seconds
- aliens and ship disappear when hit by bullet
- player lives reduce until 0, then Game over
- Game over display
- lives remaining displayed, start with 3
- bullets fired via pushbutton


### Bonus
- score keeping. 20 points for alien, 50 for ship. <15>
- restart via button after game over <10>
- display lives via icon instead of number <5>
- bullets from alien and cannon have different shapes <5>
- animations
- pause/resume via pushbutton. display paused center of screen when paused <10>
- scoreboard
- audio/sfx
- drops/power ups
	- 
### aliens and ship disappear when hit by bullet

- collision flag/detection
- bullet class
- enemy class
	- only one enemy disappears, the rest remain and keep motion

- player hit animation
	- remaining lives - 1
	- if life = 0, game over


### variables
```c 
int num_of_life = 3
int life_remaining = num_of_life
int score = 0
int alien_points = 20
int ship_points = 50
bullet
player
alien
ship
int alien_hit = 0
int player_hit = 0
player_shoot
alien_shoot
int seconds_timer
int edge_detect = 0
int screen_left
int screen_right
int screen_bottom
int screen_width
int x 
int y 
game_over = false
paused = false
```


- laser shot
- bgm loop
- high score
- 
