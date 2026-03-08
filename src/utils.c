#include "utils.h"

byte far *CGA       = (byte *)0xB8000000L;       /* this points to video memory. */

//  Sets the video mode by calling the CPU interrupt VIDEO
void set_mode(byte mode)
{
    union REGS inregs, outregs;

    inregs.h.ah = SET_MODE;
    inregs.h.al = mode;
    int86(VIDEO_INT, &inregs, &outregs);

    inregs.h.ah = SET_PALETTE;
    inregs.h.bh = 1;
    inregs.h.bl = 1;
    int86(VIDEO_INT, &inregs, &outregs);

    inregs.h.ah = SET_PALETTE;
    inregs.h.bh = 0;
    inregs.h.bl = 0;
    int86(VIDEO_INT, &inregs, &outregs);
}

//  Translate the postion x,y to a 16-bit address
//  return address
word translate_position(int x, int y){
    word offset;
    offset = (y / 2) * 80 + (x / 4);
    if (y % 2)
        offset += 0x2000;
    return offset;
}

//  draw pixel on screen
void draw_pixel(word index, byte color){
    buffer[index] = color;
}

//  Translate the postion x,y to a 16-bit address and put it on screen
void put_pixel(int x, int y, byte color)
{
    word offset;
    byte mask;

    offset = (y / 2) * 80 + (x / 4);

    if (y & 1)
        offset += 0x2000;

    mask = 0xC0 >> ((x & 3) * 2);

    buffer[offset] &= ~mask;
    buffer[offset] |= (color << (6 - (x & 3) * 2));
}

// draw square on screen
void draw_square(int x, int y, int w, int h, byte color){
    int i,j;

    for(i=0;i<w;i++){
        for(j=0;j<h;j++){
            put_pixel(x+i, y+j, color);
        }
    }
}

// draw read sprite and draw it on screen
void draw_sprite(int x, int y, Sprite *sprite){
    int i;
    byte c1,c2,c3,c4;
    byte offset;

    if(x < 0 || x > 320)
        return;
    if(y < 0 || y > 200)
        return;
            

    if(sprite->anim == 1)
        offset = sprite->size;
    else
        offset = 0;

    for(i=0;i<(sprite->height*(sprite->width/4));i++){
        c1 = (sprite->data[i+offset] & 0xC0) >> 6;
        c2 = (sprite->data[i+offset] & 0x30) >> 4;
        c3 = (sprite->data[i+offset] & 0x0C) >> 2;
        c4 = sprite->data[i+offset] & 0x03;

        
        put_pixel(x+((i%(sprite->width/4))*4), y+i/(sprite->width/4), c1);
        put_pixel(x+((i%(sprite->width/4))*4)+1, y+i/(sprite->width/4), c2);
        put_pixel(x+((i%(sprite->width/4))*4)+2, y+i/(sprite->width/4), c3);
        put_pixel(x+((i%(sprite->width/4))*4)+3, y+i/(sprite->width/4), c4);
    }
}

