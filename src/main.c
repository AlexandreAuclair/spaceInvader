#include "game.h"

byte *buffer;

void setup(){
    set_mode(CGA_4_COLOR_MODE);

    // clear the screen
    if ((buffer = (byte *)malloc(0x4000)) == NULL) {
	    printf("Error: Failed to allocate memory for double buffer.\n");
	    return;
    }
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

    free(buffer);
    set_mode(TEXT_MODE);
    return 0;
}