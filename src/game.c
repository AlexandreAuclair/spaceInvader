#include "game.h"

int kc;
Object object;

void input(int* is_running){
    if(kbhit()) 
        kc = getch();

    if(kc == 27){
        *is_running = 0;
    }
}

void update(){
    int i;

    i = 10 + 17;
}

void render(){
    int i;

    i = translate_position(234, 96);
    draw_pixel(i, 0xFF);

}