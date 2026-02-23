#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "utils.h"
#include "object.h"

extern byte *buffer;

void input(int* is_running);

void update();

void render();

#endif