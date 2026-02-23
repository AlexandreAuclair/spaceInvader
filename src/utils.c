#include "utils.h"

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