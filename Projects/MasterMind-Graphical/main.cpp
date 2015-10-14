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
ALLEGRO_BITMAP* background;
ALLEGRO_BITMAP* border;
ALLEGRO_FONT* century_gothic48B;

const unsigned int SCREEN_W = 1080, SCREEN_H = 824;
const unsigned int SCREEN_Wh = SCREEN_W/2, SCREEN_Hh = SCREEN_H/2;
const unsigned int pos_1=SCREEN_Wh-(3*25)-9;
const unsigned int pos_2=SCREEN_Wh-25-3;
const unsigned int pos_3=SCREEN_Wh+25+3;
const unsigned int pos_4=SCREEN_Wh+(3*25)+9;
const unsigned int pos_y=50;

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
            al_clear_to_color(al_map_rgb(0,0,0));
            al_set_target_bitmap(al_get_backbuffer(display));
            al_draw_bitmap(background, 0, 0, 0);
            al_draw_bitmap(border, 400, 30, 0);
            //TODO : draw border
            al_draw_text(century_gothic48B, al_map_rgb(255,255,255), SCREEN_W-355, pos_y+10, ALLEGRO_ALIGN_CENTRE, "Master Mind");
            ////////////////////////////////////////////////////////////////////

            //al_draw_filled_circle(pos_1, pos_y, 25, al_map_rgb(255, 255, 0));
            //al_draw_filled_circle(pos_2, pos_y, 25, al_map_rgb(255, 0, 255));
            //al_draw_filled_circle(pos_3, pos_y, 25, al_map_rgb(0, 255, 0));
            //al_draw_filled_circle(pos_4, pos_y, 25, al_map_rgb(0, 0, 255));

            ////////////////////////////////////////////////////////////////////
            al_flip_display();
        }
    }
    al_destroy_bitmap(background);
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
    al_init_image_addon();
    if(!al_init_primitives_addon()) {
        fprintf(stderr, "Failed to initialize primitives!\n");
        return false;
    }
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_clear_to_color(al_map_rgb(0,0,0));

    background = al_load_bitmap("res\\background.png");
    if (!background) {
        fprintf(stderr, "Failed load background image!\n");
        al_destroy_display(display);
        return false;
    }
    border = al_load_bitmap("res\\border.png");
    if (!border) {
        fprintf(stderr, "Failed load border image!\n");
        al_destroy_display(display);
        return false;
    }

    century_gothic48B = al_load_ttf_font("C:\\Windows\\Fonts\\GOTHICB.TTF", 48, ALLEGRO_ALIGN_CENTRE);

    return true;
}
