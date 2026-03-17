#include "game.h"

int alienWidthMin;
int alienWidthMax;
int alienNum;
int way;
int way2;

Object player;
Object *aliens;
Object spaceship;
Object playerBullet;
Object scoreTxt[3];
Object alienBullet;
Object LifeTxt;
Object playerLife;
Object gameOver;
Object defense[4];

byte *keys;
byte life;
int score;
int shoot;

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
    0x04, 0x51, 0x00,
    0x10, 0x00, 0x40,
    0x04, 0x01, 0x00,
    
    0x00, 0x50, 0x00,
    0x01, 0x54, 0x00,
    0x05, 0x55, 0x00,
    0x14, 0x51, 0x40,
    0x15, 0x55, 0x40,
    0x01, 0x04, 0x00,
    0x04, 0x51, 0x00,
    0x11, 0x04, 0x40,
};

const byte alien3[] = {
    0x00, 0x55, 0x00,
    0x15, 0x55, 0x54,
    0x55, 0x55, 0x55,
    0x54, 0x14, 0x15,
    0x55, 0x55, 0x55,
    0x05, 0x41, 0x50,
    0x14, 0x14, 0x14,
    0x05, 0x00, 0x50,

    0x00, 0x55, 0x00,
    0x15, 0x55, 0x54,
    0x55, 0x55, 0x55,
    0x54, 0x14, 0x15,
    0x55, 0x55, 0x55,
    0x01, 0x41, 0x40,
    0x05, 0x14, 0x50,
    0x50, 0x00, 0x05,
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
    0x02, 0x00, 0x00, 0x80,
};

const byte text[] = {
    0x0F,0xF0, 0x0F,0xF0, 0x0F,0xF0, 0x3F,0xF0, 0x3F,0xFC,
    0x30,0x0C, 0x30,0x0C, 0x30,0x0C, 0x30,0x0C, 0x30,0x00,
    0x30,0x00, 0x30,0x00, 0x30,0x0C, 0x30,0x0C, 0x30,0x00,
    0x0F,0xF0, 0x30,0x00, 0x30,0x0C, 0x3F,0xF0, 0x3F,0xF0,
    0x00,0x0C, 0x30,0x00, 0x30,0x0C, 0x30,0xC0, 0x30,0x00,
    0x30,0x0C, 0x30,0x0C, 0x30,0x0C, 0x30,0x30, 0x30,0x00,
    0x0F,0xF0, 0x0F,0xF0, 0x0F,0xF0, 0x30,0x0C, 0x3F,0xFC,
};

const byte number0[] = {
    0x0F,0xC0,
    0x30,0x30,
    0x30,0xF0,
    0x33,0x30,
    0x3C,0x30,
    0x30,0x30,
    0x0F,0xC0,
};
const byte number1[] = {
    0x03,0x00,
    0x0F,0x00,
    0x03,0x00,
    0x03,0x00,
    0x03,0x00,
    0x03,0x00,
    0x0F,0xC0,
};
const byte number2[] = {
    0x0F,0xC0,
    0x30,0x30,
    0x00,0x30,
    0x03,0xC0,
    0x0C,0x00,
    0x30,0x00,
    0x3F,0xF0,
};
const byte number3[] = {
    0x3F,0xF0,
    0x00,0x30,
    0x00,0xC0,
    0x03,0xC0,
    0x00,0x30,
    0x30,0x30,
    0x0F,0xC0,
};
const byte number4[] = {
    0x00,0xC0,
    0x03,0xC0,
    0x0C,0xC0,
    0x30,0xC0,
    0x3F,0xF0,
    0x00,0xC0,
    0x00,0xC0,
};
const byte number5[] = {
    0x3F,0xF0,
    0x30,0x00,
    0x3F,0xC0,
    0x00,0x30,
    0x00,0x30,
    0x30,0x30,
    0x0F,0xC0,
};
const byte number6[] = {
    0x03,0xF0,
    0x0C,0x00,
    0x30,0x00,
    0x3F,0xC0,
    0x30,0x30,
    0x30,0x30,
    0x0F,0xC0,
};
const byte number7[] = {
    0x3F,0xF0,
    0x00,0x30,
    0x00,0xC0,
    0x03,0x00,
    0x0C,0x00,
    0x0C,0x00,
    0x0C,0x00,
};
const byte number8[] = {
    0x0F,0xC0,
    0x30,0x30,
    0x30,0x30,
    0x0F,0xC0,
    0x30,0x30,
    0x30,0x30,
    0x0F,0xC0,
};
const byte number9[] = {
    0x0F,0xC0,
    0x30,0x30,
    0x30,0x30,
    0x0F,0xF0,
    0x00,0x30,
    0x00,0xC0,
    0x3F,0x00,
};
const byte defenseData[] = {
    0x00,0x3F, 0xFF,0xFF, 0xC0,0x00,
    0x00,0xFF, 0xFF,0xFF, 0xF0,0x00,
    0x03,0xFF, 0xFF,0xFF, 0xFC,0x00,
    0x0F,0xFF, 0xFF,0xFF, 0xFF,0x00,
    0x3F,0xFF, 0xFF,0xFF, 0xFF,0xC0,
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xF0,
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xF0,
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xF0,
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xF0,
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xF0,
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xF0,
    0xFF,0xFF, 0xFF,0xFF, 0xFF,0xF0,
    0xFF,0xFC, 0x00,0x03, 0xFF,0xF0,
    0xFF,0xF0, 0x00,0x00, 0xFF,0xF0,
    0xFF,0xC0, 0x00,0x00, 0x3F,0xF0,
    0xFF,0xC0, 0x00,0x00, 0x3F,0xF0,
};


Sprite textSpr = {40, 7, 70, text, 0};
Sprite Spr0 = {8,7, 14, number0, 0};
Sprite Spr1 = {8,7, 14, number1, 0};
Sprite Spr2 = {8,7, 14, number2, 0};
Sprite Spr3 = {8,7, 14, number3, 0};
Sprite Spr4 = {8,7, 14, number4, 0};
Sprite Spr5 = {8,7, 14, number5, 0};
Sprite Spr6 = {8,7, 14, number6, 0};
Sprite Spr7 = {8,7, 14, number7, 0};
Sprite Spr8 = {8,7, 14, number8, 0};
Sprite Spr9 = {8,7, 14, number9, 0};


void setupGame() {
    int i;
    Sprite playerSpr = {12, 8, 24, playerData, 0};
    Sprite alienSpr1 = {12, 8, 24, alien1, 0};
    Sprite alienSpr2 = {12, 8, 24, alien2, 0};
    Sprite alienSpr3 = {12, 8, 24, alien3, 0};
    Sprite spaceshipSpr = {16, 8, 32, spaceshipData, 0};
    Sprite defenseSpr = {24,16,96, defenseData};

    int startX = 85;
    int startY = 20;
    int spacingX = 16;
    int spacingY = 12;
    int cols = 11;

    alienWidthMin = startX;
    alienWidthMax = startX + (10*spacingX);
    way = 0;
    alienNum = 55;

    player.x = 160;
    player.y = 180;
    player.sprite = playerSpr;
    spaceship.x = -1;
    spaceship.y = 16;
    spaceship.sprite = spaceshipSpr;
    playerBullet.dead = 1;
    alienBullet.dead = 1;
    playerLife.sprite = playerSpr;
    playerLife.x = 28;
    playerLife.y = 192;
    life = 3;
    LifeTxt.x = 20;
    LifeTxt.y = 192;
    gameOver.dead = 1;

    if ((aliens = (Object *)malloc(55)) == NULL) {
        printf("Error : no memory for alien sprite");
        return;
    }

    for(i = 0; i < 55; i++){
        if(i < 11)
            aliens[i].sprite = alienSpr2;
        else if(i < 33)
            aliens[i].sprite = alienSpr1;
        else
            aliens[i].sprite = alienSpr3;

        aliens[i].x = startX + (i % cols) * spacingX;
        aliens[i].y = startY + (i / cols) * spacingY;
        aliens[i].dead = 0;
    }

    for(i = 0; i < 4; i++){
        defense[i].y = 160;
        defense[i].x = 56 + (i*spacingX*4);
        defense[i].dead = 0;
        defense[i].sprite = defenseSpr;
    }

    for(i=0;i<3;i++)
        scoreTxt[i].sprite = Spr0;

    keys = set_keyboard();
}

void input(int* is_running){
    if(keys[KEY_ESC] == 1){
        *is_running = 0;
    }

    if(player.dead == 1)
        return;

    if(keys[KEY_KEYPAD_4] == 1) {
        player.x--;
    }

    if(keys[KEY_KEYPAD_6] == 1) {
        player.x++;
    }

    if(keys[KEY_SPACE] == 1 && shoot == 0 && playerBullet.dead == 1) {
        shoot = 1;
        playerBullet.x = player.x+5;
        playerBullet.y = player.y-4;
        playerBullet.dead = 0;
    }
    else if (keys[KEY_SPACE] == 0 && playerBullet.dead == 1) {
        shoot = 0;
    }

}

void update(int *i, int *f, int *a){
    int j, left, right, r;
    

    // manage alien movement group
    
    if(*i >= alienNum) {
        *i = 0;
        if(player.dead && life > 0){
            player.dead = 0;
            life--;
        }
        else if(player.dead){
            gameOver.dead = 0;
        }

        if(way == 1){
            alienWidthMax += 8;
            alienWidthMin += 8;
            for(j = 0; j < 55; j++){
                if(aliens[j].dead == 1)
                    continue;

                aliens[j].sprite.anim = (aliens[j].sprite.anim + 1) % 2;
                if(alienWidthMax > 264){
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
            for(j = 0; j < 55; j++){
                if(aliens[j].dead == 1)
                    continue;

                aliens[j].sprite.anim = (aliens[j].sprite.anim + 1) % 2;
                if(alienWidthMin < 40){
                    way = 1;
                    aliens[j].y += 8;
                }
                else{
                    aliens[j].x -= 8;
                }

            }
        }

        left = find_leftmost(11, 5, aliens);
        if(left != -1){
            if(alienWidthMin < aliens[left].x){
                alienWidthMin = aliens[left].x;
            }
        }
        
        right = find_rightmost(11, 5, aliens);
        if(right != -1){
            if(alienWidthMax > aliens[right].x){
                alienWidthMax = aliens[right].x;
            }
        }
    }

    // manage spaceship movement
    if(*f >= 5){
        if(way2 == 1 && spaceship.x < 336)
            spaceship.x++;
        else if(spaceship.x > 336){
            *f = 0;
            way2 = 0;
        }


        if(way2 == 0 && spaceship.x > -16)
            spaceship.x--;
        else if(spaceship.x < -16){
            *f = 0;
            way2 = 1;
        }
    }

    // manage player movement & collision with aliens
    if(shoot == 1 && playerBullet.dead == 0) {
        playerBullet.y-=7;
        for(j = 0; j < 55; j++){
            if(aliens[j].dead == 0 && 
                playerBullet.y > aliens[j].y &&
                playerBullet.y < (aliens[j].y+8) && 
                playerBullet.x > aliens[j].x &&
                playerBullet.x < (aliens[j].x+12)){
                    playerBullet.dead = 1;
                    aliens[j].dead = 1;
                    alienNum--;
                    if(j > 36){
                        score++;
                    }else if(j > 12)
                        score += 2;
                    else
                        score += 3;
            }
        }
        if(playerBullet.y < 0){
            playerBullet.dead = 1;
        }
    }

    switch (score % 10)
    {
    case 0:
        scoreTxt[2].sprite = Spr0;
        break;
    case 1:
        scoreTxt[2].sprite = Spr1;
        break;
    case 2:
        scoreTxt[2].sprite = Spr2;
        break;
    case 3:
        scoreTxt[2].sprite = Spr3;
        break;
    case 4:
        scoreTxt[2].sprite = Spr4;
        break;
    case 5:
        scoreTxt[2].sprite = Spr5;
        break;
    case 6:
        scoreTxt[2].sprite = Spr6;
        break;
    case 7:
        scoreTxt[2].sprite = Spr7;
        break;
    case 8:
        scoreTxt[2].sprite = Spr8;
        break;
    case 9:
        scoreTxt[2].sprite = Spr9;
        break;
    }

    switch ((score/10) % 10)
    {
    case 0:
        scoreTxt[1].sprite = Spr0;
        break;
    case 1:
        scoreTxt[1].sprite = Spr1;
        break;
    case 2:
        scoreTxt[1].sprite = Spr2;
        break;
    case 3:
        scoreTxt[1].sprite = Spr3;
        break;
    case 4:
        scoreTxt[1].sprite = Spr4;
        break;
    case 5:
        scoreTxt[1].sprite = Spr5;
        break;
    case 6:
        scoreTxt[1].sprite = Spr6;
        break;
    case 7:
        scoreTxt[1].sprite = Spr7;
        break;
    case 8:
        scoreTxt[1].sprite = Spr8;
        break;
    case 9:
        scoreTxt[1].sprite = Spr9;
        break;
    }

    switch ((score/100) % 10)
    {
    case 0:
        scoreTxt[0].sprite = Spr0;
        break;
    case 1:
        scoreTxt[0].sprite = Spr1;
        break;
    case 2:
        scoreTxt[0].sprite = Spr2;
        break;
    case 3:
        scoreTxt[0].sprite = Spr3;
        break;
    case 4:
        scoreTxt[0].sprite = Spr4;
        break;
    case 5:
        scoreTxt[0].sprite = Spr5;
        break;
    case 6:
        scoreTxt[0].sprite = Spr6;
        break;
    case 7:
        scoreTxt[0].sprite = Spr7;
        break;
    case 8:
        scoreTxt[0].sprite = Spr8;
        break;
    case 9:
        scoreTxt[0].sprite = Spr9;
        break;
    }

    switch(life){
    case 0:
        LifeTxt.sprite = Spr0;
        break;
    case 1:
        LifeTxt.sprite = Spr1;
        break;
    case 2:
        LifeTxt.sprite = Spr2;
        break;
    case 3:
        LifeTxt.sprite = Spr3;
        break;
    }

    if(*a > 10 && alienBullet.dead == 1){
        r = alienWidthMin + rand() % alienWidthMax;
        *a = 0;
        alienBullet.y = aliens[54].y;
        alienBullet.dead = 0;
        alienBullet.x = r;
    }
    else if(*a > 10){
        *a = 0;
    }

    if(alienBullet.dead == 0){
        alienBullet.y+=5;
        if(player.dead == 0 && 
           alienBullet.y > player.y &&
           alienBullet.y < (player.y+8) && 
           alienBullet.x > player.x &&
           alienBullet.x < (player.x+12)){
                    player.dead = 1;
                    alienBullet.dead = 1;
                    
                    
            }

        if(alienBullet.y > 200){
            alienBullet.dead = 1;
        }
    }
}

void render(){
    int i;
    memset(buffer,0,0x4000);

    //draw
    draw_sprite(8,2,&textSpr);

    for(i=0;i<3;i++)
        draw_sprite(58+(i*8), 2, &scoreTxt[i].sprite);

    draw_sprite(82, 2, &Spr0);

    if(player.dead == 0)
        draw_sprite_fast(player.x, player.y, &player.sprite);

    for(i = 0; i < 55; i++){
        if(aliens[i].dead == 0)
            draw_sprite_fast(aliens[i].x, aliens[i].y, &aliens[i].sprite);
    }

    draw_sprite_fast(spaceship.x, spaceship.y, &spaceship.sprite);

    if(shoot == 1 && playerBullet.dead == 0){
        draw_square(playerBullet.x, playerBullet.y, 1, 4, 3);
    }

    if(alienBullet.dead == 0){
        draw_square(alienBullet.x, alienBullet.y, 1, 4, 2);
    }

    for(i = 0; i < 4; i++){
        draw_sprite_fast(defense[i].x, defense[i].y, &defense[i].sprite);
    }

    draw_sprite_fast(playerLife.x, playerLife.y, &playerLife.sprite);
    draw_sprite_fast(LifeTxt.x, LifeTxt.y, &LifeTxt.sprite);

    
    _fmemcpy(CGA,buffer,0x4000);
}