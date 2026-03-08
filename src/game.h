#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "utils.h"
#include "object.h"
#include "sprite.h"

extern byte *buffer;
extern Sprite *mage;
extern Sprite *smiley;
extern byte far *CGA;

void setupGame();

void input(int *is_running);

void update(int *i);

void render();

#endif