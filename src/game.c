#include "game.h"

int kc;
Object player;
Object *aliens;

const byte alien[] = {
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
    Sprite alienSpr = {12,8,24, alien, 0};
    int startX = 40;
    int startY = 20;
    int spacingX = 20;
    int spacingY = 20;
    int cols = 12;

    player.x = 160;
    player.y = 160;
    player.sprite = playerSpr;

    if ((aliens = (Sprite *)malloc(60)) == NULL) {
        printf("Error : no memory for alien sprite");
        return;
    }

    for(i = 0; i < 60; i++){
        aliens[i].sprite = alienSpr;

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
    
    if(*i == 10) {
        *i = 0;
        for(j = 0; j < 60; j++){
            aliens[j].sprite.anim = (aliens[j].sprite.anim + 1) % 2;
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