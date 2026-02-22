#include "game.h"

void setup(){
    set_mode(CGA_4_COLOR_MODE);
}

int main(void) {
    int is_running,i;

    setup();

    is_running = 1;
    i = 0;
    while(is_running){
        input(&is_running);
        update();
        render(i);
        i++;
    }

    set_mode(TEXT_MODE);
    return 0;
}