#ifndef UTILS_H
#define UTILS_H

#include <dos.h>
#include "globals.h"
#include "sprite.h"
#include "object.h"

extern byte *buffer;

//  Sets the video mode by calling the CPU interrupt VIDEO
void set_mode(byte mode);

//  Translate the postion x,y to a 16-bit address
//  return address
word translate_position(int x, int y);

//  draw pixel on screen
void draw_pixel(word index, byte color);

//  Translate the postion x,y to a 16-bit address and put it on screen
void put_pixel(int x, int y, byte color);

// draw square on screen
void draw_square(int x, int y, int w, int h, byte color);

// draw sprite on screen
void draw_sprite(int x, int y, Sprite *sprite);

void draw_sprite_fast(int x, int y, Sprite *sprite);

// finding the leftmost element in a array of object
int find_leftmost(int cols, int rows, Object *array);

// finding the rightmost element in a array of object
int find_rightmost(int cols, int rows, Object *array);

#endif