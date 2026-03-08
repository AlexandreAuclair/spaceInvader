#include "game.h"

int kc;
int alienWidthMin;
int alienWidthMax;
int way;
Object player;
Object *aliens;

const byte alien1[] = {
    0x04, 0x00, 0x40,
    0x01, 0x01, 0x00,
    0x05, 0x55, 0x40,
    0x14, 0x54, 0x50,
    0x55, 0x55, 0x54,
    0x45, 0x55, 0x44,
    0x44, 0x00, 0x44,
    0x01, 0x45, 0x00,

    0x04, 0x00, 0x40,
    0x41, 0x01, 0x04,
    0x45, 0x55, 0x44,
    0x54, 0x54, 0x54,
    0x55, 0x55, 0x54,
    0x15, 0x55, 0x50,
    0x04, 0x00, 0x40,
    0x10, 0x00, 0x10,
};

const byte alien2[] = {
    0x00, 0x50, 0x00,
    0x01, 0x54, 0x00,
    0x05, 0x55, 0x00,
    0x14, 0x51, 0x40,
    0x15, 0x55, 0x40,
    0x01, 0x04, 0x00,
    0x04, 0x51, 0x00,
    0x41, 0x04, 0x40,

    0x00, 0x50, 0x00,
    0x01, 0x54, 0x00,
    0x05, 0x55, 0x00,
    0x14, 0x51, 0x40,
    0x15, 0x55, 0x40,
    0x04, 0x51, 0x00,
    0x10, 0x00, 0x40,
    0x04, 0x01, 0x00,
};

const byte alien3[] = {
    0x00, 0x55, 0x00,
    0x15, 0x55, 0x54,
    0x55, 0x55, 0x55,
    0x54, 0x14, 0x15,
    0x55, 0x55, 0x55,
    0x01, 0x41, 0x40,
    0x05, 0x14, 0x50,
    0x50, 0x00, 0x05,

    0x00, 0x55, 0x00,
    0x15, 0x55, 0x54,
    0x55, 0x55, 0x55,
    0x54, 0x14, 0x15,
    0x55, 0x55, 0x55,
    0x05, 0x41, 0x50,
    0x14, 0x14, 0x14,
    0x05, 0x00, 0x50,
};

const byte playerData[] = {
    0x00, 0x30, 0x00,
    0x00, 0xFC, 0x00,
    0x00, 0xFC, 0x00,
    0x3F, 0xFF, 0xF0,
    0xFF, 0xFF, 0xFC,
    0xFF, 0xFF, 0xFC,
    0xFF, 0xFF, 0xFC,
    0x00, 0x00, 0x00
};

void setupGame() {
    int i;
    Sprite playerSpr = {12,8,24, playerData, 0};
    Sprite alienSpr1 = {12,8,24, alien1, 0};
    Sprite alienSpr2 = {12,8,24, alien2, 0};
    Sprite alienSpr3 = {12,8,24, alien3, 0};
    int startX = 32;
    int startY = 20;
    int spacingX = 20;
    int spacingY = 20;
    int cols = 12;

    alienWidthMin = 16;
    alienWidthMax = 252;
    way = 1;

    player.x = 160;
    player.y = 160;
    player.sprite = playerSpr;

    if ((aliens = (Sprite *)malloc(60)) == NULL) {
        printf("Error : no memory for alien sprite");
        return;
    }

    for(i = 0; i < 60; i++){
        if(i < 12)
            aliens[i].sprite = alienSpr2;
        else if(i < 36)
            aliens[i].sprite = alienSpr1;
        else
            aliens[i].sprite = alienSpr3;

        aliens[i].x = startX + (i % cols) * spacingX;
        aliens[i].y = startY + (i / cols) * spacingY;
    }
}

void input(int* is_running){
    if(kbhit()) 
        kc = getch();

    if(kc == 27){
        *is_running = 0;
    }
}

void update(int *i){
    int j;
    
    if(*i == 5) {
        *i = 0;
        if(way == 1){
            alienWidthMax += 8;
            alienWidthMin += 8;
            for(j = 0; j < 60; j++){
                aliens[j].sprite.anim = (aliens[j].sprite.anim + 1) % 2;
                if(alienWidthMax > 308){
                    way = 0;
                    aliens[j].x -= 8;
                }
                else{
                    aliens[j].x += 8;
                }
            }
        }
        else {
            alienWidthMax -= 8;
            alienWidthMin -= 8;
            for(j = 0; j < 60; j++){
                aliens[j].sprite.anim = (aliens[j].sprite.anim + 1) % 2;
                if(alienWidthMin < 0){
                    way = 1;
                    aliens[j].x += 8;
                }
                else{
                    aliens[j].x -= 8;
                }
            }
        }

        
    }
}

void render(){
    int i;
    memset(buffer,0,0x4000);

    //draw
    draw_sprite(player.x, player.y, &player.sprite);

    for(i = 0; i < 60; i++){
        draw_sprite(aliens[i].x, aliens[i].y, &aliens[i].sprite);
    }
    
    _fmemcpy(CGA,buffer,0x4000);
}