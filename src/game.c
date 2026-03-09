#include "game.h"

int alienWidthMin;
int alienWidthMax;
int alienNum;
int way;
int way2;
Object player;
Object *aliens;
Object spaceship;
byte *keys;

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
    0x11, 0x04, 0x40,

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

const byte spaceshipData[] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x2A, 0xA8, 0x00,
    0x02, 0xAA, 0xAA, 0x80,
    0x0A, 0xAA, 0xAA, 0xA0,
    0x28, 0xA2, 0x8A, 0x28,
    0xAA, 0xAA, 0xAA, 0xAA,
    0x0A, 0x82, 0x82, 0xA0,
    0x02, 0x00, 0x00, 0x80
};

void setupGame() {
    int i;
    Sprite playerSpr = {12, 8, 24, playerData, 0};
    Sprite alienSpr1 = {12, 8, 24, alien1, 0};
    Sprite alienSpr2 = {12, 8, 24, alien2, 0};
    Sprite alienSpr3 = {12, 8, 24, alien3, 0};
    Sprite spaceshipSpr = {16, 8, 32, spaceshipData, 0};
    int startX = 32;
    int startY = 20;
    int spacingX = 20;
    int spacingY = 20;
    int cols = 12;

    alienWidthMin = 24;
    alienWidthMax = 252;
    way = 1;
    alienNum = 60;

    player.x = 160;
    player.y = 160;
    player.sprite = playerSpr;
    spaceship.x = -1;
    spaceship.y = 16;
    spaceship.sprite = spaceshipSpr;

    if ((aliens = (Sprite *)malloc(alienNum)) == NULL) {
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

    keys = set_keyboard();
}

void input(int* is_running){
    if(keys[KEY_ESC] == 1){
        *is_running = 0;
    }

    if(keys[KEY_KEYPAD_4] == 1) {
        player.x--;
    }

    if(keys[KEY_KEYPAD_6] == 1) {
        player.x++;
    }
}

void update(int *i, int *f){
    int j;
    
    if(*i == 15) {
        *i = 0;
        if(way == 1){
            alienWidthMax += 8;
            alienWidthMin += 8;
            for(j = 0; j < 60; j++){
                aliens[j].sprite.anim = (aliens[j].sprite.anim + 1) % 2;
                if(alienWidthMax > 308){
                    way = 0;
                    aliens[j].y += 8;
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
                    aliens[j].y += 8;
                }
                else{
                    aliens[j].x -= 8;
                }
            }
        }
    }

    if(*f > 1){
        if(way2 == 1 && spaceship.x < 320)
            spaceship.x++;
        else if(spaceship.x > 320){
            *f = 0;
            way2 = 0;
        }


        if(way2 == 0 && spaceship.x > -16)
            spaceship.x--;
        else if(spaceship.x < 0){
            *f = 0;
            way2 = 1;
        }
    }
}

void render(){
    int i;
    memset(buffer,0,0x4000);

    //draw
    draw_sprite_fast(player.x, player.y, &player.sprite);

    for(i = 0; i < alienNum; i++){
        draw_sprite_fast(aliens[i].x, aliens[i].y, &aliens[i].sprite);
    }

    draw_sprite_fast(spaceship.x, spaceship.y, &spaceship.sprite);

    
    _fmemcpy(CGA,buffer,0x4000);
}