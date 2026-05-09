

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
- barriers
- drops/power ups
	- extra life
   	- rapid fire
   	- score multiplier
   	- double shot
   	- temporary shield
   	- freeze enemy movement for 3 seconds
   	- screen clear
   	- piercing bullets
   	- triple shot
   	- laser beam
   	- extra points
   	- clone
 
- difficulty scaling/wave system
  	- aliens move faster over time/as drop
  	- ships appear faster
  	- aliens shoot more often
 
- multiple alien types?
- boss level?
- bullet patterns
- title screen
- win screen
- keyboard controls
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
position_player
```


- laser shot
- bgm loop
- high score
- 

```c
main.c
	- initialize board, display, inputs, timers, game, run main loop, call update and draw functions
	- game_update()
game.c/.h
	- handles overall game states, starting, restarting, updating the game, switching between modes: start screen, playing, paused, game over, initial entry, scoreboard, boss level
	Functions:
		- initialize game
		- reset game
		- update game
		- switch to next wave
		- enter boss stage
		- handle game over
player.c/.h
	- player state and behavior: movement, firing, lives, hit state
	Functions:
		- initialize player
		- update player
		- move player
		- player fire request
		- apply damage to player
		- draw player
enemy.c/.h
	- aliens, ship, wave, boss logic
	Functions:
		- initialize wave
		- update aliens
		- move aliens
		- reverse and descend on edge
		- spawn/update ship
		- choose alien shooter
		- draw aliens
		- check if wave clear
bullet.c/.h
	- bullet movement, bullet arrays, spawning, deactivating, update behavior
	Functions:
		- initalize bullet system
		- spawn player bullet
		- spawn enemy bullet
		- update bullets
		- deactivate bullet
		- draw bullets
collision.c/collision.h
	- checks between player bullets and aliens, alien bullets and player, drops and player, boss and bullets
input.c/.h
	- handles controls and control flags, buttons, keyboard/uart, direction actions
	Functions:
	- initialize input
	- button isr
	- keyboard read/update
	- consume input flags
	- clear input flags

render.c/.h
	- drawings: sprites, score, lives, text, game over, paused, start, high score, scoreboard
	Functions:
	- draw start screen
	- draw gameplay screen
	- draw hud
	- draw score
	- draw lives
	- draw pause screen
	- draw game over
	- draw initials entry
	- draw scoreboard
	- draw boss health bar
audio.c/.h
	Functions:
		- initalize audio
		- start music
		- stop music
		- play sound effect
		- update audio
		- switch track
score.c/.h
	- current score,, top 5 list, initial entry support
	Functions:
	- reset current score
	- add alien points
	- add ship points
	- check if score qualifies
	- insert new high score
	- update initials entry
	- draw scoreboard data 
powerup.c/.h
	- power ups
	Functions:
		- spawn drops
		- update drops
		- apply power up
		- expire power up
		- draw drops
boss.c/.h
 - boss flag, pattern, timer, sprite, phase,hp
	Functions:
		- initialize boss
		- update boss
		- draw boss
		- apply boss damage
		- boss hp
		- trigger next boss pattern
		- check boss defeat
```

### Stuff that should be functions

- move player
- fire bullet
- spawn alien bullet
- update wave
- update boss pattern
- check collisions
- add score
- reduce life
- restart game
- draw hud
- insert high score
- advanced initials cursor

## structures?
	- player
		- x,y
		- lives
		- cooldown/ can shoot flag
		- hit state
		- power up flag

	- bullet
		- active
		- x,y
		- dx/dy 
		- type
		- owner (player or alien)

	- alien
		- alive (true/false)
		- local row/col / x/y
		- sprite/type

	- alien formation
		- base positio (x,y)
		- direction (left/right)
		- step size/ speed
		- edge detection state

	- ship
		- active
		- position
		- direction
		- spawn timer

	- boss
		- active
		- hp
		- max health
		- pattern state
		- timer for switching pattern
		- bounds (x,y,w,h)

	- high score
		- initials[3]
		- score

	- power ups/drops
		- active
		- type
		- position
		- fall speed
		- despawn timer

	- timers/timing
		- frame counter
		- seconds counter
		- event timer

	- game state
		- current mode:
			- start
			- playing
			- paused
			- game over
			- entering intials
			- scoreboard
			- boss stage
		- curent wave
		- timer counters
