#include "xscugic.h"
#include "xtmrctr.h"
#include "xparameters.h"
#include "interrupts.h"
#include "game_timer.h"
#include "game.h"
#include "render.h"
#include "input.h"
#include "constants.h"

#include <XGpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MyDisp.h>

//Defines for interrupt IDs
#define INTC_DEVICE_ID XPAR_PS7_SCUGIC_0_DEVICE_ID
#define GPIO_INT_ID XPAR_FABRIC_AXI_GPIO_0_IP2INTC_IRPT_INTR
#define TIMER_INT_ID XPAR_FABRIC_AXI_TIMER_0_INTERRUPT_INTR

int main(void){
  initIntrSystem(&GIC);
  init_game_timer();

  init_input(&input);
  init_render();
  init_game();

  while (true) {
    if (timer_tick){
      timer_tick = 0;
  
      update_game();
      render_game(&game, &player, powerups, MAX_POWERUPS,
            &ship, aliens, MAX_ALIENS,
            &sc, &boss, bullets, MAX_BULLETS);
    }
  }
  return 0;
}
