#ifndef SPRITE_H
#define SPRITE_H

#include "globals.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    byte width;
    byte height;
    word size;
    byte *data;
    byte anim;
}Sprite;

typedef struct {
    word count;
    dword *offsets;
    FILE *file;
} SpritePack;


void save_sprite_pack(const char *filename, Sprite *sprites, word count);

Sprite *load_sprite(SpritePack *p, int id);

SpritePack *open_sprite_pack(const char *filename);

#endif