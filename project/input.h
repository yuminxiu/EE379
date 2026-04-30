#ifndef INPUTS_H
#define INPUTS_H

#include <stdbool.h>

struct Input{
  bool left;
  bool right;
  bool shoot;
  bool pause;
  bool restart;
  char key_pressed;
}

void init_input(struct Input *input);
void update_struct(struct Input *input);

#endif
