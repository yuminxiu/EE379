#ifndef ANIMATION_H
#define ANIMATION_H

struct Animation {
  int frame;
  int frame_count;
  int frame_delay;
  int timer;
};

struct Sprite {
  int frame_w;
  int frame_h;
  int frame_count;
  const char *f; // point to file name or identifier
};

struct Animated_Sprite {
  struct Sprite *sprite;
  struct Animation ani;
};

void update_animation(struct Animated_Sprite *anim);
#endif
