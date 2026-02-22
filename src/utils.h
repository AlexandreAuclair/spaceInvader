#ifndef UTILS_H
#define UTILS_H

#include <dos.h>

#define VIDEO_INT           0x10        /* the BIOS video interrupt. */
#define SET_MODE            0x00        /* BIOS func to set the video mode. */
#define SET_PALETTE         0x0B        /* BIOS func to set the Palette mode. */

#define TEXT_MODE           0x03        /* use to set 80x25 text mode. */
#define CGA_4_COLOR_MODE    0x04        /* use to set 4-color mode. YRG or MCW */
#define CGA_5_COLOR_MODE    0x05        /* use to set 4-color mode. */
#define CGA_6_BW_MODE       0x06        /* use to set black & white mode. 640 x 200 */

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

byte far *CGA       = (byte *)0xB8000000L;       /* this points to video memory. */

//  Sets the video mode by calling the CPU interrupt VIDEO
void set_mode(byte mode);

//  Translate the postion x,y to a 16-bit address
//  return address
word translate_position(int x, int y);

//  draw pixel on screen
void draw_pixel(int index, byte color);

#endif