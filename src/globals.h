#ifndef GLOBALS_H
#define GLOBALS_H

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

#endif