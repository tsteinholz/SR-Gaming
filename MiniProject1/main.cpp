#include <allegro.h>

#include "Object.h"
#include "Rectangle.h"

void init();
void deinit();

int main() {
	init();

    Rectangle r(0,0,5,5);
    
	while (!key[KEY_ESC]) {
		r.Render();
//		blit(screen, screen, 0, 0, SCREEN_W, SCREEN_H);
	}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
}

void deinit() {
	clear_keybuf();
}
