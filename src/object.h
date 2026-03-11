#ifndef OBJECT_H
#define OBJECT_H

#include "sprite.h"

typedef struct {
    int x;
    int y;
    Sprite sprite;
    byte dead;
}Object;

#endif