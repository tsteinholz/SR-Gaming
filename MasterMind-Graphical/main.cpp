#include <iostream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Code.h"

bool init();

ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_TIMER* timer;

const unsigned int SCREEN_W = 1080, SCREEN_H = 824;

int main(int argc, char **argv)
{
    if (!init()) return -1;

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    timer = al_create_timer(1.0 / 60);
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    bool executing = true;
    while (executing) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) executing = false;
                break;
            case ALLEGRO_EVENT_TIMER:
                break;
        }

        if (al_is_event_queue_empty(queue)) {

            al_draw_circle(SCREEN_W / 2, SCREEN_H / 2, 10, al_map_rgb(255, 255, 0), 3.0);


            al_flip_display();
        }
    }
    al_destroy_display(display);
    return 0;
}

bool init() {
    if(!al_init())
    {
        fprintf(stderr, "Failed to initialize allegro!\n");
        return false;
    }
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        fprintf(stderr, "Failed to create display!\n");
        return false;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_clear_to_color(al_map_rgb(0,0,0));
    return true;
}
