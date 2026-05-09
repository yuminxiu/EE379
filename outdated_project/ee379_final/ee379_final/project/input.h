#ifndef INPUTS_H
#define INPUTS_H

#include <stdbool.h>

struct Input{
  bool left;
  bool right;
  bool up;
  bool down;
  bool shoot;
  bool pause;
  bool restart;
  bool cheat;
  char key_pressed;
};

void init_input(struct Input *input);
void update_input(struct Input *input);

void buttonInterruptHandler(void *instancePointer);
void init_button_interrupts(void);
#endif
