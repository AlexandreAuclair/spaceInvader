#include "game.h"

byte *buffer;
SpritePack *pack;
Sprite *mage;
Sprite *smiley;

void setup(){
    set_mode(CGA_4_COLOR_MODE);

    // clear the screen
    if ((buffer = (byte *)malloc(0x4000)) == NULL) {
	    printf("Error: Failed to allocate memory for double buffer.\n");
	    return;
    }

    pack = open_sprite_pack("sprites.spr");

    mage = load_sprite(pack, 1);
    smiley = load_sprite(pack, 0);

    srand((unsigned)time(NULL));

    setupGame();

}

int main(void) {
    int is_running,i,f,a;

    setup();

    is_running = 1;
    i = 0;
    f = 0;
    a = 0;
    while(is_running){
        input(&is_running);
        update(&i,&f,&a);
        render();
        i++;
        f++;
        a++;
    }

    unset_keyboard();
    free(buffer);
    set_mode(TEXT_MODE);
    return 0;
}