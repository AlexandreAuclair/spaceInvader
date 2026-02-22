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
    int offset;
    offset = (y / 2) * 80 + (x / 4);
    if (y % 2)
        offset += 0x2000;
    return offset;
}

//  draw pixel on screen
void draw_pixel(int index, byte color){
    CGA[index] = color;
}

void put_pixel(int x, int y, unsigned char color)
{
    unsigned int offset;
    unsigned char mask;

    offset = (y / 2) * 80 + (x / 4);

    if (y & 1)
        offset += 0x2000;

    mask = 0xC0 >> ((x & 3) * 2);

    CGA[offset] &= ~mask;
    CGA[offset] |= (color << (6 - (x & 3) * 2));
}