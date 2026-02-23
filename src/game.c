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
    
    memset(buffer,0,0x4000);
    



    //draw
    draw_square(object.x,object.y,32,32,2);

    if(object.x < 288)
        object.x++;
    
    if (object.y < 168)
    {
        object.y++;
    }
    
    
    _fmemcpy(CGA,buffer,0x4000);
}